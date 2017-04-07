`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/05/2017 01:53:11 PM
// Design Name: 
// Module Name: AddRoundKey
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


module AddRoundKey(
    input wire [127:0] statein,
    //176 8-bit roundkey
    input wire [1407:0] roundkey, 
    input wire [3:0] round,
    output wire [127:0] state_out
);
    reg [127:0]stateout;
    
    always@(*) begin
            case (round)
            4'h0:
                stateout = statein ^ roundkey[127:0]; 
            4'h1:
                stateout = statein ^ roundkey[255:128]; 
            4'h2:
                stateout = statein ^ roundkey[383:256]; 
            4'h3:
                stateout = statein ^ roundkey[511:384];
            4'h4:
                stateout = statein ^ roundkey[639:512];
            4'h5:
                stateout = statein ^ roundkey[767:640];
            4'h6:
                stateout = statein ^ roundkey[895:768];
            4'h7:
                stateout = statein ^ roundkey[1023:896];
            4'h8:
                stateout = statein ^ roundkey[1151:1024];
            4'h9:
                stateout = statein ^ roundkey[1279:1152];
            4'ha:
                stateout = statein ^ roundkey[1407:1280];
            default:
                stateout = stateout;
            endcase
    end
    assign state_out = stateout;
    
endmodule
