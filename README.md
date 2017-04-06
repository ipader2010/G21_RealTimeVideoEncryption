# FPGA-based Real-Time Implementation of AES Algorithm for Encryption & Decryption

#Description

#How to use
To use this project: <br />
 1. Clone this repository. <br />
 2. Add AES_CTR_1.0 to the IP repository (using vivado repository manager).<br />
 3. Open hdmi.xpr project in vivado. <br />
 4. Generate bitstream. <br />
 5. Program a Nexys Video board. <br />
 6. Run video_demo.c program from the SDK. <br >

#Repository structure
* src/proj: main hdmi.xpr project
 * repo/AES_CTR_1.0: the AXI stream IP contains AES encrytion and decrytion modules

 * hdmi.sdk
   * video_demo/src
    * video_demo.c: contains all functions to store the image, control data flow for display video after color replacement and laser        detection and animations
    * video_demo.h
   * vdma
      * vdma.c: All the functions to configure the second vdma read and write channel, in addition to operate read, write, parking and        reset.
      * vdma.h
* docs: contains group final report and slides for final presentations.
 * Group Final Report.
 * Slides.

#Authors:
Hao Gu <br />
Yucheng Tao <br />
Shan Liu <br />

#Acknowledgements:
The design is based on existed Nexys Video HDMI Demo project.
