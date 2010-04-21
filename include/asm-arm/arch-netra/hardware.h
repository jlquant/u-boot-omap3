/*
 * hardware.h
 *
 * Netra SoC defs.
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

#ifndef __NETRA_HARDWARE_H
#define __NETRA_HARDWARE_H

/* Register Base Addresses */
#define REG_TIMER_BASE			0x4802C000
#define REG_UART0_BASE			0x48020000
#define REG_UART1_BASE			0x48022000
#define REG_UART2_BASE			0x48024000

/* Timer registers */
#define REG_TIMER_TCLR			0x38
#define REG_TIMER_TCRR			0x3C
#define REG_TIMER_TLDR			0x40

/* Timer register bits */
#define TCLR_ST				(1 << 0)
#define TCLR_AR				(1 << 1)
#define TCLR_PRE			(1 << 5)
#define TCLR_PTV_SHIFT			(2)

/* McSPI register */
#define OMAP3_MCSPI1_BASE		0x48030100
/* TODO Cross check */
#define OMAP3_MCSPI_MAX_FREQ	48000000

#endif /* __NETRA_HARDWARE_H */

