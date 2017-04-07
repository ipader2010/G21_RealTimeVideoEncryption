-- Copyright 1986-2016 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2016.2 (win64) Build 1577090 Thu Jun  2 16:32:40 MDT 2016
-- Date        : Wed Mar 29 11:44:25 2017
-- Host        : DESKTOP-IKIAB7U running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               f:/G9_AES/G9_InteractiveStudio-master/src/proj/hdmi.srcs/sources_1/bd/hdmi/ip/hdmi_AES_CTR_0_1/hdmi_AES_CTR_0_1_stub.vhdl
-- Design      : hdmi_AES_CTR_0_1
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7a200tsbg484-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity hdmi_AES_CTR_0_1 is
  Port ( 
    m00_axis_tkeep : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m00_axis_tuser : out STD_LOGIC_VECTOR ( 0 to 0 );
    s00_axis_tdata : in STD_LOGIC_VECTOR ( 23 downto 0 );
    s00_axis_tlast : in STD_LOGIC;
    s00_axis_tvalid : in STD_LOGIC;
    s00_axis_tready : out STD_LOGIC;
    s00_axis_aclk : in STD_LOGIC;
    s00_axis_aresetn : in STD_LOGIC;
    m00_axis_tdata : out STD_LOGIC_VECTOR ( 23 downto 0 );
    m00_axis_tlast : out STD_LOGIC;
    m00_axis_tvalid : out STD_LOGIC;
    m00_axis_tready : in STD_LOGIC;
    m00_axis_aclk : in STD_LOGIC;
    m00_axis_aresetn : in STD_LOGIC
  );

end hdmi_AES_CTR_0_1;

architecture stub of hdmi_AES_CTR_0_1 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "m00_axis_tkeep[2:0],m00_axis_tuser[0:0],s00_axis_tdata[23:0],s00_axis_tlast,s00_axis_tvalid,s00_axis_tready,s00_axis_aclk,s00_axis_aresetn,m00_axis_tdata[23:0],m00_axis_tlast,m00_axis_tvalid,m00_axis_tready,m00_axis_aclk,m00_axis_aresetn";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "AES_CTR_v1_0,Vivado 2016.2";
begin
end;
