/************************************************************************/
/*																		*/
/*	video_demo.c	--	ZYBO Video demonstration 						*/
/*																		*/
/************************************************************************/
/*	Author: Sam Bobrowicz												*/
/*	Copyright 2015, Digilent Inc.										*/
/************************************************************************/
/*  Module Description: 												*/
/*																		*/
/*		This file contains code for running a demonstration of the		*/
/*		Video input and output capabilities on the ZYBO. It is a good	*/
/*		example of how to properly use the display_ctrl and				*/
/*		video_capture drivers.											*/
/*																		*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/* 																		*/
/*		11/25/2015(SamB): Created										*/
/*																		*/
/************************************************************************/


/* ------------------------------------------------------------ */
/*				Include File Definitions						*/
/* ------------------------------------------------------------ */
#include "video_demo.h"
#include "video_capture/video_capture.h"
#include "display_ctrl/display_ctrl.h"
#include "intc/intc.h"
#include "vdma/vdma.h"
#include "vdma/constants.h"
#include <stdio.h>
#include "xuartlite_l.h"
#include "math.h"
#include <ctype.h>
#include <stdlib.h>
#include "xil_types.h"
#include "xil_cache.h"
#include "xparameters.h"
#include "xuartlite_l.h"
#include "aes.h"


/*
* XPAR redefines
*/
#define DYNCLK_BASEADDR XPAR_AXI_DYNCLK_0_BASEADDR
#define VGA_VDMA_ID XPAR_AXIVDMA_0_DEVICE_ID
#define VGA_VDMA_ID_1 XPAR_AXIVDMA_1_DEVICE_ID
#define DISP_VTC_ID XPAR_VTC_0_DEVICE_ID
#define VID_VTC_ID XPAR_VTC_1_DEVICE_ID
#define VID_GPIO_ID XPAR_AXI_GPIO_VIDEO_DEVICE_ID
#define VID_VTC_IRPT_ID XPAR_INTC_0_VTC_1_VEC_ID
#define VID_GPIO_IRPT_ID XPAR_INTC_0_GPIO_0_VEC_ID
#define SCU_TIMER_ID XPAR_AXI_TIMER_0_DEVICE_ID
#define UART_BASEADDR XPAR_UARTLITE_0_BASEADDR

#define COLOR_TO_IP_AXI_BASEADDR 0x44a50000

#define    MEM_BASE_ADDR         0x10000000
#define    READ_ADDRESS_BASE	 MEM_BASE_ADDR
#define    WRITE_ADDRESS_BASE	 MEM_BASE_ADDR
#define    OFFSET                1920*3
/* ------------------------------------------------------------ */
/*				Global Variables								*/
/* ------------------------------------------------------------ */

/*
* Display and Video Driver structs
*/

DisplayCtrl dispCtrl;
XAxiVdma vdma;
XAxiVdma vdma_1;
XAxiVdma_Config *vdma_1_Config;
static XAxiVdma_DmaSetup vdmaConfig_1; /*VDMA_1 read channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_2; /*VDMA_1 write channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_3; /*VDMA_1 read channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_4; /*VDMA_1 write channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_5; /*VDMA_1 read channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_6; /*VDMA_1 write channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_7; /*VDMA_1 read channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_8; /*VDMA_1 write channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_9; /*VDMA_1 read channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_a; /*VDMA_1 write channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_b; /*VDMA_1 read channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_c; /*VDMA_1 write channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_d; /*VDMA_1 read channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_e; /*VDMA_1 write channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_f; /*VDMA_1 read channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_g; /*VDMA_1 write channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_h; /*VDMA_1 read channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_i; /*VDMA_1 write channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_j; /*VDMA_1 read channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_k; /*VDMA_1 write channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_l; /*VDMA_1 read channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_m; /*VDMA_1 write channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_n; /*VDMA_1 read channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_o; /*VDMA_1 write channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_p; /*VDMA_1 read channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_q; /*VDMA_1 write channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_r; /*VDMA_1 read channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_s; /*VDMA_1 write channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_t; /*VDMA_1 read channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_u; /*VDMA_1 write channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_v; /*VDMA_1 read channel configuration*/
static XAxiVdma_DmaSetup vdmaConfig_w; /*VDMA_1 write channel configuration*/


static XAxiVdma_FrameCounter frame_count_config_1;
static XAxiVdma_FrameCounter frame_count_config_2;
static XAxiVdma_FrameCounter frame_count_config_3;
static XAxiVdma_FrameCounter frame_count_config_4;
static XAxiVdma_FrameCounter frame_count_config_5;
static XAxiVdma_FrameCounter frame_count_config_6;
static XAxiVdma_FrameCounter frame_count_config_7;
static XAxiVdma_FrameCounter frame_count_config_8;
static XAxiVdma_FrameCounter frame_count_config_9;
static XAxiVdma_FrameCounter frame_count_config_a;
static XAxiVdma_FrameCounter frame_count_config_b;
static XAxiVdma_FrameCounter frame_count_config_c;
static XAxiVdma_FrameCounter frame_count_config_d;
static XAxiVdma_FrameCounter frame_count_config_e;
static XAxiVdma_FrameCounter frame_count_config_f;
static XAxiVdma_FrameCounter frame_count_config_g;
static XAxiVdma_FrameCounter frame_count_config_h;
static XAxiVdma_FrameCounter frame_count_config_i;
static XAxiVdma_FrameCounter frame_count_config_j;
static XAxiVdma_FrameCounter frame_count_config_k;
static XAxiVdma_FrameCounter frame_count_config_l;
static XAxiVdma_FrameCounter frame_count_config_m;
static XAxiVdma_FrameCounter frame_count_config_n;
static XAxiVdma_FrameCounter frame_count_config_o;
static XAxiVdma_FrameCounter frame_count_config_p;
static XAxiVdma_FrameCounter frame_count_config_q;
static XAxiVdma_FrameCounter frame_count_config_r;
static XAxiVdma_FrameCounter frame_count_config_s;
static XAxiVdma_FrameCounter frame_count_config_t;
static XAxiVdma_FrameCounter frame_count_config_u;
static XAxiVdma_FrameCounter frame_count_config_v;
static XAxiVdma_FrameCounter frame_count_config_w;


VideoCapture videoCapt;
INTC intc;
char fRefresh; //flag used to trigger a refresh of the Menu on video detect

/*
* Framebuffers for video data
*/
u8 frameBuf[DISPLAY_NUM_FRAMES][DEMO_MAX_FRAME];
u8 *pFrames[DISPLAY_NUM_FRAMES]; //array of pointers to the frame buffers



/*
* Interrupt vector table
*/
const ivt_t ivt[] = {
     videoGpioIvt(VID_GPIO_IRPT_ID, &videoCapt),
     videoVtcIvt(VID_VTC_IRPT_ID, &(videoCapt.vtc))
};

/* ------------------------------------------------------------ */
/*				Procedure Definitions							*/
/* ------------------------------------------------------------ */

// Pointer to the external memory
volatile  u8 * memptr  = (u8*)0x90000000;
volatile  u8 * memptr2 = (u8*)0x91000000;
volatile  u8 * memptr3  = (u8*)0x92000000;

void initialize_vdma_1()
{

	int Status;
	 vdma_1_Config = XAxiVdma_LookupConfig(VGA_VDMA_ID_1);
	 if (!vdma_1_Config)
	 {
		  xil_printf("No video DMA found for ID %d\r\n", VGA_VDMA_ID_1);
		  return;
	 }

	 Status = XAxiVdma_CfgInitialize(&vdma_1, vdma_1_Config, vdma_1_Config->BaseAddress);
	 if (Status != XST_SUCCESS)
	 {
		  xil_printf("VDMA Configuration Initialization failed %d\r\n", Status);
		  return;
	 }

}


int main(void)
{
     DemoInitialize();
     DemoRun();
     return 0;
}

void DemoInitialize()

{
     int Status;
     XAxiVdma_Config *vdmaConfig;
     xil_printf("\nstart\r\n");

     /*
     * Initialize an array of pointers to the 3 frame buffers
     */

     pFrames[0] = frameBuf[0];  // Original frame
     pFrames[1] = frameBuf[1];  // encryption frame
     pFrames[2] = frameBuf[2];  // decryption frame

     /*
     * Initialize VDMA driver
     */

     vdmaConfig = XAxiVdma_LookupConfig(VGA_VDMA_ID);
     if (!vdmaConfig)
     {
          xil_printf("No video DMA found for ID %d\r\n", VGA_VDMA_ID);
          return;
     }

     Status = XAxiVdma_CfgInitialize(&vdma, vdmaConfig, vdmaConfig->BaseAddress);
     if (Status != XST_SUCCESS)
     {
          xil_printf("VDMA Configuration Initialization failed %d\r\n", Status);
          return;
     }

     /*
     * Initialize the Display controller and start it
     */
     Status = DisplayInitialize(&dispCtrl, &vdma, DISP_VTC_ID, DYNCLK_BASEADDR, pFrames, DEMO_STRIDE);
     if (Status != XST_SUCCESS)
     {
          xil_printf("Display Ctrl initialization failed during demo initialization%d\r\n", Status);
          return;
     }

     Status = DisplayStart(&dispCtrl);
     if (Status != XST_SUCCESS)
     {
          xil_printf("Couldn't start display during demo initialization%d\r\n", Status);
          return;
     }

     /*
     * Initialize the Interrupt controller and start it.
     */
     Status = fnInitInterruptController(&intc);
     if (Status != XST_SUCCESS) {
          xil_printf("Error initializing interrupts");
          return;
     }
     fnEnableInterrupts(&intc, &ivt[0], sizeof(ivt) / sizeof(ivt[0]));

     /*
     * Initialize the Video Capture device
     */
     Status = VideoInitialize(&videoCapt, &intc, &vdma, VID_GPIO_ID, VID_VTC_ID, VID_VTC_IRPT_ID, pFrames, DEMO_STRIDE, DEMO_START_ON_DET);
     if (Status != XST_SUCCESS)
     {
          xil_printf("Video Ctrl initialization failed during demo initialization%d\r\n", Status);
          return;
     }

     /*
     * Set the Video Detect callback to trigger the menu to reset, displaying the new detected resolution
     */
     VideoSetCallback(&videoCapt, DemoISR, &fRefresh);
     DemoPrintTest(dispCtrl.framePtr[dispCtrl.curFrame], dispCtrl.vMode.width, dispCtrl.vMode.height, dispCtrl.stride, DEMO_PATTERN_1);

     return;
}

void DemoRun()
{
	int nextFrame = 0;
	int Status;
	char userInput = 0;
	int i;
	u32 locked;
	XGpio *GpioPtr = &videoCapt.gpio;

	DisplayStop(&dispCtrl);
	DisplaySetMode(&dispCtrl, &VMODE_1920x1080);
	DisplayStart(&dispCtrl);

	/* Flush UART FIFO */
	while (!XUartLite_IsReceiveEmpty(UART_BASEADDR))
	{
		XUartLite_ReadReg(UART_BASEADDR, XUL_RX_FIFO_OFFSET);
	}
	while (userInput != 'q')
	{
		fRefresh = 0;
		DemoPrintMenu();

		/* Wait for data on UART */
		while (XUartLite_IsReceiveEmpty(UART_BASEADDR) && !fRefresh)
		{}

		/* Store the first character in the UART receive FIFO and echo it */
		if (!XUartLite_IsReceiveEmpty(UART_BASEADDR))
		{
			userInput = XUartLite_ReadReg(UART_BASEADDR, XUL_RX_FIFO_OFFSET);
			xil_printf("%c", userInput);
		}
		else  //Refresh triggered by video detect interrupt
		{
			userInput = 'r';
		}

		switch (userInput)
		{
		case '1':
			DemoChangeRes();
			break;
		case '2':
			nextFrame = dispCtrl.curFrame + 1;
			if (nextFrame >= DISPLAY_NUM_FRAMES)
			{
				nextFrame = 0;
			}
			DisplayChangeFrame(&dispCtrl, nextFrame);
			break;
		case '3':
			DemoPrintTest(pFrames[dispCtrl.curFrame], dispCtrl.vMode.width, dispCtrl.vMode.height, DEMO_STRIDE, DEMO_PATTERN_0);
			break;
		case '4':
			DemoPrintTest(pFrames[dispCtrl.curFrame], dispCtrl.vMode.width, dispCtrl.vMode.height, DEMO_STRIDE, DEMO_PATTERN_1);
			break;
		case '5':
			if (videoCapt.state == VIDEO_STREAMING)
				VideoStop(&videoCapt);
			else
				VideoStart(&videoCapt);
			break;
		case '6':
			nextFrame = videoCapt.curFrame + 1;
			if (nextFrame >= DISPLAY_NUM_FRAMES)
			{
				nextFrame = 0;
			}
			VideoChangeFrame(&videoCapt, nextFrame);
			break;
		case '8':
			aes_core();
			break;
		case 'r':
			locked = XGpio_DiscreteRead(GpioPtr, 2);
			xil_printf("%d", locked);
			break;
		default :
			xil_printf("\n\rInvalid Selection");
			MB_Sleep(50);
		}
	}
	return;
}

void aes_core()
{

		char userInput;
		initialize_vdma_1(); //cfgInitialize
		int ind = 0;
		int ind1 = 0;
		parking_read(&vdma, 1);

		write_config(&vdma_1, &vdmaConfig_2, &frame_count_config_2);
		read_config(&vdma_1, &vdmaConfig_1, &frame_count_config_1);
		write_config(&vdma_1, &vdmaConfig_4, &frame_count_config_4);
		read_config(&vdma_1, &vdmaConfig_3, &frame_count_config_3);
		write_config(&vdma_1, &vdmaConfig_6, &frame_count_config_6);
		read_config(&vdma_1, &vdmaConfig_5, &frame_count_config_5);
		write_config(&vdma_1, &vdmaConfig_8, &frame_count_config_8);
		read_config(&vdma_1, &vdmaConfig_7, &frame_count_config_7);
		write_config(&vdma_1, &vdmaConfig_a, &frame_count_config_a);
		read_config(&vdma_1, &vdmaConfig_9, &frame_count_config_9);
		write_config(&vdma_1, &vdmaConfig_c, &frame_count_config_c);
		read_config(&vdma_1, &vdmaConfig_b, &frame_count_config_b);
		write_config(&vdma_1, &vdmaConfig_e, &frame_count_config_e);
		read_config(&vdma_1, &vdmaConfig_d, &frame_count_config_d);
		write_config(&vdma_1, &vdmaConfig_g, &frame_count_config_g);
		read_config(&vdma_1, &vdmaConfig_f, &frame_count_config_f);
		read_config(&vdma_1, &vdmaConfig_h, &frame_count_config_h);
		write_config(&vdma_1, &vdmaConfig_i, &frame_count_config_i);
		read_config(&vdma_1, &vdmaConfig_j, &frame_count_config_j);
		write_config(&vdma_1, &vdmaConfig_k, &frame_count_config_k);
		read_config(&vdma_1, &vdmaConfig_l, &frame_count_config_l);
		write_config(&vdma_1, &vdmaConfig_m, &frame_count_config_m);
		read_config(&vdma_1, &vdmaConfig_n, &frame_count_config_n);
		write_config(&vdma_1, &vdmaConfig_o, &frame_count_config_o);
		read_config(&vdma_1, &vdmaConfig_p, &frame_count_config_p);
		write_config(&vdma_1, &vdmaConfig_q, &frame_count_config_q);
		read_config(&vdma_1, &vdmaConfig_r, &frame_count_config_r);
		write_config(&vdma_1, &vdmaConfig_s, &frame_count_config_s);
		read_config(&vdma_1, &vdmaConfig_t, &frame_count_config_t);
		write_config(&vdma_1, &vdmaConfig_u, &frame_count_config_u);
		read_config(&vdma_1, &vdmaConfig_v, &frame_count_config_v);
		write_config(&vdma_1, &vdmaConfig_w, &frame_count_config_w);

		int Status;
		//PrintBGRow(pFrames[2], 1920, 1080);
		//PrintBG(pFrames[2], 1920, 1080, (1920 * 3));


		//XAxiVdma_StopParking(&vdma, XAXIVDMA_READ);
		//parking_read(&vdma, 1);

		u32 iPixelAddr;
		int rInd = 0;
		int rInd1 = 0;

		while(1) {

				userInput = XUartLite_ReadReg(UART_BASEADDR, XUL_RX_FIFO_OFFSET);
				if (userInput == 'e') {
					XAxiVdma_StopParking(&vdma, XAXIVDMA_READ);
					parking_read(&vdma, 1);
				}
				else if (userInput == 'd') {
					XAxiVdma_StopParking(&vdma, XAXIVDMA_READ);
					parking_read(&vdma, 2);
				}
				else if (userInput == 'o') {
					XAxiVdma_StopParking(&vdma, XAXIVDMA_READ);
					parking_read(&vdma, 0);
				}
				//encryption
				for (ind = 0; ind < LOOP; ind+=6) {

						//1
						vdmaConfig_2.FrameStoreStartAddr[0] = (u32) (pFrames[1] + ind * OFFSET_VER);
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_WRITE, vdmaConfig_2.FrameStoreStartAddr);
						XAxiVdma_StartWriteFrame(&vdma_1, &vdmaConfig_2);

						vdmaConfig_1.FrameStoreStartAddr[0] = (u32) (pFrames[0] + ind * OFFSET_VER);
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_READ, vdmaConfig_1.FrameStoreStartAddr);
						XAxiVdma_StartReadFrame(&vdma_1, &vdmaConfig_1);



						//2
						vdmaConfig_4.FrameStoreStartAddr[0] = (u32) (pFrames[1] + ((ind + 1) * OFFSET_VER));
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_WRITE, vdmaConfig_4.FrameStoreStartAddr);
						XAxiVdma_StartWriteFrame(&vdma_1, &vdmaConfig_4);

						vdmaConfig_3.FrameStoreStartAddr[0] = (u32) (pFrames[0] + ((ind + 1) * OFFSET_VER));
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_READ, vdmaConfig_3.FrameStoreStartAddr);
						XAxiVdma_StartReadFrame(&vdma_1, &vdmaConfig_3);



						//3
						vdmaConfig_6.FrameStoreStartAddr[0] = (u32) (pFrames[1] + ((ind + 2) * OFFSET_VER));
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_WRITE, vdmaConfig_6.FrameStoreStartAddr);
						XAxiVdma_StartWriteFrame(&vdma_1, &vdmaConfig_6);

						vdmaConfig_5.FrameStoreStartAddr[0] = (u32) (pFrames[0] + ((ind + 2) * OFFSET_VER));
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_READ, vdmaConfig_5.FrameStoreStartAddr);
						XAxiVdma_StartReadFrame(&vdma_1, &vdmaConfig_5);

						//4
						vdmaConfig_8.FrameStoreStartAddr[0] = (u32) (pFrames[1] + ((ind + 3) * OFFSET_VER));
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_WRITE, vdmaConfig_8.FrameStoreStartAddr);
						XAxiVdma_StartWriteFrame(&vdma_1, &vdmaConfig_8);

						vdmaConfig_7.FrameStoreStartAddr[0] = (u32) (pFrames[0] + ((ind + 3) * OFFSET_VER));
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_READ, vdmaConfig_7.FrameStoreStartAddr);
						XAxiVdma_StartReadFrame(&vdma_1, &vdmaConfig_7);


						//5
						vdmaConfig_a.FrameStoreStartAddr[0] = (u32) (pFrames[1] + ((ind + 4) * OFFSET_VER));
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_WRITE, vdmaConfig_a.FrameStoreStartAddr);
						XAxiVdma_StartWriteFrame(&vdma_1, &vdmaConfig_a);

						vdmaConfig_9.FrameStoreStartAddr[0] = (u32) (pFrames[0] + ((ind + 4) * OFFSET_VER));
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_READ, vdmaConfig_9.FrameStoreStartAddr);
						XAxiVdma_StartReadFrame(&vdma_1, &vdmaConfig_9);


						//6
						vdmaConfig_c.FrameStoreStartAddr[0] = (u32) (pFrames[1] + ((ind + 5) * OFFSET_VER));
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_WRITE, vdmaConfig_c.FrameStoreStartAddr);
						XAxiVdma_StartWriteFrame(&vdma_1, &vdmaConfig_c);

						vdmaConfig_b.FrameStoreStartAddr[0] = (u32) (pFrames[0] + ((ind + 5) * OFFSET_VER));
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_READ, vdmaConfig_b.FrameStoreStartAddr);
						XAxiVdma_StartReadFrame(&vdma_1, &vdmaConfig_b);



				}
				
				//decryption
				for (ind1 = 0; ind1 < LOOP; ind1+=6){


						//1
						vdmaConfig_e.FrameStoreStartAddr[0] = (u32) (pFrames[2] + ind1 * OFFSET_VER);
						Status = XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_WRITE, vdmaConfig_e.FrameStoreStartAddr);
						if (Status != XST_SUCCESS) {
							xdbg_printf(XDBG_DEBUG_ERROR,
								"Setting buffer addr vmcg4 "
								"failed with %d\r\n", Status);
						}
						Status = XAxiVdma_StartWriteFrame(&vdma_1, &vdmaConfig_e);
						if (Status != XST_SUCCESS) {
							xdbg_printf(XDBG_DEBUG_ERROR,
								"start write frame vmcg4 "
								"failed with %d\r\n", Status);
						}

						vdmaConfig_d.FrameStoreStartAddr[0] = (u32) (pFrames[1] + ind1 * OFFSET_VER);
						Status = XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_READ, vdmaConfig_d.FrameStoreStartAddr);
						if (Status != XST_SUCCESS) {
							xdbg_printf(XDBG_DEBUG_ERROR,
								"Setting buffer addr vmcg3"
								"failed with %d\r\n", Status);
						}
						Status = XAxiVdma_StartReadFrame(&vdma_1, &vdmaConfig_d);
						if (Status != XST_SUCCESS) {
							xdbg_printf(XDBG_DEBUG_ERROR,
								"Start read frame vmcg3 "
								"failed with %d\r\n", Status);
						}


						//2
						vdmaConfig_g.FrameStoreStartAddr[0] = (u32) (pFrames[2] + ((ind1 + 1) * OFFSET_VER));
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_WRITE, vdmaConfig_g.FrameStoreStartAddr);
						XAxiVdma_StartWriteFrame(&vdma_1, &vdmaConfig_g);

						vdmaConfig_f.FrameStoreStartAddr[0] = (u32) (pFrames[1] + ((ind1 + 1) * OFFSET_VER));
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_READ, vdmaConfig_f.FrameStoreStartAddr);
						XAxiVdma_StartReadFrame(&vdma_1, &vdmaConfig_f);


						//3
						vdmaConfig_i.FrameStoreStartAddr[0] = (u32) (pFrames[2] + ((ind1 + 2) * OFFSET_VER));
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_WRITE, vdmaConfig_i.FrameStoreStartAddr);
						XAxiVdma_StartWriteFrame(&vdma_1, &vdmaConfig_i);

						vdmaConfig_h.FrameStoreStartAddr[0] = (u32) (pFrames[1] + ((ind1 + 2) * OFFSET_VER));
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_READ, vdmaConfig_h.FrameStoreStartAddr);
						XAxiVdma_StartReadFrame(&vdma_1, &vdmaConfig_h);


						//4
						vdmaConfig_k.FrameStoreStartAddr[0] = (u32) (pFrames[2] + ((ind1 + 3) * OFFSET_VER));
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_WRITE, vdmaConfig_k.FrameStoreStartAddr);
						XAxiVdma_StartWriteFrame(&vdma_1, &vdmaConfig_k);

						vdmaConfig_j.FrameStoreStartAddr[0] = (u32) (pFrames[1] + ((ind1 + 3) * OFFSET_VER));
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_READ, vdmaConfig_j.FrameStoreStartAddr);
						XAxiVdma_StartReadFrame(&vdma_1, &vdmaConfig_j);



						//5
						vdmaConfig_m.FrameStoreStartAddr[0] = (u32) (pFrames[2] + ((ind1 + 4) * OFFSET_VER));
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_WRITE, vdmaConfig_m.FrameStoreStartAddr);
						XAxiVdma_StartWriteFrame(&vdma_1, &vdmaConfig_m);

						vdmaConfig_l.FrameStoreStartAddr[0] = (u32) (pFrames[1] + ((ind1 + 4) * OFFSET_VER));
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_READ, vdmaConfig_l.FrameStoreStartAddr);
						XAxiVdma_StartReadFrame(&vdma_1, &vdmaConfig_l);



						//6
						vdmaConfig_o.FrameStoreStartAddr[0] = (u32) (pFrames[2] + ((ind1 + 5) * OFFSET_VER));
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_WRITE, vdmaConfig_o.FrameStoreStartAddr);
						XAxiVdma_StartWriteFrame(&vdma_1, &vdmaConfig_o);

						vdmaConfig_n.FrameStoreStartAddr[0] = (u32) (pFrames[1] + ((ind1 + 5) * OFFSET_VER));
						XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_READ, vdmaConfig_n.FrameStoreStartAddr);
						XAxiVdma_StartReadFrame(&vdma_1, &vdmaConfig_n);




				}

		}				
		//XAxiVdma_StopParking(&vdma, XAXIVDMA_READ);
		//parking_read(&vdma, 2);
		ind = 0;
		xil_printf("decryption done");
		while(1);
}


void DemoPrintMenu()
{
	xil_printf("\x1B[H"); //Set cursor to top left of terminal
	xil_printf("\x1B[2J"); //Clear terminal
	xil_printf("**************************************************\n\r");
	xil_printf("*                ZYBO Video Demo                 *\n\r");
	xil_printf("**************************************************\n\r");
	xil_printf("*Display Resolution: %28s*\n\r", dispCtrl.vMode.label);
//	printf("*Display Pixel Clock Freq. (MHz): %15.3f*\n\r", dispCtrl.pxlFreq);
	xil_printf("*Display Frame Index: %27d*\n\r", dispCtrl.curFrame);
	if (videoCapt.state == VIDEO_DISCONNECTED) xil_printf("*Video Capture Resolution: %22s*\n\r", "!HDMI UNPLUGGED!");
	else xil_printf("*Video Capture Resolution: %17dx%-4d*\n\r", videoCapt.timing.HActiveVideo, videoCapt.timing.VActiveVideo);
	xil_printf("*Video Frame Index: %29d*\n\r", videoCapt.curFrame);
	xil_printf("**************************************************\n\r");
	xil_printf("\n\r");
	xil_printf("1 - Change Display Resolution\n\r");
	xil_printf("2 - Change Display Framebuffer Index\n\r");
	xil_printf("4 - Print Color Bar Test Pattern to Display Framebuffer\n\r");
	xil_printf("5 - Start/Stop Video stream into Video Framebuffer\n\r");
	xil_printf("6 - Change Video Framebuffer Index\n\r");
	xil_printf("8 - AES Encryption In CTR Mode\n\r");
	xil_printf("q - Quit\n\r");
	xil_printf("\n\r");
	xil_printf("\n\r");
	xil_printf("Enter a selection:");
}

void DemoChangeRes()
{
	int fResSet = 0;
	int status;
	char userInput = 0;

	/* Flush UART FIFO */
	while (!XUartLite_IsReceiveEmpty(UART_BASEADDR))
		{
			XUartLite_ReadReg(UART_BASEADDR, XUL_RX_FIFO_OFFSET);
		}

	while (!fResSet)
	{
		DemoCRMenu();

		/* Wait for data on UART */
		while (XUartLite_IsReceiveEmpty(UART_BASEADDR) && !fRefresh)
		{}

		/* Store the first character in the UART recieve FIFO and echo it */

		userInput = XUartLite_ReadReg(UART_BASEADDR, XUL_RX_FIFO_OFFSET);
		xil_printf("%c", userInput);
		status = XST_SUCCESS;
		switch (userInput)
		{
		case '1':
			status = DisplayStop(&dispCtrl);
			DisplaySetMode(&dispCtrl, &VMODE_640x480);
			DisplayStart(&dispCtrl);
			fResSet = 1;
			break;
		case '2':
			status = DisplayStop(&dispCtrl);
			DisplaySetMode(&dispCtrl, &VMODE_800x600);
			DisplayStart(&dispCtrl);
			fResSet = 1;
			break;
		case '3':
			status = DisplayStop(&dispCtrl);
			DisplaySetMode(&dispCtrl, &VMODE_1280x720);
			DisplayStart(&dispCtrl);
			fResSet = 1;
			break;
		case '4':
			status = DisplayStop(&dispCtrl);
			DisplaySetMode(&dispCtrl, &VMODE_1280x1024);
			DisplayStart(&dispCtrl);
			fResSet = 1;
			break;
		case '5':
			status = DisplayStop(&dispCtrl);
			DisplaySetMode(&dispCtrl, &VMODE_1920x1080);
			DisplayStart(&dispCtrl);
			fResSet = 1;
			break;
		case 'q':
			fResSet = 1;
			break;
		default :
			xil_printf("\n\rInvalid Selection");
			MB_Sleep(50);
		}
		if (status == XST_DMA_ERROR)
		{
			xil_printf("\n\rWARNING: AXI VDMA Error detected and cleared\n\r");
		}
	}
}

void DemoCRMenu()
{
	xil_printf("\x1B[H"); //Set cursor to top left of terminal
	xil_printf("\x1B[2J"); //Clear terminal
	xil_printf("**************************************************\n\r");
	xil_printf("*                ZYBO Video Demo                 *\n\r");
	xil_printf("**************************************************\n\r");
	xil_printf("*Current Resolution: %28s*\n\r", dispCtrl.vMode.label);
//	printf("*Pixel Clock Freq. (MHz): %23.3f*\n\r", dispCtrl.pxlFreq);
	xil_printf("**************************************************\n\r");
	xil_printf("\n\r");
	xil_printf("1 - %s\n\r", VMODE_640x480.label);
	xil_printf("2 - %s\n\r", VMODE_800x600.label);
	xil_printf("3 - %s\n\r", VMODE_1280x720.label);
	xil_printf("4 - %s\n\r", VMODE_1280x1024.label);
	xil_printf("5 - %s\n\r", VMODE_1920x1080.label);
	xil_printf("q - Quit (don't change resolution)\n\r");
	xil_printf("\n\r");
	xil_printf("Select a new resolution:");
}


void PrintRed(u8 *frame, u32 xcoi, u32 ycoi)
{
    u32 iPixelAddr;
    u8 wRed, wBlue, wGreen;
    int i;
    wRed = 0;
    wBlue = 0;
    wGreen = 0;
    iPixelAddr = 1920*ycoi*3 + xcoi*3;
    u32 iPixelAddr2 = iPixelAddr;

    int radius = 10;
    int y, x;

    int counter = 0;

    //Draw closed Pacman
	for(y = -radius; y<= radius; y++){
		for (x = -radius; x<=radius; x++){
			if(x*x + y*y <= radius * radius){
				frame[iPixelAddr] = wRed+255;
				frame[iPixelAddr + 1] = wBlue;
				frame[iPixelAddr + 2] = wGreen+255;
				iPixelAddr = 1920*(ycoi+y)*3 + (xcoi+x)*3;
			}
		}
	}
	counter++;

    iPixelAddr = 0;
}


void DemoPrintTest(u8 *frame, u32 width, u32 height, u32 stride, int pattern)
{
	u32 xcoi, ycoi;
	u32 iPixelAddr;
	u8 wRed, wBlue, wGreen;
	u32 wCurrentInt;
	double fRed, fBlue, fGreen, fColor;
	u32 xLeft, xMid, xRight, xInt;
	u32 yMid, yInt;
	double xInc, yInc;


	switch (pattern)
	{
	case DEMO_PATTERN_0:
	case DEMO_PATTERN_1:

		xInt = width / 7; //Seven intervals, each with width/7 pixels
		xInc = 256.0 / ((double) xInt); //256 color intensities per interval. Notice that overflow is handled for this pattern.

		fColor = 0.0;
		wCurrentInt = 1;
		for(xcoi = 0; xcoi < (width*3); xcoi+=3)
		{

			/*
			 * Just draw white in the last partial interval (when width is not divisible by 7)
			 */
			if (wCurrentInt > 7)
			{
				wRed = 255;
				wBlue = 255;
				wGreen = 255;
			}
			else
			{
				if (wCurrentInt & 0b001)
					wRed = (u8) fColor;
				else
					wRed = 0;

				if (wCurrentInt & 0b010)
					wBlue = (u8) fColor;
				else
					wBlue = 0;

				if (wCurrentInt & 0b100)
					wGreen = (u8) fColor;
				else
					wGreen = 0;
			}

			iPixelAddr = xcoi;

			for(ycoi = 0; ycoi < height; ycoi++)
			{
				frame[iPixelAddr] = wRed;
				frame[iPixelAddr + 1] = wBlue;
				frame[iPixelAddr + 2] = wGreen;
				/*
				 * This pattern is printed one vertical line at a time, so the address must be incremented
				 * by the stride instead of just 1.
				 */
				iPixelAddr += stride;
			}

			fColor += xInc;
			if (fColor >= 256.0)
			{
				fColor = 0.0;
				wCurrentInt++;
			}
		}
		/*
		 * Flush the framebuffer memory range to ensure changes are written to the
		 * actual memory, and therefore accessible by the VDMA.
		 */
		Xil_DCacheFlushRange((unsigned int) frame, DEMO_MAX_FRAME);
		break;
	default :
		xil_printf("Error: invalid pattern passed to DemoPrintTest");
	}
}

void DemoISR(void *callBackRef, void *pVideo)
{
	char *data = (char *) callBackRef;
	*data = 1; //set fRefresh to 1
}
