# FPGA-based Real-Time Implementation of AES Algorithm for Encryption & Decryption

# Description

# How to use
To use this project: <br />
 1. Clone this repository. <br />
 2. Add AES_CTR_1.0 to the IP repository (using vivado repository manager).<br />
 3. Open hdmi.xpr project in vivado. <br />
 4. Run systhesis, implementation, and generate bitstream. <br />
 5. Connect to a Nexys Video board. <br />
 6. Launch SDK tool in vivado. <br />
 7. Program FPGA and run video_demo.c. <br >

# Repository structure
* src/proj: main hdmi.xpr project
* src/repo/AES_CTR_1.0: the AXI stream IP contains AES encrytion and decrytion modules

* src/proj/hdmi.sdk
   * demo/src
    * video_demo.c: main file contains all the functions to run the design
    * video_demo.h:
   * vdma
      * vdma.c: All the functions to configure the second vdma read and write channels, as well as read, write, parking and reset.
      * vdma.h
* docs: contains group final report and slides for final presentations.
 * Group Final Report.
 * Slides.

# Authors:
 Hao Gu <br />
 Yucheng Tao <br />
 Shan Liu <br />

# Acknowledgements:
The design is based on existed Nexys Video HDMI Demo project.
