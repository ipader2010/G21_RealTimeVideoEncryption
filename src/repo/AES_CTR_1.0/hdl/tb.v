`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/25/2017 01:20:47 AM
// Design Name: 
// Module Name: tb
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


module tb();

    reg clk, resetn;

    wire [2:0] m00_axis_tkeep;
    wire m00_axis_tuser;

    wire  m00_axis_tvalid;
    wire [23 : 0] m00_axis_tdata;

    wire  m00_axis_tlast;
    reg  m00_axis_tready;


    wire  s00_axis_tready;
    reg [23 : 0] s00_axis_tdata;

    reg  s00_axis_tlast;
    reg  s00_axis_tvalid;

    AES_CTR_v1_0 #
    (

        .H_RESOLUTION(1920),
        .V_RESOLUTION(1080),

        .C_M00_AXIS_TDATA_WIDTH(24),
        .C_M00_AXIS_START_COUNT(24),


        .C_S00_AXIS_TDATA_WIDTH(24)
    ) AES_CTR_v1_0_M00_AXIS_inst
    (
        
        .m00_axis_tkeep(m00_axis_tkeep),
        .m00_axis_tuser(m00_axis_tuser),

        .m00_axis_aclk(clk),
        .m00_axis_aresetn(resetn),
        .m00_axis_tvalid(m00_axis_tvalid),
        .m00_axis_tdata(m00_axis_tdata),

        .m00_axis_tlast(m00_axis_tlast),
        .m00_axis_tready(m00_axis_tready),


        .s00_axis_aclk(clk),
        .s00_axis_aresetn(resetn),
        .s00_axis_tready(s00_axis_tready),
        .s00_axis_tdata(s00_axis_tdata),

        .s00_axis_tlast(s00_axis_tlast),
        .s00_axis_tvalid(s00_axis_tvalid)
    );



    initial begin
        clk = 0;
        resetn = 0;
        s00_axis_tdata = 0;
        s00_axis_tvalid = 0;
        s00_axis_tlast = 0;
        m00_axis_tready = 1;
    end

    always
        #5  clk = ~clk;

    initial begin
        #10     resetn = 1;
        #100    s00_axis_tdata = 24'hfff0;
                s00_axis_tvalid = 1;
        #19210
                s00_axis_tvalid = 0;
                s00_axis_tdata = 24'hf000;

//        #1000    s00_axis_tdata = 24'hf0f0;
//                s00_axis_tvalid = 1;
        // #20 s00_axis_tdata = 24'hfff0;
        //         s00_axis_tvalid = 1;
        // #20 s00_axis_tdata = 24'hff0f;
        //         s00_axis_tvalid = 1;
        // #20 s00_axis_tdata = 24'hf0ff;
        //         s00_axis_tvalid = 1;
    end

endmodule
