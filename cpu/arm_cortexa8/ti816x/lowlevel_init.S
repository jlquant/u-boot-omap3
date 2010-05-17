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
#include <asm/arch/cpu.h>
#include <asm/arch/clocks_ti816x.h>

_TEXT_BASE:
	.word	TEXT_BASE	/* Load address (RAM) */

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

/* default gpmc pad config valaue */
#define GPMC_PAD_DEF_VAL	(0x00000009)

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
	mov r2, #512	/* r2 <- copy size(% by 32 bytes:r3-r10 (8) regs used) */
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

	/****** GPMC out of reset ******/
	ldr r5, cm_alwon_gpm_clkctrl_addr
	mov r2, #0x2
	str r2, [r5]
	/* wait for gpmc enable to settle */
 gpmc_next_wait0:
	ldr r2, [r5]
	ands r2, r2, #0x00030000
	cmp r2, #0
	bne gpmc_next_wait0

	/***** GPMC CS0 init ******/
	/* disable CS0 */
	ldr r5, gpmc_cfg7_addr
	mov r2, #0
	str r2, [r5]
	/* wait for disable to settle */
	mov r3, #0x900
 gpmc_next_wait1:
	sub r3, r3, #1
	cmp r3, #1
	bne gpmc_next_wait1

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
	ldr r2, gpmc_pad_def_val
	ldr r5, tim7_out_addr
	str r2, [r5]
	ldr r5, sc1_data_addr
	str r2, [r5]
	ldr r5, sc1_clk_addr
	str r2, [r5]
	ldr r5, sc1_rst_addr
	str r2, [r5]
	ldr r5, sc1_det_addr
	str r2, [r5]
	ldr r5, uart0_rin_addr
	str r2, [r5]
	ldr r5, uart0_dcdn_addr
	str r2, [r5]
	ldr r5, uart0_dsrn_addr
	str r2, [r5]
	ldr r5, uart0_dtrn_addr
	str r2, [r5]
	ldr r5, sc1_vccen_addr
	str r2, [r5]
	ldr r5, sc0_rst_addr
	str r2, [r5]
	ldr r5, sc0_vccen_addr
	str r2, [r5]
	ldr r5, tim6_out_addr
	str r2, [r5]

	/* enable CS0 */
	ldr r5, gpmc_cfg7_addr
	ldr r2, gpmc_cfg7_val
	orr r2, r2, #0x40
	str r2, [r5]
	/* wait for enable to settle */
	mov r3, #0x900
 gpmc_next_wait2:
	sub r3, r3, #1
	cmp r3, #1
	bne gpmc_next_wait2

	ldmfd sp!, {ip}
	ldmfd sp!, {r0 - r7}
	mov sp, r0
	mov pc, lr      /* back to caller*/

/* these constants need to be close for PIC code */
/* The Nor has to be in the Flash Base CS0 for this condition to happen */
cm_alwon_gpm_clkctrl_addr:
	.word CM_ALWON_GPMC_CLKCTRL
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
tim7_out_addr:
	.word TIM7_OUT
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
tim6_out_addr:
	.word TIM6_OUT

/* default gpmc pad value */
gpmc_pad_def_val:
	.word GPMC_PAD_DEF_VAL

/*****************************************************************************
 * lowlevel_init: - Platform low level init.
 * Corrupted Register : r0, r1, r2, r3, r4, r5, r6
 ****************************************************************************/
.globl lowlevel_init
 lowlevel_init:

	/* The link register is saved in ip by start.S */
	mov r6, ip
	/* check if we are already running from RAM */
	ldr r2, _lowlevel_init
	ldr r3, _TEXT_BASE
	sub r4, r2, r3
	sub r0, pc, r4
	/* require dummy instr or subtract pc by 4 instead i'm doing stack init */
	ldr sp, SRAM_STACK
mark1:
	ldr r5, _mark1
	sub r5, r5, r2 /* bytes between mark1 and lowlevel_init */
	sub r0, r0, r5 /* r0 <- _start w.r.t current place of execution */
	ldr r1, _TEXT_BASE   /* test if we run from flash or RAM */
	cmp r0, r1          /* don't reloc during debug */
	beq gpmc_init_ret

	/**** enable ocmc 0 ****/
	/* CLKSTCTRL */
	ldr r5, cm_alwon_ocmc_0_clkstctrl_addr
	mov r2, #0x2
	str r2, [r5]
	/* wait for gpmc enable to settle */
 ocmc0_wait0:
	ldr r2, [r5]
	ands r2, r2, #0x00000010
	cmp r2, #1
	bne ocmc0_wait0
	/* CLKCTRL */
	ldr r5, cm_alwon_ocmc_0_clkctrl_addr
	mov r2, #0x2
	str r2, [r5]
	/* wait for gpmc enable to settle */
 ocmc0_wait1:
	ldr r2, [r5]
	ands r2, r2, #0x00030000
	cmp r2, #0
	bne ocmc0_wait1

	/**** enable ocmc 1 ****/
	/* CLKSTCTRL */
	ldr r5, cm_alwon_ocmc_1_clkstctrl_addr
	mov r2, #0x2
	str r2, [r5]
	/* wait for gpmc enable to settle */
 ocmc1_wait0:
	ldr r2, [r5]
	ands r2, r2, #0x00000010
	cmp r2, #1
	bne ocmc1_wait0
	/* CLKCTRL */
	ldr r5, cm_alwon_ocmc_1_clkctrl_addr
	mov r2, #0x2
	str r2, [r5]
	/* wait for gpmc enable to settle */
 ocmc1_wait1:
	ldr r2, [r5]
	ands r2, r2, #0x00030000
	cmp r2, #0
	bne ocmc1_wait1

	/* gpmc init */
	bl  cpy_nor_gpmc_code /* copy nor gpmc init code to sram */
	ldr r0, _gpmc_init_ret
	mov lr, r0	 /* gpmc init code in sram should return to gpmc_init_ret */
	ldr r0, sram0_start
	mov pc, r0	/* transfer ctrl to nor_gpmc_init() in sram */

gpmc_init_ret:
	ldr r5, sysclk10_clksel_addr	/* Fix ROM code bug */
	ldr r2, sysclk10_clksel_val
	str r2, [r5]
	bl s_init
	/* back to arch calling code */
	mov pc, r6
	/* the literal pools origin */
	.ltorg

cm_alwon_ocmc_0_clkstctrl_addr:
	.word CM_ALWON_OCMC_0_CLKSTCTRL
cm_alwon_ocmc_0_clkctrl_addr:
	.word CM_ALWON_OCMC_0_CLKCTRL
cm_alwon_ocmc_1_clkstctrl_addr:
	.word CM_ALWON_OCMC_1_CLKSTCTRL
cm_alwon_ocmc_1_clkctrl_addr:
	.word CM_ALWON_OCMC_1_CLKCTRL
_mark1:
	.word mark1
_lowlevel_init:
	.word lowlevel_init
_gpmc_init_ret:
	.word gpmc_init_ret

SRAM_STACK:
	.word (SRAM0_START + SRAM0_SIZE - SRAM_GPMC_STACK_SIZE)

/* ROM code bug */
sysclk10_clksel_addr:
	.word (TI816X_PRCM_BASE + 0x0324)
sysclk10_clksel_val:
	.word DDR_SYSCLK10_DIV


.global invalidate_dcache
.global l2_cache_enable
.global l2_cache_disable

/*
 *	invalidate_dcache()
 *
 *	Invalidate the whole D-cache.
 *
 *	Corrupted registers: r0-r5, r7, r9-r11
 *
 *	- mm	- mm_struct describing address space
 */
invalidate_dcache:
	stmfd	r13!, {r0 - r5, r7, r9 - r12, r14}
	mov	r10, #0				@ swith back to cache level 0
	mcr	p15, 2, r10, c0, c0, 0		@ select current cache level
						@ in cssr
	mcr	p15, 0, r10, c7, c5, 4		@ flush prefetch buffer,
						@ with armv7 this is 'isb',
						@ but we compile with armv5
	ldmfd	r13!, {r0 - r5, r7, r9 - r12, pc}


l2_cache_enable:
	push	{r0, r1, r2, lr}
	mrc	15, 0, r3, cr1, cr0, 1
	orr	r3, r3, #2
	mcr	15, 0, r3, cr1, cr0, 1
	pop	{r1, r2, r3, pc}


l2_cache_disable:
	push	{r0, r1, r2, lr}
	mrc	15, 0, r3, cr1, cr0, 1
	bic	r3, r3, #2
	mcr	15, 0, r3, cr1, cr0, 1
	pop	{r1, r2, r3, pc}


/* DPLL(1-4) PARAM TABLES */

/*
 * The first row in the table is the N,P values for the VCO
 *
 * The other rows have INT_FREQ, FRAC_FREQ, M_POST_DIV values.
 *
 * The fields are defined according to dpll_param struct (clock.c).
 *
 * The values are defined for all possible pll block outputs. One line for each DPLL o/p
 *
 * The PRCM dividers are present in a separate table
 */

main_dpll_param:
/* 26MHz */
.word MAIN_N_MUL, MAIN_P_DIV, DUMMY_VAL, DUMMY_VAL
/* main_pll_clock_1 */
.word MAIN_INTFREQ1, MAIN_FRACFREQ1, MAIN_M_POST_DIV1, DUMMY_VAL
/* main_pll_clock_2 */
.word MAIN_INTFREQ2, MAIN_FRACFREQ2, MAIN_M_POST_DIV2, DUMMY_VAL
/* main_pll_clock_3 */
.word MAIN_INTFREQ3, MAIN_FRACFREQ3, MAIN_M_POST_DIV3, DUMMY_VAL
/* main_pll_clock_4 */
.word MAIN_INTFREQ4, MAIN_FRACFREQ4, MAIN_M_POST_DIV4, DUMMY_VAL
/* main_pll_clock_5 */
.word MAIN_INTFREQ5, MAIN_FRACFREQ5, MAIN_M_POST_DIV5, DUMMY_VAL

.globl get_main_dpll_param
get_main_dpll_param:
	adr	r0, main_dpll_param
	mov	pc, lr

ddr_dpll_param:
/* 26MHz */
.word DDR_N_MUL, DDR_P_DIV, DUMMY_VAL, DUMMY_VAL
/* ddr_pll_clock_2 */
.word DDR_INTFREQ2, DDR_FRACFREQ2, DDR_M_POST_DIV2, DUMMY_VAL
/* ddr_pll_clock_3 */
.word DDR_INTFREQ3, DDR_FRACFREQ3, DDR_M_POST_DIV3, DUMMY_VAL

.globl get_ddr_dpll_param
get_ddr_dpll_param:
	adr	r0, ddr_dpll_param
	mov	pc, lr

video_dpll_param:
/* 26MHz */
.word VIDEO_N_MUL, VIDEO_P_DIV, DUMMY_VAL, DUMMY_VAL
/* video_pll_clock_1 */
.word VIDEO_INTFREQ1, VIDEO_FRACFREQ1, VIDEO_M_POST_DIV1, DUMMY_VAL
/* video_pll_clock_2 */
.word VIDEO_INTFREQ2, VIDEO_FRACFREQ2, VIDEO_M_POST_DIV2, DUMMY_VAL
/* video_pll_clock_3 */
.word VIDEO_INTFREQ3, VIDEO_FRACFREQ3, VIDEO_M_POST_DIV3, DUMMY_VAL

.globl get_video_dpll_param
get_video_dpll_param:
	adr	r0, video_dpll_param
	mov	pc, lr

audio_dpll_param:
/* 26MHz */
.word AUDIO_N_MUL, AUDIO_P_DIV, DUMMY_VAL, DUMMY_VAL
/* audio_pll_clock_1 */
/* .word AUDIO_INTFREQ1, AUDIO_FRACFREQ1, AUDIO_M_POST_DIV1, DUMMY_VAL*/
/* audio_pll_clock_2 */
.word AUDIO_INTFREQ2, AUDIO_FRACFREQ2, AUDIO_M_POST_DIV2, DUMMY_VAL
/* audio_pll_clock_3 */
.word AUDIO_INTFREQ3, AUDIO_FRACFREQ3, AUDIO_M_POST_DIV3, DUMMY_VAL
/* audio_pll_clock_4 */
.word AUDIO_INTFREQ4, AUDIO_FRACFREQ4, AUDIO_M_POST_DIV4, DUMMY_VAL
/* audio_pll_clock_5 */
.word AUDIO_INTFREQ5, AUDIO_FRACFREQ5, AUDIO_M_POST_DIV5, DUMMY_VAL


.globl get_audio_dpll_param
get_audio_dpll_param:
	adr	r0, audio_dpll_param
	mov	pc, lr

iva_param:
.word IVAHD0_CONFIG_REG_BASE, PRCM_IVAHD0_ICONT_RST_CNTL_ADDR, IVAHD0_ICONT1_ITCM_BASE, IVAHD0_ICONT2_ITCM_BASE
.word IVAHD1_CONFIG_REG_BASE, PRCM_IVAHD1_ICONT_RST_CNTL_ADDR, IVAHD1_ICONT1_ITCM_BASE, IVAHD1_ICONT2_ITCM_BASE
.word IVAHD2_CONFIG_REG_BASE, PRCM_IVAHD2_ICONT_RST_CNTL_ADDR, IVAHD2_ICONT1_ITCM_BASE, IVAHD2_ICONT2_ITCM_BASE

.globl get_iva_param
get_iva_param:
	adr	r0,iva_param
	mov	pc,lr


