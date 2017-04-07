`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/08/2017 07:08:59 PM
// Design Name: 
// Module Name: KeyExpSub_Byte16
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


module KeyExpSub_Byte16(    
    input wire [7:0]i,
    input wire [127:0]wordin,
    output wire [127:0]keyout
    );
    
    KeyExpSub_Byte4 keySub0(
        .i(i),
        .word_in(wordin[127:96]),
        .word_in1(wordin[31:0]),
        .wordheader(1'b1),
        .wordout(keyout[31:0])
    );
    

    KeyExpSub_Byte4 keySub1(
        .i(i),
        .word_in(keyout[31:0]),
        .word_in1(wordin[63:32]),
        .wordheader(1'b0),
        .wordout(keyout[63:32])
    );
    
   
    KeyExpSub_Byte4 keySub2(
        .i(i),
        .word_in(keyout[63:32]),
        .word_in1(wordin[95:64]),
        .wordheader(1'b0),
        .wordout(keyout[95:64])
    );
    
    KeyExpSub_Byte4 keySub3(
        .i(i),
        .word_in(keyout[95:64]),
        .word_in1(wordin[127:96]),
        .wordheader(1'b0),
        .wordout(keyout[127:96])
    );
    
endmodule
