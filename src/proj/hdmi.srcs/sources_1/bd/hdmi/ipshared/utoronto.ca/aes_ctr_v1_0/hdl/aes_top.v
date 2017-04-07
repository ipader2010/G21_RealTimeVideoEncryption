`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 03/20/2017 03:22:53 PM
// Design Name:
// Module Name: aes_top
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


module aes_top(
    input wire [127:0] key_in,
    input wire [127:0] data_in,
    input wire [127:0] cnt_in,
    input wire clk,
    input wire resetn,
    input wire enable,
    output reg [127:0] data_out,
    output wire done
    );

    wire start, write;
    reg [127:0]key;
    reg [127:0]datain;
    reg [127:0]cnt;
    wire [127:0]dataout;

    fsm_aes fsm_mod(
        .clk(clk),
        .resetn(resetn),
        .enable(enable),
        .start(start),
        .write(write),
        .done(done)
    );

    Encryption  aes_en(
        .keyin(key),
        .statein(cnt),
        .datain(datain),
        .stateout(dataout)
   );
    always@(posedge clk)  begin
        if (!resetn)  begin
          key <= 128'd0;
          datain <= 128'd0;
          cnt <= 128'd0;
          data_out <= 128'd0;
        end
        else if (start) begin
          key <= key_in;
          datain <= data_in;
          cnt <= cnt_in;
        end
        else if (write) begin
            data_out <= dataout;
        end
    end

    
endmodule
