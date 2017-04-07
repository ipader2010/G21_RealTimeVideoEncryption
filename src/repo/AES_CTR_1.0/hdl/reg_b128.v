`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/05/2017 03:03:39 PM
// Design Name: 
// Module Name: reg_b128
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


module reg_b128(
    input [127:0]D,
    input clk, resetn, en,
    output reg[127:0]Q  
    );
  
    always@(posedge clk) begin
        if (!resetn)
            Q <= 128'b0;
        else if (en)
            Q <= D;
        else
            Q <= Q;
    end
    
endmodule
