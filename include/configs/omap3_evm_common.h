/*
 * Common configuration settings for the TI OMAP3 EVM board.
 *
 * Copyright (C) 2006-2010 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __OMAP3_EVM_COMMON_H
#define __OMAP3_EVM_COMMON_H

#define CONFIG_ARCH_CPU_INIT	1

/*
 * High level configuration options
 */
#define CONFIG_ARMCORTEXA8	1	/* This is an ARM V7 CPU core */
#define CONFIG_OMAP		1	/* in a TI OMAP core */
#define CONFIG_OMAP34XX		1	/* which is a 34XX */
#define CONFIG_OMAP3430		1	/* which is in a 3430 */
#define CONFIG_OMAP3_EVM	1	/* working with EVM */
#define CONFIG_SDRC		1	/* chip has SDRC controller */
#define CONFIG_OMAP3_MICRON_DDR	1
#define CONFIG_TWL4030_POWER	1

/*
 * Get cpu and chip specific definitions
 */
#include <asm/arch/cpu.h>
#include <asm/arch/omap3.h>

#undef CONFIG_USE_IRQ			/* no support for IRQs */

/*
 * Clock related definitions
 */
#define V_OSCK			26000000	/* Clock output from T2 */
#define V_SCLK			(V_OSCK >> 1)

/*
 * OMAP3 has 12 GP timers, they can be driven by the system clock
 * (12/13/16.8/19.2/38.4MHz) or by 32KHz clock. We use 13MHz (V_SCLK).
 * This rate is divided by a local divisor.
 */
#define CONFIG_SYS_TIMERBASE		OMAP34XX_GPT2
#define CONFIG_SYS_PTV			2	/* Divisor: 2^(PTV+1) => 8 */
#define CONFIG_SYS_HZ			1000

/*
 * Size of malloc() pool
 */
#define CONFIG_ENV_SIZE			(128 << 10)	/* 128 KiB */
							/* Sector */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + (128 << 10))
#define CONFIG_SYS_GBL_DATA_SIZE	128	/* bytes reserved for */
						/* initial data */

/*
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
#define CONFIG_STACKSIZE	(128 << 10)	/* regular stack 128 KiB */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ	(4 << 10)	/* IRQ stack 4 KiB */
#define CONFIG_STACKSIZE_FIQ	(4 << 10)	/* FIQ stack 4 KiB */
#endif

/*
 * Physical Memory Map
 * Note 1: CS1 may or may not be populated
 * Note 2: SDRAM size is expected to be at least 32MB
 */
#define CONFIG_NR_DRAM_BANKS		2
#define PHYS_SDRAM_1			OMAP34XX_SDRC_CS0
#define PHYS_SDRAM_1_SIZE		(32 << 20)
#define PHYS_SDRAM_2			OMAP34XX_SDRC_CS1

/* Limits for memtest */
#define CONFIG_SYS_MEMTEST_START	(OMAP34XX_SDRC_CS0)
#define CONFIG_SYS_MEMTEST_END		(OMAP34XX_SDRC_CS0 + \
						0x01F00000) /* 31MB */

/*
 * SDRAM Bank Allocation method
 */
#define SDRC_R_B_C			1

/*
 * Default load address
 */
#define CONFIG_SYS_LOAD_ADDR		(OMAP34XX_SDRC_CS0)

/* -----------------------------------------------------------------------------
 * Hardware drivers
 * -----------------------------------------------------------------------------
 */

/*
 * NS16550 Configuration
 */
#define V_NS16550_CLK			48000000	/* 48MHz (APLL96/2) */

#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
#define CONFIG_SYS_NS16550_CLK		V_NS16550_CLK
#define CONFIG_SYS_NS16550_COM1		OMAP34XX_UART1

/*
 * Serial console configuration
 */
#define CONFIG_CONS_INDEX		1
#define CONFIG_SERIAL1			1		/* UART1 on OMAP3 EVM */
#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{4800, 9600, 19200, 38400, 57600,\
					115200}

/*
 * I2C
 */
#define CONFIG_HARD_I2C			1
#define CONFIG_SYS_I2C_SPEED		100000
#define CONFIG_SYS_I2C_SLAVE		1
#define CONFIG_SYS_I2C_BUS		0
#define CONFIG_SYS_I2C_BUS_SELECT	1
#define CONFIG_DRIVER_OMAP34XX_I2C	1

/*
 * PISMO support
 */
#define PISMO1_NAND_SIZE		GPMC_SIZE_128M
#define PISMO1_ONEN_SIZE		GPMC_SIZE_128M

/* Max number of sectors on one chip */
#define CONFIG_SYS_MAX_FLASH_SECT	520

/* Max number of flash banks */
#define CONFIG_SYS_MAX_FLASH_BANKS	2

#define CONFIG_SYS_FLASH_BASE		boot_flash_base

/* Monitor at start of flash */
#define CONFIG_SYS_MONITOR_BASE		CONFIG_SYS_FLASH_BASE
#define CONFIG_SYS_ONENAND_BASE		ONENAND_MAP
#define CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* Reserve 2 sectors */

#define CONFIG_SYS_ENV_SECT_SIZE	boot_flash_sec
#define CONFIG_ENV_OFFSET		boot_flash_off
#define CONFIG_ENV_ADDR			boot_flash_env_addr

/*
 * Start location of environment
 */
#define ONENAND_ENV_OFFSET		0x260000
#define SMNAND_ENV_OFFSET		0x260000

/*
 * NAND
 */
/* Physical address to access NAND */
#define CONFIG_SYS_NAND_ADDR		NAND_BASE

/* Physical address to access NAND at CS0 */
#define CONFIG_SYS_NAND_BASE		NAND_BASE

/* Max number of NAND devices */
#define CONFIG_SYS_MAX_NAND_DEVICE	1

/* Timeout values (in ticks) */
#define CONFIG_SYS_FLASH_ERASE_TOUT	(100 * CONFIG_SYS_HZ)
#define CONFIG_SYS_FLASH_WRITE_TOUT	(100 * CONFIG_SYS_HZ)

/* Flash banks JFFS2 should use */
#define CONFIG_SYS_MAX_MTD_BANKS	(CONFIG_SYS_MAX_FLASH_BANKS + \
						CONFIG_SYS_MAX_NAND_DEVICE)

#define CONFIG_SYS_JFFS2_MEM_NAND
#define CONFIG_SYS_JFFS2_FIRST_BANK	CONFIG_SYS_MAX_FLASH_BANKS
#define CONFIG_SYS_JFFS2_NUM_BANKS	1

#define CONFIG_JFFS2_NAND
/* nand device jffs2 lives on */
#define CONFIG_JFFS2_DEV		"nand0"
/* Start of jffs2 partition */
#define CONFIG_JFFS2_PART_OFFSET	0x680000
/* Size of jffs2 partition */
#define CONFIG_JFFS2_PART_SIZE		0xf980000


#ifndef __ASSEMBLY__
extern unsigned int boot_flash_base;
extern volatile unsigned int boot_flash_env_addr;
extern unsigned int boot_flash_off;
extern unsigned int boot_flash_sec;
extern unsigned int boot_flash_type;
#endif

/* -----------------------------------------------------------------------------
 * Board specific
 * -----------------------------------------------------------------------------
 */
#define CONFIG_SYS_NO_FLASH

/* -----------------------------------------------------------------------------
 * U-boot features
 * -----------------------------------------------------------------------------
 */
#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_REVISION_TAG

#define CONFIG_MISC_INIT_R

#define CONFIG_SYS_PROMPT		"OMAP3_EVM # "
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#define CONFIG_SYS_MAXARGS		16	/* max args for a command */

/* Size of Console IO Buffer */
#define CONFIG_SYS_CBSIZE		256

/* Size of print buffer */
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
						sizeof(CONFIG_SYS_PROMPT) + 16)

/* Size of bootarg buffer */
#define CONFIG_SYS_BARGSIZE		(CONFIG_SYS_CBSIZE)

#define CONFIG_BOOTFILE			uImage

#endif /* __OMAP3_EVM_COMMON_H */
