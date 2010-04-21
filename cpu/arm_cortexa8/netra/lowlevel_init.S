/*
 * lowlevel_init.S
 *
 * Netra EVM low level initialization.
 *
 * Copyright (C) 2010, Texas Instruments, Incorporated
 *
 * Initial Code by:
 * Mansoor Ahamed  <mansoor.ahamed@ti.com>
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

#include <config.h>
#include <asm/arch/hardware.h>

_TEXT_BASE:
.word	TEXT_BASE	/* Load address (RAM) */

/* TODO: These set of defines should be moved to some other file */
#define SRAM0_START 			0x40300000
#define SRAM0_SIZE				0x40000
#define SRAM_GPMC_STACK_SIZE	0x40

/* GPMC MMR 
 * TODO: Should we move this to someother file?
 */
#define GPMC_BASE				0x50000000
#define GPMC_CONFIG_CS0			0x60
#define GPMC_CONFIG_CS0_BASE	(GPMC_BASE + GPMC_CONFIG_CS0)
#define GPMC_CONFIG1			0x00
#define GPMC_CONFIG2			0x04
#define GPMC_CONFIG3			0x08
#define GPMC_CONFIG4			0x0C
#define GPMC_CONFIG5			0x10
#define GPMC_CONFIG6			0x14
#define GPMC_CONFIG7			0x18

/* GPMC CFG values for Spansion S29GL512P11TFI010 & S29GL512N11TFI010
 * This should work for most NOR, else we might have to move
 * these defines to evm.h
 * Values used here are for nominal speed, tweak it to improve performance
 */
#define SPNOR_GPMC_CONFIG1	0x00001010	
#define SPNOR_GPMC_CONFIG2	0x00101080
#define SPNOR_GPMC_CONFIG3	0x00020201
#define SPNOR_GPMC_CONFIG4	0x0f031003
#define SPNOR_GPMC_CONFIG5	0x000f1111
#define SPNOR_GPMC_CONFIG6	0x0f030080
#define SPNOR_GPMC_CONFIG7	0x00000C00

/* PAD configuration register offsets and values for gpmc address
 * lines a12 - a26
 */
#define CFG_MOD_BASE 0x48140000
#define SC1_VPPEN	(CFG_MOD_BASE + 0xb24)	/* a12 */
#define SC1_DATA	(CFG_MOD_BASE + 0xb18)	/* a13 */
#define SC1_CLK		(CFG_MOD_BASE + 0xb14)	/* a14 */
#define SC1_RST		(CFG_MOD_BASE + 0xb10)  /* a15 */
#define SC1_DET		(CFG_MOD_BASE + 0xb0c)  /* a16 */
#define UART0_RIN	(CFG_MOD_BASE + 0xacc)  /* a17 */
#define UART0_DCDN	(CFG_MOD_BASE + 0xac8)  /* a18 */
#define UART0_DSRN	(CFG_MOD_BASE + 0xac4)  /* a19 */
#define UART0_DTRN	(CFG_MOD_BASE + 0xac0)  /* a20 */
#define SC1_VCCEN	(CFG_MOD_BASE + 0xb20)  /* a21 */
#define SC0_RST		(CFG_MOD_BASE + 0xaf4)  /* a22 */
#define SC0_VCCEN	(CFG_MOD_BASE + 0xb04)  /* a23 */
#define SC0_VPPEN	(CFG_MOD_BASE + 0xb08)  /* a24 */
#define SC0_DATA	(CFG_MOD_BASE + 0xafc)  /* a25 */
#define SC0_CLK		(CFG_MOD_BASE + 0xaf8)	/* a26 */
/* pad values */
#define GPMC_PAD_DEF	(0x00000008)
#define SC1_VPPEN_VAL	(GPMC_PAD_DEF | 0x1)  /* a12 */
#define SC1_DATA_VAL	(GPMC_PAD_DEF | 0x1)  /* a13 */
#define SC1_CLK_VAL		(GPMC_PAD_DEF | 0x1)  /* a14 */
#define SC1_RST_VAL		(GPMC_PAD_DEF | 0x1)  /* a15 */
#define SC1_DET_VAL		(GPMC_PAD_DEF | 0x1)  /* a16 */
#define UART0_RIN_VAL	(GPMC_PAD_DEF | 0x1)  /* a17 */
#define UART0_DCDN_VAL	(GPMC_PAD_DEF | 0x1)  /* a18 */
#define UART0_DSRN_VAL	(GPMC_PAD_DEF | 0x1)  /* a19 */
#define UART0_DTRN_VAL	(GPMC_PAD_DEF | 0x1)  /* a20 */
#define SC1_VCCEN_VAL	(GPMC_PAD_DEF | 0x1)  /* a21 */
#define SC0_RST_VAL		(GPMC_PAD_DEF | 0x1)  /* a22 */
#define SC0_VCCEN_VAL	(GPMC_PAD_DEF | 0x1)  /* a23 */
#define SC0_VPPEN_VAL	(GPMC_PAD_DEF | 0x1)  /* a24 */
#define SC0_DATA_VAL	(GPMC_PAD_DEF | 0x1)  /* a25 */
#define SC0_CLK_VAL		(GPMC_PAD_DEF | 0x1)  /* a26 */

/**************************************************************************
 * cpy_nor_gpmc_code: relocates nor gpmc init code into ocmc0 where its 
 * safer to execute
 * R2 is loaded wtih size of data to be copied, this should be calculated
 * if we are modifying nor_gpmc_init()
 *************************************************************************/
.global cpy_nor_gpmc_code 
 cpy_nor_gpmc_code:
	/* Copy NOR GPMC init code into SRAM */
	adr r0, nor_gpmc_init     /* get addr of nor gpmc init code */
	mov r2, #640	/* r2 <- copy size(% by 32 bytes:r3-r10 (8) regs used) */
	ldr r1, sram0_start     /* r1 <- dest address (passed in) */
	add r2, r2, r0      /* r2 <- source end address */
next2:
	ldmia   r0!, {r3 - r10}     /* copy from source address [r0] */
	stmia   r1!, {r3 - r10}     /* copy to   target address [r1] */
	cmp r0, r2          /* until source end address [r2] */
	bne next2
	mov pc, lr          /* back to caller */

/*****************************************************************************
 *  nor_gpmc_init: - Init GPMC for NOR on CS0, executed from SRAM.
 *
 *  R0 - used for saving SP, hence do not use it anywhere
 ****************************************************************************/
.global nor_gpmc_init 
 nor_gpmc_init:
	mov r0, sp
	ldr sp, SRAM_STACK_GPMC
	stmfd sp!, {r0 - r7}
	stmfd sp!, {ip}

	/***** GPMC CS0 init ******/

	/* disable CS0 */
	ldr r5, gpmc_cfg7_addr
	mov r2, #0
	str r2, [r5]
	/* wait for disable to settle */	
	mov r3, #0x900
_gpmc_next_wait1:
	sub r3, r3, #1
	cmp r3, #1
	bne _gpmc_next_wait1

	/* set gpmc config registers */
	ldr r5, gpmc_cfg1_addr
	ldr r2, gpmc_cfg1_val
	str r2, [r5]
	ldr r5, gpmc_cfg2_addr
	ldr r2, gpmc_cfg2_val
	str r2, [r5]
	ldr r5, gpmc_cfg3_addr
	ldr r2, gpmc_cfg3_val
	str r2, [r5]
	ldr r5, gpmc_cfg4_addr
	ldr r2, gpmc_cfg4_val
	str r2, [r5]
	ldr r5, gpmc_cfg5_addr
	ldr r2, gpmc_cfg5_val
	str r2, [r5]
	ldr r5, gpmc_cfg6_addr
	ldr r2, gpmc_cfg6_val
	str r2, [r5]
	ldr r5, gpmc_cfg7_addr
	ldr r2, gpmc_cfg7_val
	str r2, [r5]

	/* do pin muxing */	
	ldr r5, sc1_vppen_addr
	ldr r2, sc1_vppen_val
	str r2, [r5]
	ldr r5, sc1_data_addr
	ldr r2, sc1_data_val
	str r2, [r5]
	ldr r5, sc1_clk_addr
	ldr r2, sc1_clk_val
	str r2, [r5]
	ldr r5, sc1_rst_addr
	ldr r2, sc1_rst_val
	str r2, [r5]
	ldr r5, sc1_det_addr
	ldr r2, sc1_det_val
	str r2, [r5]
	ldr r5, uart0_rin_addr
	ldr r2, uart0_rin_val
	str r2, [r5]
	ldr r5, uart0_dcdn_addr
	ldr r2, uart0_dcdn_val
	str r2, [r5]
	ldr r5, uart0_dsrn_addr
	ldr r2, uart0_dsrn_val
	str r2, [r5]
	ldr r5, uart0_dtrn_addr
	ldr r2, uart0_dtrn_val
	str r2, [r5]
	ldr r5, sc1_vccen_addr
	ldr r2, sc1_vccen_val
	str r2, [r5]
	ldr r5, sc0_rst_addr
	ldr r2, sc0_rst_val
	str r2, [r5]
	ldr r5, sc0_vccen_addr
	ldr r2, sc0_vccen_val
	str r2, [r5]
	ldr r5, sc0_vppen_addr
	ldr r2, sc0_vppen_val
	str r2, [r5]
	ldr r5, sc0_data_addr
	ldr r2, sc0_data_val
	str r2, [r5]
	ldr r5, sc0_clk_addr
	ldr r2, sc0_clk_val
	
	/* enable CS0 */
	ldr r5, gpmc_cfg7_addr
	ldr r2, gpmc_cfg7_val
	orr r2, r2, #0x40
	str r2, [r5]
	/* wait for enable to settle */	
	mov r3, #0x900
_gpmc_next_wait2:
	sub r3, r3, #1
	cmp r3, #1
	bne _gpmc_next_wait2

	ldmfd sp!, {ip}
	ldmfd sp!, {r0 - r7}
	mov sp, r0
	mov pc, lr      /* back to caller*/

/* these constants need to be close for PIC code */
/* The Nor has to be in the Flash Base CS0 for this condition to happen */
sram0_start:
	.word SRAM0_START
SRAM_STACK_GPMC:
	.word (SRAM0_START + SRAM0_SIZE)
gpmc_cfg1_addr:
    .word (GPMC_CONFIG_CS0_BASE + GPMC_CONFIG1)
gpmc_cfg2_addr:
    .word (GPMC_CONFIG_CS0_BASE + GPMC_CONFIG2)
gpmc_cfg3_addr:
    .word (GPMC_CONFIG_CS0_BASE + GPMC_CONFIG3)
gpmc_cfg4_addr:
    .word (GPMC_CONFIG_CS0_BASE + GPMC_CONFIG4)
gpmc_cfg5_addr:
    .word (GPMC_CONFIG_CS0_BASE + GPMC_CONFIG5)
gpmc_cfg6_addr:
    .word (GPMC_CONFIG_CS0_BASE + GPMC_CONFIG6)
gpmc_cfg7_addr:
    .word (GPMC_CONFIG_CS0_BASE + GPMC_CONFIG7)

gpmc_cfg1_val:
    .word SPNOR_GPMC_CONFIG1
gpmc_cfg2_val:
    .word SPNOR_GPMC_CONFIG2
gpmc_cfg3_val:
    .word SPNOR_GPMC_CONFIG3
gpmc_cfg4_val:
    .word SPNOR_GPMC_CONFIG4
gpmc_cfg5_val:
    .word SPNOR_GPMC_CONFIG5
gpmc_cfg6_val:
    .word SPNOR_GPMC_CONFIG6
gpmc_cfg7_val:
    .word SPNOR_GPMC_CONFIG7

/* pad config reg addresses and values */
sc1_vppen_addr:
	.word SC1_VPPEN
sc1_data_addr:
	.word SC1_DATA
sc1_clk_addr:
	.word SC1_CLK
sc1_rst_addr:
	.word SC1_RST
sc1_det_addr:
	.word SC1_DET
uart0_rin_addr:
	.word UART0_RIN
uart0_dcdn_addr:
	.word UART0_DCDN
uart0_dsrn_addr:
	.word UART0_DSRN
uart0_dtrn_addr:
	.word UART0_DTRN
sc1_vccen_addr:
	.word SC1_VCCEN
sc0_rst_addr:
	.word SC0_RST
sc0_vccen_addr:
	.word SC0_VCCEN
sc0_vppen_addr:
	.word SC0_VPPEN
sc0_data_addr:
	.word SC0_DATA
sc0_clk_addr:
	.word SC0_CLK

/* pad values */
sc1_vppen_val:
	.word SC1_VPPEN_VAL 
sc1_data_val:
	.word SC1_DATA_VAL
sc1_clk_val:
	.word SC1_CLK_VAL
sc1_rst_val:
	.word SC1_RST_VAL
sc1_det_val:
	.word SC1_DET_VAL
uart0_rin_val:
	.word UART0_RIN_VAL
uart0_dcdn_val:
	.word UART0_DCDN_VAL
uart0_dsrn_val:
	.word UART0_DSRN_VAL
uart0_dtrn_val:
	.word uart0_dtrn_val
sc1_vccen_val:
	.word SC1_VCCEN_VAL 
sc0_rst_val:
	.word SC0_RST_VAL 
sc0_vccen_val:
	.word SC0_VCCEN_VAL
sc0_vppen_val:
	.word SC0_VPPEN_VAL
sc0_data_val:
	.word SC0_DATA_VAL
sc0_clk_val:
	.word SC0_CLK_VAL

/*****************************************************************************
 * lowlevel_init: - Platform low level init.
 *
 ****************************************************************************/
.extern _start
.globl lowlevel_init
 lowlevel_init:

	mov r0, sp
	ldr sp, SRAM_STACK
	stmfd sp!, {r0 - r6}
	stmfd sp!, {ip,lr}
	
	/* check if we are already running from RAM */
	ldr r2, _lowlevel_init
	ldr r3, _TEXT_BASE
	sub r4, r2, r3
	sub r0, pc, r4
mark1:
	ldr r5, _mark1
	sub r5, r5, r2 /* bytes between mark1 and lowlevel_init */
	sub r0, r0, r5 /* r0 <- _start w.r.t current place of execution */  
    ldr r1, _TEXT_BASE   /* test if we run from flash or RAM */
    cmp r0, r1          /* don't reloc during debug */
    bne gpmc_init_ret

	bl  cpy_nor_gpmc_code /* copy nor gpmc init code to sram */
	ldr r0, _gpmc_init_ret
	mov lr, r0	 /* gpmc init code in sram should return to gpmc_init_ret */
	ldr r0, sram0_start
	mov pc, r0	/* transfer ctrl to nor_gpmc_init() in sram */ 

gpmc_init_ret:	
	ldmfd sp!, {ip,lr}
	ldmfd sp!, {r0 - r6}
	mov sp, r0
	/* back to arch calling code */
	mov pc, lr
	/* the literal pools origin */
	.ltorg

_mark1:
	.word mark1
_lowlevel_init:
	.word lowlevel_init
_gpmc_init_ret:
	.word gpmc_init_ret

SRAM_STACK:
	.word (SRAM0_START + SRAM0_SIZE - SRAM_GPMC_STACK_SIZE)
