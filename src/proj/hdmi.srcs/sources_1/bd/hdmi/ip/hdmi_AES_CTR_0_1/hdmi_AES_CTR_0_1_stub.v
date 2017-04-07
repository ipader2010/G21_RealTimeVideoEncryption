// Copyright 1986-2016 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2016.2 (win64) Build 1577090 Thu Jun  2 16:32:40 MDT 2016
// Date        : Wed Mar 29 11:44:25 2017
// Host        : DESKTOP-IKIAB7U running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               f:/G9_AES/G9_InteractiveStudio-master/src/proj/hdmi.srcs/sources_1/bd/hdmi/ip/hdmi_AES_CTR_0_1/hdmi_AES_CTR_0_1_stub.v
// Design      : hdmi_AES_CTR_0_1
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a200tsbg484-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "AES_CTR_v1_0,Vivado 2016.2" *)
module hdmi_AES_CTR_0_1(m00_axis_tkeep, m00_axis_tuser, s00_axis_tdata, s00_axis_tlast, s00_axis_tvalid, s00_axis_tready, s00_axis_aclk, s00_axis_aresetn, m00_axis_tdata, m00_axis_tlast, m00_axis_tvalid, m00_axis_tready, m00_axis_aclk, m00_axis_aresetn)
/* synthesis syn_black_box black_box_pad_pin="m00_axis_tkeep[2:0],m00_axis_tuser[0:0],s00_axis_tdata[23:0],s00_axis_tlast,s00_axis_tvalid,s00_axis_tready,s00_axis_aclk,s00_axis_aresetn,m00_axis_tdata[23:0],m00_axis_tlast,m00_axis_tvalid,m00_axis_tready,m00_axis_aclk,m00_axis_aresetn" */;
  output [2:0]m00_axis_tkeep;
  output [0:0]m00_axis_tuser;
  input [23:0]s00_axis_tdata;
  input s00_axis_tlast;
  input s00_axis_tvalid;
  output s00_axis_tready;
  input s00_axis_aclk;
  input s00_axis_aresetn;
  output [23:0]m00_axis_tdata;
  output m00_axis_tlast;
  output m00_axis_tvalid;
  input m00_axis_tready;
  input m00_axis_aclk;
  input m00_axis_aresetn;
endmodule
