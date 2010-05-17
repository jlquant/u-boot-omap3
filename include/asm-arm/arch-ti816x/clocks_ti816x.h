/*
 * (C) Copyright 2006-2008
 * Texas Instruments, <www.ti.com>
 * Richard Woodruff <r-woodruff2@ti.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR /PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#ifndef _CLOCKS_TI816X_H_
#define _CLOCKS_TI816X_H_

/* MAIN PLL */

#define MAIN_SYSCLK1_DIV	0	/* 800MHz GEM SS 	: CM_SYSCLK1_CLKSEL */
#define MAIN_SYSCLK2_DIV	0	/* 1GHz MONZA		: CM_SYSCLK2_CLKSEL */
#define MAIN_SYSCLK3_DIV	0	/* 600MHz IVA HDs	: CM_SYSCLK3_CLKSEL */
#define MAIN_SYSCLK4_DIV	0	/* 500MHz L3_FAST ETC	: CM_SYSCLK4_CLKSEL */
#define MAIN_SYSCLK7_DIV	0	/* 100MHZ VLYNQ		: CM_SYSCLK7_CLKSEL */
#define MAIN_SYSCLK23_DIV	0	/* 333MHZ SGX530	: CM_SYSCLK23_CLKSEL */
#define MAIN_SYSCLK24_DIV	0	/* 125MHZ GMII		: CM_SYSCLK24_CLKSEL */

/* THE DIVIDERS FOR SYSCLK 5,6 ARE FIXED AND CANT BE CHANGED */

/* DDR PLL */

#define DDR_SYSCLK8_DIV		0	/* 400MHZ DMM,EMIFS	: CM_SYSCLK8_CLKSEL */
#define DDR_SYSCLK9_DIV		0	/* 16MHz VTP		: CM_SYSCLK9_CLKSEL */
#define DDR_SYSCLK10_DIV	0	/* 48MHz SPI,I2C,UART	: CM_SYSCLK10_CLKSEL */
/* ROM CODE BUG: SYSCLK10_CLKSEL is taken as 1 i.e. DIV by2 giving 24Mhz and not 48Mhz.
 * The actual value has to be 0 i.e. DIV by 1 */

/* VIDEO PLL */

#define VIDEO_SYSCLK11_DIV	0	/* 218MHZ RF MOD	: CM_SYSCLK11_CLKSEL */
#define VIDEO_SYSCLK13_DIV	7	/* 165MHZ HD_VENC_D	: CM_SYSCLK13_CLKSEL */
#define VIDEO_SYSCLK15_DIV	3	/* 165MHZ HD_VENC_A	: CM_SYSCLK15_CLKSEL */
#define VIDEO_SYSCLK14_B3_DIV	2	/* STC0			: CM_VPB3_CLKSEL */
#define VIDEO_SYSCLK14_C1_DIV	3	/* STC0			: CM_VPC1_CLKSEL */
#define VIDEO_SYSCLK16_D1_DIV	7	/* STC1			: CM_VPD1_CLKSEL */
#define VIDEO_SYSCLK14_SRC	0	/* MUX FOR SYSCLK14 */

/* AUDIO PLL */

#define AUDIO_SYSCLK19_DIV	0	/* TPPSS		: CM_SYSCLK19_CLKSEL */
#define AUDIO_SYSCLK20_DIV	0	/* AUDIO CLK1		: CM_SYSCLK19_CLKSEL */
#define AUDIO_SYSCLK21_DIV	0	/* AUDIO CLK2		: CM_SYSCLK20_CLKSEL */
#define AUDIO_SYSCLK22_DIV	0	/* AUDIO CLK3		: CM_SYSCLK21_CLKSEL */
#define AUDIO_SYSCLK18_DIV	0	/* RTC			: CM_APA_CLKSEL */


/* Now the FAPLL multipler, divider, freq for the synthesizer for various PLLs needs to be given */

/* Main PLL */
#define MAIN_N_MUL		64
#define MAIN_P_DIV		1
#define MAIN_INTFREQ1		8
#define MAIN_FRACFREQ1		500 /* Will divide by 1000 while getting the net freq */
#define MAIN_M_POST_DIV1	2
#define MAIN_INTFREQ2		14
#define MAIN_FRACFREQ2		0
#define MAIN_M_POST_DIV2	1
#define MAIN_INTFREQ3		8
#define MAIN_FRACFREQ3		667
#define MAIN_M_POST_DIV3	3
#define MAIN_INTFREQ4		9
#define MAIN_FRACFREQ4		33
#define MAIN_M_POST_DIV4	3
#define MAIN_INTFREQ5		9
#define MAIN_FRACFREQ5		216
#define MAIN_M_POST_DIV5	12

#define MAIN_M_POST_DIV6	72
#define MAIN_M_POST_DIV7	4

/* DDR PLL */
#define DDR_N_MUL		59
#define DDR_P_DIV		1

#define DDR_M_POST_DIV1		1

#define DDR_INTFREQ2		8
#define DDR_FRACFREQ2		850
#define DDR_M_POST_DIV2		15	/* Note: This is diff from what is documented */
#define DDR_INTFREQ3		8
#define DDR_FRACFREQ3		0
#define DDR_M_POST_DIV3		4
#define DDR_INTFREQ4		14 /* Expansion DDR clk */
#define DDR_FRACFREQ4		0
#define DDR_M_POST_DIV4		4
#define DDR_INTFREQ5		14 /* Expansion DDR clk */
#define DDR_FRACFREQ5		0
#define DDR_M_POST_DIV5		4

/* Video PLL */
#define VIDEO_N_MUL		110
#define VIDEO_P_DIV		2
#define VIDEO_INTFREQ1		11
#define VIDEO_FRACFREQ1		0
#define VIDEO_M_POST_DIV1	5
#define VIDEO_INTFREQ2		10
#define VIDEO_FRACFREQ2		0
#define VIDEO_M_POST_DIV2	2
#define VIDEO_INTFREQ3		10
#define VIDEO_FRACFREQ3		0
#define VIDEO_M_POST_DIV3	2

/* Audio PLL */
#define AUDIO_N_MUL		64
#define AUDIO_P_DIV		25
#define AUDIO_INTFREQ2		14
#define AUDIO_FRACFREQ2		0
#define AUDIO_M_POST_DIV2	4
#define AUDIO_INTFREQ3		9
#define AUDIO_FRACFREQ3		0
#define AUDIO_M_POST_DIV3	5
#define AUDIO_INTFREQ4		9
#define AUDIO_FRACFREQ4		796
#define AUDIO_M_POST_DIV4	20
#define AUDIO_INTFREQ5		13
#define AUDIO_FRACFREQ5		500
#define AUDIO_M_POST_DIV5	20

#define DUMMY_VAL		57005 /* 0xDEAD == 57005 */

#define DDRPLL_CTRL	(0x0440 + TI816X_CTRL_BASE)
#define DDRPLL_PWD	(0x0444 + TI816X_CTRL_BASE)
#define DDRPLL_DIV2	(0x0454 + TI816X_CTRL_BASE)


#endif	/* endif _CLOCKS_TI816X_H_ */
