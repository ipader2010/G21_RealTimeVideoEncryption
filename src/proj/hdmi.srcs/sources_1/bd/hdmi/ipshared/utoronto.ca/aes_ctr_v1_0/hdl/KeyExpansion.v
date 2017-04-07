`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/08/2017 06:30:08 PM
// Design Name: 
// Module Name: KeyExpansion
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


module KeyExpansion(
    input wire [127:0]keyin,
    output wire [1407:0]roundKey
    );
    
    wire [319:0]key_in;
    wire [1279:0]key_out;
    
    assign roundKey[127:0] = keyin;
    assign roundKey[1407:128] = key_out;
    
    KeyExpSub_Byte16 keysuk0(
        .i(8'h1),
        .wordin(keyin[127:0]),
        .keyout(key_out[127:0])
    );
    
    KeyExpSub_Byte16 keysuk1(
        .i(8'h2),
        .wordin(key_out[127:0]),
        .keyout(key_out[255:128])
    );

    KeyExpSub_Byte16 keysuk2(
        .i(8'h3),
        .wordin(key_out[255:128]),
        .keyout(key_out[383:256])
    );
    
    KeyExpSub_Byte16 keysuk3(
        .i(8'h4),
        .wordin(key_out[383:256]),
        .keyout(key_out[511:384])
    );
    
    KeyExpSub_Byte16 keysuk4(
        .i(8'h5),
        .wordin(key_out[511:384]),
        .keyout(key_out[639:512])
    );
    
    KeyExpSub_Byte16 keysuk5(
        .i(8'h6),
        .wordin(key_out[639:512]),
        .keyout(key_out[767:640])
    );
    
    KeyExpSub_Byte16 keysuk6(
        .i(8'h7),
        .wordin(key_out[767:640]),
        .keyout(key_out[895:768])
    );
    
    KeyExpSub_Byte16 keysuk7(
        .i(8'h8),
        .wordin(key_out[895:768]),
        .keyout(key_out[1023:896])
    );
    
    KeyExpSub_Byte16 keysuk8(
        .i(8'h9),
        .wordin(key_out[1023:896]),
        .keyout(key_out[1151:1024])
    );   
    
    KeyExpSub_Byte16 keysuk9(
        .i(8'ha),
        .wordin(key_out[1151:1024]),
        .keyout(key_out[1279:1152])
    );
    
endmodule
