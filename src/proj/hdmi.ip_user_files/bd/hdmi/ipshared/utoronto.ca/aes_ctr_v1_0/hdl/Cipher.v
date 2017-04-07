`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/10/2017 01:08:05 PM
// Design Name: 
// Module Name: Cipher
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


module Cipher(
    input wire [1407:0]roundkey,
    input wire [127:0]statein,
    input wire [3:0]round,
    output wire [127:0]stateout
    );
    
    wire [127:0]state_out[3:0];
   
    
    //Sub Byte
    SubBytes sbox(
           .state_data_in(statein),
           .state_data_out(state_out[0])
    );
    
    //Shift Row
    ShiftRows shfr(
           .state_data_in(state_out[0]),
           .state_data_out(state_out[1])
    );
    
    //Mix Column
    MixColumns mxcl(
           .state_data_in(state_out[1]),
           .state_data_out(state_out[2])
    );
    
    //Add Roundkey
    AddRoundKey rkey(
        .statein(state_out[2]),
        .roundkey(roundkey), 
        .round(round),
        .state_out(state_out[3])
    );
    
     assign stateout = state_out[3];
endmodule
