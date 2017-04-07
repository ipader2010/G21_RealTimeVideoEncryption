`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/07/2017 03:29:34 PM
// Design Name: 
// Module Name: ShiftRows
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


module ShiftRows(
	input [127:0] state_data_in,
	output [127:0] state_data_out
    );

	/*
		 0       1       2       3
	0	7:0    15:8    23:16   31:24
	1	39:32  47:40   55:48   63:56
	2	71:64  79:72   87:80   95:88
	3	103:96 111:104 119:112 127:120
	*/

	// row 0
	assign state_data_out[7:0]     = state_data_in[7:0];
	assign state_data_out[39:32]   = state_data_in[39:32];
	assign state_data_out[71:64]   = state_data_in[71:64];
	assign state_data_out[103:96]  = state_data_in[103:96];

	// row 1
	assign state_data_out[15:8]    = state_data_in[47:40];
	assign state_data_out[47:40]   = state_data_in[79:72];
	assign state_data_out[79:72]   = state_data_in[111:104];
	assign state_data_out[111:104] = state_data_in[15:8];

	// row 2
	assign state_data_out[23:16]   = state_data_in[87:80];
	assign state_data_out[87:80]   = state_data_in[23:16];
	assign state_data_out[55:48]   = state_data_in[119:112];
	assign state_data_out[119:112] = state_data_in[55:48];

	// row 3
	assign state_data_out[31:24]   = state_data_in[127:120];
	assign state_data_out[127:120] = state_data_in[95:88];
	assign state_data_out[95:88]   = state_data_in[63:56];
	assign state_data_out[63:56]   = state_data_in[31:24];

endmodule



