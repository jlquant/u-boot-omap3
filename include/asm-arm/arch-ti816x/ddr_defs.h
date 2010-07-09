/*
 * Copyright (C) 2010 Texas Instruments
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * ----------------------------------------------------------------------------
 *
 */

#ifndef _DDR_DEFS_H
#define _DDR_DEFS_H

#include <asm/arch/hardware.h>

#ifdef CONFIG_TI816X_EVM_DDR3
/*
 * DDR3 force values.  These are board dependent
 */

/* EVM 400 MHz clock Settings */
#define N_RANK			1
#define INVERT_CLOCK		1
#define CMD_SLAVE_FROM_INV_CLOCK(i) (((i)==0) ? 0x80 : 0x100)
#define CMD_SLAVE_RATIO		CMD_SLAVE_FROM_INV_CLOCK(INVERT_CLOCK)

#define WR_DQS_FORCE_3		 0x00000010
#define WR_DQS_FORCE_2  	 0x00000010
#define WR_DQS_FORCE_1  	 0x00000010
#define WR_DQS_FORCE_0  	 0x00000010

#define RD_DQS_FORCE_0		 0x00000028
#define RD_DQS_FORCE_1		 0x00000028
#define RD_DQS_FORCE_2		 0x00000028
#define RD_DQS_FORCE_3		 0x00000028

#define RD_GATE_FORCE_3		0x44
#define RD_GATE_FORCE_2		0x44
#define RD_GATE_FORCE_1		0x44
#define RD_GATE_FORCE_0		0x44

#define WR_DQS_RATIO_0		0x40
#define WR_DQS_RATIO_1		0x20
#define WR_DQS_RATIO_2		0x40
#define WR_DQS_RATIO_3		0x20

#define RD_DQS_RATIO_0		0x40
#define RD_DQS_RATIO_1		0x40
#define RD_DQS_RATIO_2		0x40
#define RD_DQS_RATIO_3		0x40

#define RD_GATE_RATIO_0		0x38
#define RD_GATE_RATIO_1		0x20
#define RD_GATE_RATIO_2		0x38
#define RD_GATE_RATIO_3		0x20

#define HACK_EYE_TRAINING	1
#define USE_WR_DQS_FORCE	0
#define USE_RD_DQS_FORCE	HACK_EYE_TRAINING
#define USE_RD_GATE_FORCE	0

#define DDR_DATA_RATE		800
#define USE_EMIF0		1
#define USE_EMIF1		1

/*
 * EMIF Paramters
 */
#define EMIF_TIM1    0x0CCCE524  /* relaxed timing values - optimal 0AAAD4E3 */
#define EMIF_TIM2    0x30308023  /* relaxed timing valeus - optimal 242F7FDA */
#define EMIF_TIM3    0x009F82CF  /* relaxed timing valeus - optimal 009F82B8 */
#define EMIF_SDREF   0x10000C30  /* optimal refresh interval - 10000C30 */
#define EMIF_SDCFG   0x62A452B2  /* 32 bit ddr3, CL=6, CWL=5, 14 rows, 8 banks, 10 bit column, 1 CS */
#define EMIF_PHYCFG  0x0000030B  /* local odt = 3, read latency = 11 (max = 12, min=6) */

#endif

#ifdef CONFIG_TI816X_EVM_DDR2

#define INVERT_CLK_OUT              0x0
#define CMD_SLAVE_RATIO             0x80
/*
 * DDR2 ratio values.  These are board dependent
 * obtained from sweep experiments
 */

/* EVM 400 MHz clock Settings */

#define WR_DQS_RATIO_BYTE_LANE3   ((0x4a << 10) | 0x4a)
#define WR_DQS_RATIO_BYTE_LANE2   ((0x4a << 10) | 0x4a)
#define WR_DQS_RATIO_BYTE_LANE1   ((0x4a << 10) | 0x4a)
#define WR_DQS_RATIO_BYTE_LANE0   ((0x4a << 10) | 0x4a)

#define WR_DATA_RATIO_BYTE_LANE3   (((0x4a + 0x40) << 10) | (0x4a + 0x40))
#define WR_DATA_RATIO_BYTE_LANE2   (((0x4a + 0x40) << 10) | (0x4a + 0x40))
#define WR_DATA_RATIO_BYTE_LANE1   (((0x4a + 0x40) << 10) | (0x4a + 0x40))
#define WR_DATA_RATIO_BYTE_LANE0   (((0x4a + 0x40) << 10) | (0x4a + 0x40))

#define RD_DQS_RATIO		  ((0x40 << 10) | 0x40)

#define DQS_GATE_BYTE_LANE0       ((0x13a << 10) | 0x13a)
#define DQS_GATE_BYTE_LANE1       ((0x13a << 10) | 0x13a)
#define DQS_GATE_BYTE_LANE2       ((0x13a << 10) | 0x13a)
#define DQS_GATE_BYTE_LANE3       ((0x13a << 10) | 0x13a)

/*
 * EMIF Paramters
 */
#define EMIF_TIM1    0xAAB15E2
#define EMIF_TIM2    0x423631D2
#define EMIF_TIM3    0x80032F
#define EMIF_SDREF   0x10000C30
#define EMIF_SDCFG   0x43801A3A  /* 32 bit ddr2, CL=6, CWL=5, 13 rows, 8 banks, 10 bit column, 2 CS */
#define EMIF_PHYCFG  0x0000030B  /* local odt = 3, read latency = 11 (max = 12, min=6) */

#endif

#endif  /* _DDR_DEFS_H */
