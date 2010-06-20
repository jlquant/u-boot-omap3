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

#ifdef CONFIG_TI816X
/*
 * DDR invert clock selection - 0/1.  CMD_SLAVE_RATIO = (INVERT_CLK_OUT == 0) ? 0x80 : 0x100
 *
 * For DDR3 systems, we only recomend using INVERT_CLK_OUT = 0 right now
 */

#define INVERT_CLK_OUT              0x0
#define CMD_SLAVE_RATIO             0x80


/*
 * DDR3 force values.  These are board dependent
 */

/* EVM 400 MHz clock Settings */

#define WR_DQS_FORCE_BYTE_LANE3   0x00000032
#define WR_DQS_FORCE_BYTE_LANE2   0x00000032
#define WR_DQS_FORCE_BYTE_LANE1   0x00000032
#define WR_DQS_FORCE_BYTE_LANE0   0x00000032

#define RD_DQS_FORCE		  0x0000002C

#define DQS_GATE_BYTE_LANE0       0x68
#define DQS_GATE_BYTE_LANE1       0x63
#define DQS_GATE_BYTE_LANE2       0x52
#define DQS_GATE_BYTE_LANE3       0x35

/*
 * EMIF Paramters
 */
#define EMIF_TIM1    0x0CCCE524  /* relaxed timing values - optimal 0AAAD4E3 */
#define EMIF_TIM2    0x30308023  /* relaxed timing valeus - optimal 242F7FDA */
#define EMIF_TIM3    0x009F82CF  /* relaxed timing valeus - optimal 009F82B8 */
#define EMIF_SDREF   0x10000C30  /* optimal refresh interval - 10000C30 */
#define EMIF_SDCFG   0x62A412B2  /* 32 bit ddr3, CL=6, CWL=5, 14 rows, 8 banks, 10 bit column, 1 CS */
#define EMIF_PHYCFG  0x0000030B  /* local odt = 3, read latency = 11 (max = 12, min=6) */


#endif

#endif  /* _DDR_DEFS_H */
