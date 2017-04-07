`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/05/2017 01:40:33 PM
// Design Name: 
// Module Name: aes_part1
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


module aes_part1   
(
    input wire clk,
    input wire resetn
);
    
    wire [127:0] newState;
    wire [127:0] currState;
    //176 8-bit roundkey
    wire [1407:0] roundkey;
    wire wren;
    wire adden, mixen;
    wire [3:0]round;
    
    AddRoundKey addrkey( 
        .clk(clk),
        .resetn(resetn),
        .enable(adden),
        .statein(newState),
        .roundkey(roundkey), 
        .round(round),
        .stateout(currState)
    );
    
    stateRegs statereg(
        .clk(clk),
        .resetn(resetn),
        .writen(wren),
        .newState(newState),
        .currState(currState)  
    ); 
        
    MixCol mixcol(
        .clk(clk),
        .resetn(resetn),
        .enable(mixen),
        .statein(newState),
        .stateout(currState)
    );    
    
endmodule
