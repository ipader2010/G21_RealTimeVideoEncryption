`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/10/2017 01:34:57 PM
// Design Name: 
// Module Name: Encryption
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module Encryption(
    input wire [127:0]keyin,
    input wire [127:0]statein,
    input wire [127:0]datain,
    output wire [127:0]stateout
    );
    
    wire [127:0]state_out[12:0];
    wire [1407:0]round_key;
    
    KeyExpansion keyexp(
        .keyin(keyin),
        .roundKey(round_key)
    );
    
    AddRoundKey rkey0(
        .statein(statein),
        .roundkey(round_key), 
        .round(4'h0),
        .state_out(state_out[0])
    );
    
    Cipher cpr1(.roundkey(round_key), .statein(state_out[0]), .round(4'h1), .stateout(state_out[1]));
    Cipher cpr2(.roundkey(round_key), .statein(state_out[1]), .round(4'h2), .stateout(state_out[2]));
    Cipher cpr3(.roundkey(round_key), .statein(state_out[2]), .round(4'h3), .stateout(state_out[3]));
    Cipher cpr4(.roundkey(round_key), .statein(state_out[3]), .round(4'h4), .stateout(state_out[4]));
    Cipher cpr5(.roundkey(round_key), .statein(state_out[4]), .round(4'h5), .stateout(state_out[5]));
    Cipher cpr6(.roundkey(round_key), .statein(state_out[5]), .round(4'h6), .stateout(state_out[6]));
    Cipher cpr7(.roundkey(round_key), .statein(state_out[6]), .round(4'h7), .stateout(state_out[7]));
    Cipher cpr8(.roundkey(round_key), .statein(state_out[7]), .round(4'h8), .stateout(state_out[8]));
    Cipher cpr9(.roundkey(round_key), .statein(state_out[8]), .round(4'h9), .stateout(state_out[9]));
   
   /*
    */
    //Last round SubByte
    SubBytes sbox(
        .state_data_in(state_out[9]),
        .state_data_out(state_out[10])
    );
    
       
    //Last round ShiftRow
    ShiftRows shfr(
        .state_data_in(state_out[10]),
        .state_data_out(state_out[11])
    );
      
    
    //Last round addRoundKey
    AddRoundKey rkey10(
        .statein(state_out[11]),
        .roundkey(round_key), 
        .round(4'ha),
        .state_out(state_out[12])
    );
    
    assign stateout = state_out[12] ^ datain;
    
endmodule
