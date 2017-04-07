`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/08/2017 06:25:36 PM
// Design Name: 
// Module Name: xtime
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


module xtime(
    input [7:0] x,
    output [7:0] d_out
    );
    
    assign d_out = (x<<1) ^ (((x>>7) & 8'b1) * 8'h1b);
endmodule
