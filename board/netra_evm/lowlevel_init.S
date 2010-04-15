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

#if !defined(CONFIG_SYS_NAND_BOOT)
/**************************************************************************
 * cpy_nor_gpmc_code: relocates nor gpmc init code into ocmc0 where its 
 * safer to execute
 *************************************************************************/
.global cpy_nor_gpmc_code 
 cpy_nor_gpmc_code:
	/* Copy NOR GPMC init code into SRAM */
	adr r0, nor_gpmc_init     /* get addr of nor gpmc init code */
	mov r2, #384        	/* r2 size to copy (div by 32 bytes) */
	ldr r1, sram0_start     /* r1 <- dest address (passed in) */
	add r2, r2, r0      /* r2 <- source end address */
next2:
	ldmia   r0!, {r3 - r10}     /* copy from source address [r0] */
	stmia   r1!, {r3 - r10}     /* copy to   target address [r1] */
	cmp r0, r2          /* until source end address [r2] */
	bne next2
	mov pc, lr          /* back to caller */

/* ***************************************************************************
 *  nor_gpmc_init: - Init GPMC for NOR on CS0, executed from SRAM.
 *
 *  R0 - used for saving SP, hence do not use it anywhere
 * TODO
 ****************************************************************************/
.global nor_gpmc_init 
 nor_gpmc_init:
	mov r0, sp
	ldr sp, SRAM_STACK_GPMC
	stmfd sp!, {r4 - r6}
	stmfd sp!, {ip}

	/* do GPMC init: TODO */
	/*	.
		.
		.
		.
	*/ 
		
	ldmfd sp!, {ip}
	ldmfd sp!, {r4 - r6}
	mov sp, r0

	mov pc, lr      /* back to caller*/

/* these constants need to be close for PIC code */
/* The Nor has to be in the Flash Base CS0 for this condition to happen */
sram0_start:
	.word SRAM0_START
SRAM_STACK_GPMC:
	.word (SRAM0_START + SRAM0_SIZE)
flash_cfg1_addr:
    .word (GPMC_CONFIG_CS0_BASE + GPMC_CONFIG1)
flash_cfg3_addr:
    .word (GPMC_CONFIG_CS0_BASE + GPMC_CONFIG3)
flash_cfg3_val:
    .word SPNOR_GPMC_CONFIG3
flash_cfg4_addr:
    .word (GPMC_CONFIG_CS0_BASE + GPMC_CONFIG4)
flash_cfg4_val:
    .word SPNOR_GPMC_CONFIG4
flash_cfg5_val:
    .word SPNOR_GPMC_CONFIG5
flash_cfg5_addr:
    .word (GPMC_CONFIG_CS0_BASE + GPMC_CONFIG5)

.globl lowlevel_init
 lowlevel_init:

#if 0
	ldr sp, SRAM_STACK
	str ip, [sp]    /* stash old link register */
	mov ip, lr      /* save link reg across call */
#endif

	bl  cpy_nor_gpmc_code /* go copy nor gpmc init code to sram */
	adr r0, gpmc_init_ret
	mov lr, r0	 /* gpmc init code in sram should return to gpmc_init_ret */
	ldr r0, sram0_start
	mov pc, r0	/* transfer ctrl to nor_gpmc_init() in sram */ 

gpmc_init_ret:	
#if 0
	ldr ip, [sp]    /* restore save ip */
	mov lr, ip      /* restore link reg */
#endif

	/* back to arch calling code */
	mov pc, lr

	/* the literal pools origin */
	.ltorg

SRAM_STACK:
	.word (SRAM0_START + SRAM0_SIZE - SRAM_STACK_GPMC_SIZE)

#else /* no NOR hence lowlevel_init() should simply return */

.globl lowlevel_init
 lowlevel_init:
	/* back to arch calling code */
	mov pc, lr

#endif
