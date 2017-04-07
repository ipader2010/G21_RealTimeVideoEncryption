`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/08/2017 07:10:12 PM
// Design Name: 
// Module Name: KeyExpSub_Byte4
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


module KeyExpSub_Byte4(
    input wire [7:0]i,
    input wire [31:0]word_in,
    input wire [31:0]word_in1,
    input wire wordheader,
    output wire [31:0]wordout
    );
    
    reg [7:0] tempbyte;
    reg [127:0] tempwordin;
    wire [127:0] tempwordout;
    wire [7:0] rconwordin, rconwordout;
    wire [31:0] wdout;
    
    assign rconwordin = i;

    SubBytes sbox(
        .state_data_in(tempwordin),
        .state_data_out(tempwordout)
    );
   
    SubRcon rcon(
        .data_in(rconwordin),
        .data_out(rconwordout)
    );
    
    always@(*) begin
        tempbyte = word_in[7:0];
        tempwordin[31:0] = word_in[31:0];
        tempwordin[31:0] = tempwordin[31:0] >> 8;
        tempwordin[31:24] = tempbyte;
    end

    assign wdout[31:8] = tempwordout[31:8];
    assign wdout[7:0] =  tempwordout[7:0] ^ rconwordout;
    assign wordout = (wordheader == 1'b1) ? wdout^word_in1 : word_in^word_in1;
    
endmodule
