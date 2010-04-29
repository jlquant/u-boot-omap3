/*
 * (C) Copyright 2006
 * Texas Instruments, <www.ti.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 */

#ifndef _TI816X_CPU_H
#define  _TI816X_CPU_H
#include <asm/arch/hardware.h>

/* Register offsets of common modules */
/* Control */
#define CONTROL_STATUS		(TI816X_CTRL_BASE + 0x40)

/* device type */
#define DEVICE_MASK		(BIT(8) | BIT(9) | BIT(10))
#define TST_DEVICE			0x0
#define EMU_DEVICE			0x1
#define HS_DEVICE			0x2
#define GP_DEVICE			0x3

/* This gives the status of the boot mode pins on the evm
 */
#define SYSBOOT_MASK		(BIT(0) | BIT(1) | BIT(2) |BIT(3) |BIT(4))

/* Control Module */
/* Use these offsets in conjuction with Control module base address present in hardware.h */

#define MAINPLL_CONTROL			0x0400
#define MAINPLL_PWD			0x0404
#define MAINPLL_FREQ1			0x0408
#define MAINPLL_DIV1			0x040C
#define MAINPLL_FREQ2			0x0410
#define MAINPLL_DIV2			0x0414
#define MAINPLL_FREQ3			0x0418
#define MAINPLL_DIV3			0x041C
#define MAINPLL_FREQ4			0x0420
#define MAINPLL_DIV4			0x0424
#define MAINPLL_FREQ5			0x0428
#define MAINPLL_DIV5			0x042C
#define MAINPLL_DIV6			0x0434
#define MAINPLL_DIV7			0x043C

#define DDRPLL_CONTROL			0x0440
#define DDRPLL_PWD			0x0444
/* #define DDRPLL_FREQ1			0x04 */
#define DDRPLL_DIV1			0x044C
#define DDRPLL_FREQ2			0x0450
#define DDRPLL_DIV2			0x0454
#define DDRPLL_FREQ3			0x0458
#define DDRPLL_DIV3			0x045C
#define DDRPLL_FREQ4			0x0460
#define DDRPLL_DIV4			0x0464
#define DDRPLL_FREQ5			0x0468
#define DDRPLL_DIV5			0x046C


#define VIDEOPLL_CONTROL		0x0470
#define VIDEOPLL_PWD			0x0474
#define VIDEOPLL_FREQ1			0x0478
#define VIDEOPLL_DIV1			0x047C
#define VIDEOPLL_FREQ2			0x0480
#define VIDEOPLL_DIV2			0x0484
#define VIDEOPLL_FREQ3			0x0488
#define VIDEOPLL_DIV3			0x048C

#define AUDIOPLL_CONTROL		0x04A0
#define AUDIOPLL_PWD			0x04A4
/* 
#define AUDIOPLL_FREQ1			0x04
#define AUDIOPLL_DIV1			0x04
This is not be meddled with as it supplies clk to the secure wdt
Fixed at 32kHz 
 */
#define AUDIOPLL_FREQ2			0x04B0
#define AUDIOPLL_DIV2			0x04B4
#define AUDIOPLL_FREQ3			0x04B8
#define AUDIOPLL_DIV3			0x04BC
#define AUDIOPLL_FREQ4			0x04C0
#define AUDIOPLL_DIV4			0x04C4
#define AUDIOPLL_FREQ5			0x04C8
#define AUDIOPLL_DIV5			0x04CC

/* PRCM */
#define CM_DPLL_OFFSET			(TI816X_PRCM_BASE + 0x0300)

/* Registers for selecting the PRCM divider values */
#define CM_SYSCLK1_CLKSEL		(CM_DPLL_OFFSET + 0x00)
#define CM_SYSCLK2_CLKSEL		(CM_DPLL_OFFSET + 0x04)
#define CM_SYSCLK3_CLKSEL		(CM_DPLL_OFFSET + 0x08)
#define CM_SYSCLK4_CLKSEL		(CM_DPLL_OFFSET + 0x0C)
#define CM_SYSCLK7_CLKSEL		(CM_DPLL_OFFSET + 0x18)
#define CM_SYSCLK8_CLKSEL		(CM_DPLL_OFFSET + 0x1C)
#define CM_SYSCLK9_CLKSEL		(CM_DPLL_OFFSET + 0x20)
#define CM_SYSCLK10_CLKSEL		(CM_DPLL_OFFSET + 0x24)
#define CM_SYSCLK11_CLKSEL		(CM_DPLL_OFFSET + 0x2C)
#define CM_SYSCLK12_CLKSEL		(CM_DPLL_OFFSET + 0x30)
#define CM_SYSCLK13_CLKSEL		(CM_DPLL_OFFSET + 0x34)
#define CM_SYSCLK15_CLKSEL		(CM_DPLL_OFFSET + 0x38)
#define CM_VPB3_CLKSEL			(CM_DPLL_OFFSET + 0x40)
#define CM_VPC1_CLKSEL			(CM_DPLL_OFFSET + 0x44)
#define CM_VPD1_CLKSEL			(CM_DPLL_OFFSET + 0x48)
#define CM_SYSCLK19_CLKSEL		(CM_DPLL_OFFSET + 0x4C)
#define CM_SYSCLK20_CLKSEL		(CM_DPLL_OFFSET + 0x50)
#define CM_SYSCLK21_CLKSEL		(CM_DPLL_OFFSET + 0x54)
#define CM_SYSCLK22_CLKSEL		(CM_DPLL_OFFSET + 0x58)
#define CM_APA_CLKSEL			(CM_DPLL_OFFSET + 0x5C)
#define CM_SYSCLK14_CLKSEL		(CM_DPLL_OFFSET + 0x70)
#define CM_SYSCLK16_CLKSEL		(CM_DPLL_OFFSET + 0x74)
#define CM_SYSCLK18_CLKSEL		(CM_DPLL_OFFSET + 0x78)
#define CM_AUDIOCLK_MCASP0_CLKSEL	(CM_DPLL_OFFSET + 0x7C)
#define CM_AUDIOCLK_MCASP1_CLKSEL	(CM_DPLL_OFFSET + 0x80)
#define CM_AUDIOCLK_MCASP2_CLKSEL	(CM_DPLL_OFFSET + 0x84)
#define CM_AUDIOCLK_MCBSP_CLKSEL	(CM_DPLL_OFFSET + 0x88)
#define CM_TIMER0_CLKSEL		(CM_DPLL_OFFSET + 0x8C)
#define CM_TIMER1_CLKSEL		(CM_DPLL_OFFSET + 0x90)
#define CM_TIMER2_CLKSEL		(CM_DPLL_OFFSET + 0x94)
#define CM_TIMER3_CLKSEL		(CM_DPLL_OFFSET + 0x98)
#define CM_TIMER4_CLKSEL		(CM_DPLL_OFFSET + 0x9C)
#define CM_TIMER5_CLKSEL		(CM_DPLL_OFFSET + 0xA0)
#define CM_TIMER6_CLKSEL		(CM_DPLL_OFFSET + 0xA4)
#define CM_TIMER7_CLKSEL		(CM_DPLL_OFFSET + 0xA8)
#define CM_HDMI_CLKSEL			(CM_DPLL_OFFSET + 0xAC)
#define CM_SYSCLK23_CLKSEL		(CM_DPLL_OFFSET + 0xB0)
#define CM_SYSCLK24_CLKSEL		(CM_DPLL_OFFSET + 0xB4)


#define CM_ALWON_UART_0_CLKCTRL		(TI816X_PRCM_BASE + 0x1550)
#define CM_ALWON_UART_1_CLKCTRL		(TI816X_PRCM_BASE + 0x1554)
#define CM_ALWON_UART_2_CLKCTRL		(TI816X_PRCM_BASE + 0x1558)
#define CM_ALWON_TIMER_1_CLKCTRL	(TI816X_PRCM_BASE + 0x1570)
#define CM_ALWON_WDTIMER_CLKCTRL	(TI816X_PRCM_BASE + 0x158C)
/* WDTIMER register is RO. Cant disable it. Needs a kick */
#define CM_ALWON_SPI_CLKCTRL		(TI816X_PRCM_BASE + 0x1590)
#define CM_ALWON_ETH0_CLKCTRL		(TI816X_PRCM_BASE + 0x15D4)
#define CM_ALWON_ETH1_CLKCTRL		(TI816X_PRCM_BASE + 0x15D8)

#define CM_ALWON_L3_SLOW_CLKSTCTRL	(TI816X_PRCM_BASE + 0x1400)

/* UART registers */
#define UART_SYSCFG			(REG_UART0_BASE + 0x54)
#define UART_SYSSTS			(REG_UART0_BASE + 0x58)
#define UART_LCR			(REG_UART0_BASE + 0x0C)
#define UART_EFR			(REG_UART0_BASE + 0x08)
#define UART_MCR			(REG_UART0_BASE + 0x10)
#define UART_SCR			(REG_UART0_BASE + 0x40)
#define UART_TCR			(REG_UART0_BASE + 0x18)
#define UART_FCR			(REG_UART0_BASE + 0x08)
#define UART_DLL			(REG_UART0_BASE + 0x00)
#define UART_DLH			(REG_UART0_BASE + 0x04)
#define UART_MDR			(REG_UART0_BASE + 0x20)

/*DMM & EMIF4 MMR Declaration*/
#define DMM_LISA_MAP__0			(DMM_BASE_ADDR + 0x40)
#define DMM_LISA_MAP__1			(DMM_BASE_ADDR + 0x44)
#define DMM_LISA_MAP__2			(DMM_BASE_ADDR + 0x48)
#define DMM_LISA_MAP__3			(DMM_BASE_ADDR + 0x4C)
#define DMM_PAT_BASE_ADDR 		(DMM_BASE_ADDR + 0x460)

#define EMIF4_0_SDRAM_CONFIG		(EMIF4_0_CFG_BASE_ADDR + 0x08)	
#define EMIF4_0_SDRAM_CONFIG2		(EMIF4_0_CFG_BASE_ADDR + 0x0C)	
#define EMIF4_0_SDRAM_REF_CTRL		(EMIF4_0_CFG_BASE_ADDR + 0x10)	
#define EMIF4_0_SDRAM_REF_CTRL_SHADOW	(EMIF4_0_CFG_BASE_ADDR + 0x14)	
#define EMIF4_0_SDRAM_TIM_1		(EMIF4_0_CFG_BASE_ADDR + 0x18)	
#define EMIF4_0_SDRAM_TIM_1_SHADOW	(EMIF4_0_CFG_BASE_ADDR + 0x1C)	
#define EMIF4_0_SDRAM_TIM_2		(EMIF4_0_CFG_BASE_ADDR + 0x20)	
#define EMIF4_0_SDRAM_TIM_2_SHADOW	(EMIF4_0_CFG_BASE_ADDR + 0x24)	
#define EMIF4_0_SDRAM_TIM_3		(EMIF4_0_CFG_BASE_ADDR + 0x28)	
#define EMIF4_0_SDRAM_TIM_3_SHADOW	(EMIF4_0_CFG_BASE_ADDR + 0x2C)	
#define EMIF4_0_DDR_PHY_CTRL_1		(EMIF4_0_CFG_BASE_ADDR + 0xE4)	
#define EMIF4_0_DDR_PHY_CTRL_1_SHADOW	(EMIF4_0_CFG_BASE_ADDR + 0xE8)	

#define EMIF4_1_SDRAM_CONFIG		(EMIF4_1_CFG_BASE_ADDR + 0x08)	
#define EMIF4_1_SDRAM_CONFIG2		(EMIF4_1_CFG_BASE_ADDR + 0x0C)	
#define EMIF4_1_SDRAM_REF_CTRL		(EMIF4_1_CFG_BASE_ADDR + 0x10)	
#define EMIF4_1_SDRAM_REF_CTRL_SHADOW	(EMIF4_1_CFG_BASE_ADDR + 0x14)	
#define EMIF4_1_SDRAM_TIM_1		(EMIF4_1_CFG_BASE_ADDR + 0x18)	
#define EMIF4_1_SDRAM_TIM_1_SHADOW	(EMIF4_1_CFG_BASE_ADDR + 0x1C)	
#define EMIF4_1_SDRAM_TIM_2		(EMIF4_1_CFG_BASE_ADDR + 0x20)	
#define EMIF4_1_SDRAM_TIM_2_SHADOW	(EMIF4_1_CFG_BASE_ADDR + 0x24)	
#define EMIF4_1_SDRAM_TIM_3		(EMIF4_1_CFG_BASE_ADDR + 0x28)	
#define EMIF4_1_SDRAM_TIM_3_SHADOW	(EMIF4_1_CFG_BASE_ADDR + 0x2C)	
#define EMIF4_1_DDR_PHY_CTRL_1		(EMIF4_1_CFG_BASE_ADDR + 0xE4)	 
#define EMIF4_1_DDR_PHY_CTRL_1_SHADOW	(EMIF4_1_CFG_BASE_ADDR + 0xE8)	 


/*EMIF4 PRCM Defintion*/
#define CM_DEFAULT_L3_FAST_CLKSTCTRL	(TI816X_PRCM_BASE + 0x0508)    
#define CM_DEFAULT_EMIF_0_CLKCTRL	(TI816X_PRCM_BASE + 0x0520)
#define CM_DEFAULT_EMIF_1_CLKCTRL    	(TI816X_PRCM_BASE + 0x0524)
#define CM_DEFAULT_DMM_CLKCTRL 		(TI816X_PRCM_BASE + 0x0528)
#define CM_DEFAULT_FW_CLKCTRL 		(TI816X_PRCM_BASE + 0x052C)

#endif
