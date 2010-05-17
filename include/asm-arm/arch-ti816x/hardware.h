/*
 * hardware.h
 *
 * TODO: VB_Rename this file to ti816x.h as the addresses specfic to ti816x are present here
 *
 * TI816X SoC defs.
 *
 * Copyright (C) 2009, Texas Instruments, Incorporated
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __TI816X_HARDWARE_H
#define __TI816X_HARDWARE_H

/* Make a new file sys_info.h for this #define */
#define CPU_TI816X            816

/* The objective is to keep only the top level memory map here
 * The break-up of the memory map for individual modules should
 * in a diff file like cpu.h so that when this is the only place
 * where change is needed for new SoCs when the ip is the same
 */

#define BIT(x)				(1 << x)

/* Register Base Addresses */
#define REG_TIMER_BASE			0x4802C000
#define REG_UART0_BASE			0x48020000
#define REG_UART1_BASE			0x48022000
#define REG_UART2_BASE			0x48024000

/* Timer registers */
#define REG_TIMER_TCLR			0x38	/* Timer control register */
#define REG_TIMER_TCRR			0x3C	/* Timer counter register */
#define REG_TIMER_TLDR			0x40	/* Timer load value register*/

/* Timer register bits */
#define TCLR_ST				BIT(0)	/* Start=1 Stop=0 */
#define TCLR_AR				BIT(1)	/* Auto reload */
#define TCLR_PRE			BIT(5)	/* Pre-scaler enable for the timer input clk */
#define TCLR_PTV_SHIFT			(2)	/* Pre-scaler shift value */

/* McSPI register */
#define OMAP3_MCSPI1_BASE		0x48030100
/* TODO Cross check */
#define OMAP3_MCSPI_MAX_FREQ		48000000
/* Watchdog Timer */
#define WD1_BASE			0x480C2000

/* Control Module Base Address */
#define TI816X_CTRL_BASE		0x48140000

/* PRCM Base Address */
#define TI816X_PRCM_BASE		0x48180000

/* IVAHD related */
#define CM_IVAHD0_CLKSTCTRL		(TI816X_PRCM_BASE + 0x0600)
#define CM_IVAHD0_IVAHD_CLKCTRL		(TI816X_PRCM_BASE + 0x0620)
#define CM_IVAHD0_SL2_CLKCTRL		(TI816X_PRCM_BASE + 0x0624)
#define PM_IVAHD0_PWRSTST		(TI816X_PRCM_BASE + 0x0C04)
#define RM_IVAHD0_RSTCTRL		(TI816X_PRCM_BASE + 0x0C10)
#define RM_IVAHD0_RSTST			(TI816X_PRCM_BASE + 0x0C14)


#define CM_IVAHD1_CLKSTCTRL		(TI816X_PRCM_BASE + 0x0700)
#define CM_IVAHD1_IVAHD_CLKCTRL		(TI816X_PRCM_BASE + 0x0720)
#define CM_IVAHD1_SL2_CLKCTRL		(TI816X_PRCM_BASE + 0x0724)
#define PM_IVAHD1_PWRSTST		(TI816X_PRCM_BASE + 0x0D04)
#define RM_IVAHD1_RSTCTRL		(TI816X_PRCM_BASE + 0x0D10)
#define RM_IVAHD1_RSTST			(TI816X_PRCM_BASE + 0x0D14)

#define CM_IVAHD2_CLKSTCTRL		(TI816X_PRCM_BASE + 0x0800)
#define CM_IVAHD2_IVAHD_CLKCTRL		(TI816X_PRCM_BASE + 0x0820)
#define CM_IVAHD2_SL2_CLKCTRL		(TI816X_PRCM_BASE + 0x0824)
#define PM_IVAHD2_PWRSTST		(TI816X_PRCM_BASE + 0x0E04)
#define RM_IVAHD2_RSTCTRL		(TI816X_PRCM_BASE + 0x0E10)
#define RM_IVAHD2_RSTST			(TI816X_PRCM_BASE + 0x0E14)

#define IVAHD0_CONFIG_REG_BASE		0x58000000
#define IVAHD1_CONFIG_REG_BASE		0x5A000000
#define IVAHD2_CONFIG_REG_BASE		0x53000000

#define PRCM_IVAHD0_ICONT_RST_CNTL_ADDR (TI816X_PRCM_BASE + 0x0C10)
#define PRCM_IVAHD1_ICONT_RST_CNTL_ADDR (TI816X_PRCM_BASE + 0x0D10)
#define PRCM_IVAHD2_ICONT_RST_CNTL_ADDR (TI816X_PRCM_BASE + 0x0E10)

#define IVAHD0_ICONT1_ITCM_BASE  (IVAHD0_CONFIG_REG_BASE + 0x08000)
#define IVAHD0_ICONT2_ITCM_BASE  (IVAHD0_CONFIG_REG_BASE + 0x18000)
#define IVAHD1_ICONT1_ITCM_BASE  (IVAHD1_CONFIG_REG_BASE + 0x08000)
#define IVAHD1_ICONT2_ITCM_BASE  (IVAHD1_CONFIG_REG_BASE + 0x18000)
#define IVAHD2_ICONT1_ITCM_BASE  (IVAHD2_CONFIG_REG_BASE + 0x08000)
#define IVAHD2_ICONT2_ITCM_BASE  (IVAHD2_CONFIG_REG_BASE + 0x18000)

#define IVAHD_LENGTH_BOOT_CODE  	14

/* EMIF Base address */
#define EMIF4_0_CFG_BASE_ADDR		0x4C000000
#define EMIF4_1_CFG_BASE_ADDR		0x4D000000

#define DMM_BASE_ADDR			0x4E000000

/* DM Timer base addresses */
#define DM_TIMER0_BASE_ADDR		0x4802c000
#define DM_TIMER1_BASE_ADDR		0x4802e000
#define DM_TIMER2_BASE_ADDR		0x48040000
#define DM_TIMER3_BASE_ADDR		0x48042000
#define DM_TIMER4_BASE_ADDR		0x48044000
#define DM_TIMER5_BASE_ADDR		0x48046000
#define DM_TIMER6_BASE_ADDR		0x48048000
#define DM_TIMER7_BASE_ADDR		0x4804A000

#endif /* __TI816X_HARDWARE_H */

