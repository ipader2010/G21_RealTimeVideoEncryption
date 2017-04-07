-- Copyright 1986-2016 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2016.2 (win64) Build 1577090 Thu Jun  2 16:32:40 MDT 2016
-- Date        : Tue Mar 28 23:29:41 2017
-- Host        : DESKTOP-IKIAB7U running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               F:/G9_AES/G9_InteractiveStudio-master/src/proj/hdmi.srcs/sources_1/bd/hdmi/ip/hdmi_xlconstant_0_0/hdmi_xlconstant_0_0_stub.vhdl
-- Design      : hdmi_xlconstant_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7a200tsbg484-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity hdmi_xlconstant_0_0 is
  Port ( 
    dout : out STD_LOGIC_VECTOR ( 0 to 0 )
  );

end hdmi_xlconstant_0_0;

architecture stub of hdmi_xlconstant_0_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "dout[0:0]";
begin
end;
