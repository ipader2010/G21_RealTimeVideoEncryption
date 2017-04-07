`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/05/2017 02:17:20 PM
// Design Name: 
// Module Name: stateRegs
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


module stateRegs
(
    input wire clk,
    input wire resetn,
    input wire writen,
    input wire [127:0] newState,
    output wire [127:0] currState 
);
      
    reg_b128 regb128 (
        .D(newState),
        .clk(clk), 
        .resetn(resetn),
        .en(writen),
        .Q(currState)
    );
endmodule
