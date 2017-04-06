# FPGA-based Real-Time Implementation of AES Algorithm for Encryption & Decryption

# Description
This is an FPGA implementation of AES-128 CTR mode real-time video encryption and decryption written in verilog and C.

# How to use
To use this project: <br/>
 1. Clone this repository. <br/>
 2. Add AES_CTR_1.0 to the IP repository (using vivado repository manager).<br/>
 3. Open hdmi.xpr project in vivado. <br/>
 4. Run systhesis, implementation, and generate bitstream. <br/>
 5. Connect to a Nexys Video board. <br/>
 6. Launch SDK tool in vivado. <br/>
 7. Program FPGA and run video_demo.c. <br/>

# Repository structure
* src/proj: main hdmi.xpr project
* src/repo/AES_CTR_1.0: the AXI stream IP contains AES encrytion and decrytion modules <br/>

* src/proj/hdmi.sdk
   * demo/src
    * video_demo.c: main file contains all the functions to run the design
    * video_demo.h:
   * vdma
      * vdma.c: All the functions to configure the second vdma read and write channels, as well as read, write, parking and reset.
      * vdma.h
* docs: contains group final report and slides for final presentations.
 * Group Final Report.
 * Final Demo Presentation.

# Authors:
 Hao Gu <br/>
 Yucheng Tao <br/>
 Shan Liu <br/>

# Acknowledgements:
The design is based on existed Nexys Video HDMI Demo project. We used some helper functions from https://github.com/marmot1234/G9_InteractiveStudio to configure the sencond vdma. The AES-CTR IP core was implemented based on https://github.com/kokke/tiny-AES128-C and was verified against the data from [National Institute of Standards and Technology Special Publication 800-38A 2001 ED](<a href="http://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38a.pdf">click here</a>) Appendix F: Example Vectors for Modes of Operation of the AES. 
