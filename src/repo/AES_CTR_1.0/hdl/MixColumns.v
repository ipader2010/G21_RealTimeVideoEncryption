`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/07/2017 07:47:35 PM
// Design Name: 
// Module Name: MixColumns
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


module MixColumns(
    input [127:0] state_data_in,
    output [127:0] state_data_out
    );
    
    genvar i;
    generate
        for(i = 0; i < 4; i = i+ 1) begin: i1
            assign state_data_out[i*32 + 7 : i*32] = state_data_in[i*32 + 7 : i*32] 
                    ^ (((state_data_in[i*32 + 7 : i*32] ^ state_data_in[i*32 + 15 : i*32 + 8]) << 1) // xtime -> x<<1
                    ^ (((state_data_in[i*32 + 7 : i*32] ^ state_data_in[i*32 + 15 : i*32 + 8]) >> 7) & 127'd1) * 128'h1b) // xtime -> x>>6, &1, *0x1b
                    ^ (state_data_in[i*32 + 7 : i*32] ^ state_data_in[i*32 + 15 : i*32 + 8] ^ state_data_in[i*32 + 23: i*32 + 16]
                    ^ state_data_in[i*32 + 31 : i*32 + 24]); // ^ Tmp
                    
            assign state_data_out[i*32 + 15 : i*32 + 8] = state_data_in[i*32 + 15 : i*32 + 8] 
                                        ^ (((state_data_in[i*32 + 15 : i*32 + 8] ^ state_data_in[i*32 + 23 : i*32 + 16]) << 1) // xtime -> x<<1
                                        ^ (((state_data_in[i*32 + 15 : i*32 + 8] ^ state_data_in[i*32 + 23 : i*32 + 16]) >> 7) & 127'd1) * 128'h1b) // xtime -> x>>6, &1, *0x1b
                                        ^ (state_data_in[i*32 + 7 : i*32] ^ state_data_in[i*32 + 15 : i*32 + 8] ^ state_data_in[i*32 + 23: i*32 + 16]
                                        ^ state_data_in[i*32 + 31 : i*32 + 24]); // ^ Tmp
                                        
            assign state_data_out[i*32 + 23 : i*32 + 16] = state_data_in[i*32 + 23 : i*32 + 16] // ^=
                                        ^ (((state_data_in[i*32 + 23 : i*32 + 16] ^ state_data_in[i*32 + 31 : i*32 + 24]) << 1) // xtime -> x<<1
                                        ^ (((state_data_in[i*32 + 23 : i*32 + 16] ^ state_data_in[i*32 + 31 : i*32 + 24]) >> 7) & 127'd1) * 128'h1b) // xtime -> x>>6, &1, *0x1b
                                        ^ (state_data_in[i*32 + 7 : i*32] ^ state_data_in[i*32 + 15 : i*32 + 8] ^ state_data_in[i*32 + 23: i*32 + 16]
                                        ^ state_data_in[i*32 + 31 : i*32 + 24]); // ^ Tmp
                                        
            assign state_data_out[i*32 + 31 : i*32 + 24] = state_data_in[i*32 + 31 : i*32 + 24]
                                        ^ (((state_data_in[i*32 + 31 : i*32 + 24] ^ state_data_in[i*32 + 7 : i*32]) << 1)
                                        ^ (((state_data_in[i*32 + 31 : i*32 + 24] ^ state_data_in[i*32 + 7 : i*32]) >> 7) & 127'd1) * 128'h1b)
                                        ^ (state_data_in[i*32 + 7 : i*32] ^ state_data_in[i*32 + 15 : i*32 + 8] ^ state_data_in[i*32 + 23: i*32 + 16]
                                        ^ state_data_in[i*32 + 31 : i*32 + 24]);
        end
    endgenerate
endmodule
