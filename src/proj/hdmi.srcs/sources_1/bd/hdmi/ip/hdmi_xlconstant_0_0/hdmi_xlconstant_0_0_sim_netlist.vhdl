-- Copyright 1986-2016 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2016.2 (win64) Build 1577090 Thu Jun  2 16:32:40 MDT 2016
-- Date        : Tue Mar 28 23:29:41 2017
-- Host        : DESKTOP-IKIAB7U running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim
--               F:/G9_AES/G9_InteractiveStudio-master/src/proj/hdmi.srcs/sources_1/bd/hdmi/ip/hdmi_xlconstant_0_0/hdmi_xlconstant_0_0_sim_netlist.vhdl
-- Design      : hdmi_xlconstant_0_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xc7a200tsbg484-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity hdmi_xlconstant_0_0 is
  port (
    dout : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of hdmi_xlconstant_0_0 : entity is true;
  attribute downgradeipidentifiedwarnings : string;
  attribute downgradeipidentifiedwarnings of hdmi_xlconstant_0_0 : entity is "yes";
end hdmi_xlconstant_0_0;

architecture STRUCTURE of hdmi_xlconstant_0_0 is
  signal \<const1>\ : STD_LOGIC;
begin
  dout(0) <= \<const1>\;
VCC: unisim.vcomponents.VCC
     port map (
      P => \<const1>\
    );
end STRUCTURE;
