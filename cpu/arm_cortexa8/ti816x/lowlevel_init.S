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
#define SPNOR_GPMC_CONFIG7	0x00000C08

/* default gpmc pad config valaue */
#define GPMC_PAD_DEF_VAL	(0x00000001)

/* GPIO clk control */
#define GPIO0_CFG_VAL		0xFFEFFFFF
#define GPIO0_CLKCTRL_VAL	0x102

#define SRAM1_START			(0x40400000)
#define RAM_ADDR_MASK		(0xC0000000)

/**************************************************************************
 * cpy_nor_gpmc_code: relocates nor gpmc init code into ocmc0 where its
 * safer to execute
 * R2 is loaded wtih size of data to be copied, this should be calculated
 * if we are modifying nor_gpmc_init()
 *************************************************************************/
.global cpy_nor_gpmc_code
 cpy_nor_gpmc_code:
	stmfd sp!, {r0 - r10}
	/* Copy NOR GPMC init code into SRAM */
	adr r0, nor_gpmc_init     /* get addr of nor gpmc init code */
	mov r2, #640	/* r2 <- copy size(% by 32 bytes:r3-r10 (8) regs used) */
	ldr r1, sram_pc_start     /* r1 <- dest address (passed in) */
	add r2, r2, r0      /* r2 <- source end address */
next2:
	ldmia   r0!, {r3 - r10}     /* copy from source address [r0] */
	stmia   r1!, {r3 - r10}     /* copy to   target address [r1] */
	cmp r0, r2          /* until source end address [r2] */
	bne next2
	ldmfd sp!, {r0 - r10}
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
	stmfd sp!, {r0 - r5}
	stmfd sp!, {ip}

	/****** GPMC out of reset ******/
	ldr r5, cm_alwon_gpmc_clkctrl_addr
	mov r2, #0x2
	str r2, [r5]
	/* wait for gpmc enable to settle */
 gpmc_next_wait0:
	ldr r2, [r5]
	ands r2, r2, #0x00030000
	cmp r2, #0
	bne gpmc_next_wait0

	/****** GPIO out of reset *******/
	ldr r5, cm_alwon_gpio0_clkctrl_addr
	ldr r2, cm_alwon_gpio0_clkctrl_val
	str r2, [r5]
	/* wait for gpio enable to settle */
 gpio_next_wait0:
	ldr r2, [r5]
	ands r2, r2, #0x3
	cmp r2, #0x2
	bne gpio_next_wait0

	/****** Set GPIO-20 to low */
	ldr r5, gpio0_data_addr
	mov r2, #0x0
	str r2, [r5]
	ldr r5, gpio0_cfg_addr 
	ldr r2, gpio0_cfg_val
	str r2, [r5]

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
	mov r2, #0x1
	ldr r5, gpmc_a12_addr
	str r2, [r5]
	ldr r5, gpmc_a13_addr
	str r2, [r5]
	ldr r5, gpmc_a14_addr
	str r2, [r5]
	ldr r5, gpmc_a15_addr
	str r2, [r5]
	ldr r5, sc1_rst_addr /* gpmc_a15 used in two pins */
	str r2, [r5]
	ldr r5, gpmc_a16_addr
	str r2, [r5]
	ldr r5, gpmc_a17_addr
	str r2, [r5]
	ldr r5, gpmc_a18_addr
	str r2, [r5]
	ldr r5, gpmc_a19_addr
	str r2, [r5]
	ldr r5, gpmc_a20_addr
	str r2, [r5]
	ldr r5, gpmc_a21_addr
	str r2, [r5]
	ldr r5, gpmc_a22_addr
	str r2, [r5]
	ldr r5, gpmc_a23_addr
	mov r2, #0x2
	str r2, [r5]
	mov r2, #0x1
	ldr r5, gpmc_a24_addr
	str r2, [r5]
	ldr r5, gpmc_a25_addr
	str r2, [r5]
	ldr r5, gpmc_a27_addr
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
	ldmfd sp!, {r0 - r5}
	mov sp, r0
	mov pc, lr      /* back to caller*/

/* these constants need to be close for PIC code */
/* The Nor has to be in the Flash Base CS0 for this condition to happen */
cm_alwon_gpmc_clkctrl_addr:
	.word CM_ALWON_GPMC_CLKCTRL
cm_alwon_gpio0_clkctrl_addr:
	.word CM_ALWON_GPIO_0_CLKCTRL
cm_alwon_gpio0_clkctrl_val:
	.word GPIO0_CLKCTRL_VAL
gpio0_cfg_addr:
	.word (TI816X_GPIO0_BASE + 0x134)
gpio0_data_addr:
	.word (TI816X_GPIO0_BASE + 0x13C)
gpio0_cfg_val:
	.word GPIO0_CFG_VAL
sram_pc_start:
	.word (SRAM0_START + 0x10000)
SRAM_STACK_GPMC:
	.word (SRAM0_START + 0x1000)
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
gpmc_a12_addr:
	.word GPMC_A12
gpmc_a13_addr:
	.word GPMC_A13
gpmc_a14_addr:
	.word GPMC_A14
gpmc_a15_addr:
	.word GPMC_A15
gpmc_a16_addr:
	.word GPMC_A16
gpmc_a17_addr:
	.word GPMC_A17
gpmc_a18_addr:
	.word GPMC_A18
gpmc_a19_addr:
	.word GPMC_A19
gpmc_a20_addr:
	.word GPMC_A20
gpmc_a21_addr:
	.word GPMC_A21
gpmc_a22_addr:
	.word GPMC_A22
gpmc_a23_addr:
	.word GPMC_A23
gpmc_a24_addr:
	.word GPMC_A24
gpmc_a25_addr:
	.word GPMC_A25
gpmc_a27_addr:
	.word GPMC_A27
sc1_rst_addr:
	.word  SC1_RST
ram_addr_mask:
	.word RAM_ADDR_MASK
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
	mov r10, #0x0 /* r10 has in_ddr used by s_init() */

#ifdef CONFIG_NOR_BOOT
	cmp r0, #0x08000000 /* check for running from NOR */
	beq ocmc_init_start /* if == then running from NOR */
	ands r0, r0, #0xC0000000 /* MSB 2 bits <> 0 then we are in ocmc or DDR */
	cmp r0, #0x40000000 /* if running from ocmc */
	beq nor_init_start /* if == skip ocmc init and jump to nor init */
	mov r10, #0x01 /* if <> we are running from DDR hence skip ddr init */
				   /* by setting in_ddr to 1 */
	b s_init_start /* and jump to s_init */
#else
	ands r0, r0, #0xC0000000 /* MSB 2 bits <> 0 then we are in ocmc or DDR */
	cmp r0, #0x80000000
	bne s_init_start
	mov r10, #0x01
	b s_init_start
#endif

ocmc_init_start:
	/**** enable ocmc 0 ****/
	/* CLKSTCTRL */
	ldr r5, cm_alwon_ocmc_0_clkstctrl_addr
	mov r2, #0x2
	str r2, [r5]
	/* wait for gpmc enable to settle */
 ocmc0_wait0:
	ldr r2, [r5]
	ands r2, r2, #0x00000100
	cmp r2, #0x00000100
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
	ands r2, r2, #0x00000100
	cmp r2, #0x00000100
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

nor_init_start:
	/* gpmc init */
	bl  cpy_nor_gpmc_code /* copy nor gpmc init code to sram */
	mov r0, pc
	add r0, r0, #12  /* 12 is for next three instructions */
	mov lr, r0	 /* gpmc init code in sram should return to s_init_start */
	ldr r0, sram_pc_start
	mov pc, r0	/* transfer ctrl to nor_gpmc_init() in sram */

s_init_start:
	mov r0, r10 /* passing in_ddr in r0 */
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
_s_init_start:
	.word s_init_start

SRAM_STACK:
	.word (SRAM0_START + SRAM0_SIZE - SRAM_GPMC_STACK_SIZE)

/* ROM code bug */
sysclk10_clksel_addr:
	.word (PRCM_BASE + 0x0324)
sysclk10_clksel_val:
	.word DDR_SYSCLK10_DIV

/* Documentation mismatch for CLK == ROM code bug */
ddr_pll_control_addr:
	.word DDRPLL_CTRL
ddr_pll_powerdown_reg:
	.word DDRPLL_PWD
ddr_div2_reg:
	.word DDRPLL_DIV2

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

	mrc	p15, 1, r0, c0, c0, 1		@ read clidr
	ands	r3, r0, #0x7000000		@ extract loc from clidr
	mov	r3, r3, lsr #23			@ left align loc bit field
	beq	finished_inval			@ if loc is 0, then no need to
						@ clean
	mov	r10, #0				@ start clean at cache level 0
inval_loop1:
	add	r2, r10, r10, lsr #1		@ work out 3x current cache
						@ level
	mov	r1, r0, lsr r2			@ extract cache type bits from
						@ clidr
	and	r1, r1, #7			@ mask of the bits for current
						@ cache only
	cmp	r1, #2				@ see what cache we have at
						@ this level
	blt	skip_inval			@ skip if no cache, or just
						@ i-cache
	mcr	p15, 2, r10, c0, c0, 0		@ select current cache level
						@ in cssr
	mov	r2, #0				@ operand for mcr SBZ
	mcr	p15, 0, r2, c7, c5, 4		@ flush prefetch buffer to
						@ sych the new cssr&csidr,
						@ with armv7 this is 'isb',
						@ but we compile with armv5
	mrc	p15, 1, r1, c0, c0, 0		@ read the new csidr
	and	r2, r1, #7			@ extract the length of the
						@ cache lines
	add	r2, r2, #4			@ add 4 (line length offset)
	ldr	r4, =0x3ff
	ands	r4, r4, r1, lsr #3		@ find maximum number on the
						@ way size
	clz	r5, r4				@ find bit position of way
						@ size increment
	ldr	r7, =0x7fff
	ands	r7, r7, r1, lsr #13		@ extract max number of the
						@ index size
inval_loop2:
	mov	r9, r4				@ create working copy of max
						@ way size
inval_loop3:
	orr	r11, r10, r9, lsl r5		@ factor way and cache number
						@ into r11
	orr	r11, r11, r7, lsl r2		@ factor index number into r11
	mcr	p15, 0, r11, c7, c6, 2		@ invalidate by set/way
	subs	r9, r9, #1			@ decrement the way
	bge	inval_loop3
	subs	r7, r7, #1			@ decrement the index
	bge	inval_loop2
skip_inval:
	add	r10, r10, #2			@ increment cache number
	cmp	r3, r10
	bgt	inval_loop1
finished_inval:
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

