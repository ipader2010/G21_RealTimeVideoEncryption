`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 03/20/2017 02:46:42 PM
// Design Name:
// Module Name: fsm_top
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


module fsm_aes(
    input wire clk,
    input wire resetn,
    input wire enable,
    output wire start,
    output wire write,
    output wire done
    );

    parameter [2:0] S_Reset  = 3'd0,
                    S_Data     = 3'd1,
                    S_Wait     = 3'd2,
                    S_Write    = 3'd3,
                    S_Done     = 3'd4;


    reg [2:0] PS, NS;
    reg [3:0] wait_cnt;

    assign start = (PS == S_Data);
    assign write = (PS == S_Write);
    assign done = (PS == S_Done);

    //Synchrnou state transition block
    always@(posedge clk) begin
        if (!resetn)
          PS <= S_Reset;
        else
          PS <= NS;
    end

    //Conditional state transition block
    always@(*) begin
      NS = PS;
      case (PS)
        S_Reset: begin
          if (enable)
            NS = S_Data;
        end
        S_Data:  begin
          NS = S_Wait;
        end
        S_Wait:  begin
          //if (wait_cnt >= 4'd15)
            NS = S_Write;
        end
        S_Write: begin
            NS = S_Done;
        end
        S_Done:  begin
           NS = S_Reset;
        end
        default: NS = S_Reset;
      endcase
    end
    /*
    always@(posedge clk) begin
      if (!resetn)
        wait_cnt <= 4'd0;
      else if (wait_cnt >= 4'd15)
        wait_cnt <= 4'd0;
      else
        wait_cnt <= wait_cnt + 1'b1;
    end
    */


endmodule
