/*
 * (C) Copyright 2006-2008
 * Texas Instruments.
 * Author :
 *	Manikandan Pillai <mani.pillai@ti.com>
 * Derived from Beagle Board and 3430 SDP code by
 *	Richard Woodruff <r-woodruff2@ti.com>
 *	Syed Mohammed Khasim <khasim@ti.com>
 *
 * Manikandan Pillai <mani.pillai@ti.com>
 *
 * Configuration settings for the TI OMAP3 EVM board.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

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

/*
 * select serial console configuration
 */
#define CONFIG_CONS_INDEX		1
#define CONFIG_SERIAL1			1	/* UART1 on OMAP3 EVM */
#define CONFIG_SYS_NS16550_COM1		OMAP34XX_UART1
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

/*
 * MMC
 */
#define CONFIG_MMC			1
#define CONFIG_OMAP3_MMC		1
#define CONFIG_DOS_PARTITION		1

/*
 * USB
 *
 * Enable CONFIG_MUSB_HCD for Host functionalities e.g. MSC, keyboard
 * Enable CONFIG_MUSB_UDD for Device functionalities.
 */
#define CONFIG_USB_OMAP3		1
#define CONFIG_MUSB_HCD			1
/* #define CONFIG_MUSB_UDC		1 */

#ifdef CONFIG_USB_OMAP3

#ifdef CONFIG_MUSB_HCD
#define CONFIG_CMD_USB

#define CONFIG_USB_STORAGE
#define CONGIG_CMD_STORAGE
#define CONFIG_CMD_FAT

#ifdef CONFIG_USB_KEYBOARD
#define CONFIG_SYS_USB_EVENT_POLL
#define CONFIG_PREBOOT			"usb start"
#endif /* CONFIG_USB_KEYBOARD */

#endif /* CONFIG_MUSB_HCD */

#ifdef CONFIG_MUSB_UDC
/* USB device configuration */
#define CONFIG_USB_DEVICE		1
#define CONFIG_USB_TTY			1
#define CONFIG_SYS_CONSOLE_IS_IN_ENV	1

/* Change these to suit your needs */
#define CONFIG_USBD_VENDORID		0x0451
#define CONFIG_USBD_PRODUCTID		0x5678
#define CONFIG_USBD_MANUFACTURER	"Texas Instruments"
#define CONFIG_USBD_PRODUCT_NAME	"EVM"
#endif /* CONFIG_MUSB_UDC */

#endif /* CONFIG_USB_OMAP3 */

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

/* Define the board revision statically */
/* #define CONFIG_STATIC_BOARD_REV	OMAP3EVM_BOARD_GEN_2 */


/* -----------------------------------------------------------------------------
 * U-boot features
 * -----------------------------------------------------------------------------
 */
#define CONFIG_SYS_LONGHELP		1
#define CONFIG_SYS_HUSH_PARSER		1
#define CONFIG_SYS_PROMPT		"OMAP3_EVM # "
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#define CONFIG_SYS_MAXARGS		16	/* max args for a command */

#define CONFIG_DISPLAY_CPUINFO		1
#define CONFIG_DISPLAY_BOARDINFO	1

#define CONFIG_MISC_INIT_R		1

#define CONFIG_ENV_OVERWRITE		1
#define CONFIG_AUTO_COMPLETE		1

#define CONFIG_CMDLINE_TAG		1
#define CONFIG_SETUP_MEMORY_TAGS	1
#define CONFIG_INITRD_TAG		1
#define CONFIG_REVISION_TAG		1

/*
 * Size of Console IO Buffer
 */
#define CONFIG_SYS_CBSIZE		256

/*
 * Size of print buffer
 */
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
						sizeof(CONFIG_SYS_PROMPT) + 16)

/*
 * Size of bootarg buffer
 */
#define CONFIG_SYS_BARGSIZE		(CONFIG_SYS_CBSIZE)

/*
 * Common commands
 */
#include <config_cmd_default.h>

#define CONFIG_CMD_EXT2		/* EXT2 Support			*/
#define CONFIG_CMD_FAT		/* FAT support			*/
#define CONFIG_CMD_JFFS2	/* JFFS2 Support		*/

#define CONFIG_CMD_I2C		/* I2C serial bus support	*/
#define CONFIG_CMD_MMC		/* MMC support			*/
#define CONFIG_CMD_NAND		/* NAND support			*/
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING

#undef CONFIG_CMD_FLASH		/* flinfo, erase, protect	*/
#undef CONFIG_CMD_FPGA		/* FPGA configuration Support	*/
#undef CONFIG_CMD_IMI		/* iminfo			*/
#undef CONFIG_CMD_IMLS		/* List all found images	*/

/*
 * Additional definitions that depend on chosen commands
 */
/* NAND */
#if defined(CONFIG_CMD_NAND)
#define CONFIG_NAND_OMAP_GPMC
#define GPMC_NAND_ECC_LP_x16_LAYOUT	1
#define CONFIG_ENV_IS_IN_NAND
#elif defined(CONFIG_CMD_ONENAND)
#define CONFIG_ENV_IS_IN_ONENAND	1
#endif

/* Ethernet (SMSC9115 from SMSC9118 family) */
#if defined(CONFIG_CMD_NET)

#define CONFIG_NET_MULTI
#define CONFIG_SMC911X
#define CONFIG_SMC911X_32_BIT
#define CONFIG_SMC911X_BASE		0x2C000000

/* BOOTP fields */
#define CONFIG_BOOTP_SUBNETMASK		0x00000001
#define CONFIG_BOOTP_GATEWAY		0x00000002
#define CONFIG_BOOTP_HOSTNAME		0x00000004
#define CONFIG_BOOTP_BOOTPATH		0x00000010

#endif /* (CONFIG_CMD_NET) */

/*
 * Environment and boot command
 */
#define CONFIG_BOOTDELAY		10
#define CONFIG_BOOTFILE			uImage

#define CONFIG_EXTRA_ENV_SETTINGS \
	"loadaddr=0x82000000\0" \
	"usbtty=cdc_acm\0" \
	"console=ttyO0,115200n8\0" \
	"mmcargs=setenv bootargs console=${console} " \
		"root=/dev/mmcblk0p2 rw " \
		"rootfstype=ext3 rootwait\0" \
	"nandargs=setenv bootargs console=${console} " \
		"root=/dev/mtdblock4 rw " \
		"rootfstype=jffs2\0" \
	"loadbootscript=fatload mmc 0 ${loadaddr} boot.scr\0" \
	"bootscript=echo Running bootscript from mmc ...; " \
		"source ${loadaddr}\0" \
	"loaduimage=fatload mmc 0 ${loadaddr} uImage\0" \
	"mmcboot=echo Booting from mmc ...; " \
		"run mmcargs; " \
		"bootm ${loadaddr}\0" \
	"nandboot=echo Booting from nand ...; " \
		"run nandargs; " \
		"onenand read ${loadaddr} 280000 400000; " \
		"bootm ${loadaddr}\0" \

#define CONFIG_BOOTCOMMAND \
	"if mmc init; then " \
		"if run loadbootscript; then " \
			"run bootscript; " \
		"else " \
			"if run loaduimage; then " \
				"run mmcboot; " \
			"else run nandboot; " \
			"fi; " \
		"fi; " \
	"else run nandboot; fi"

#endif /* __CONFIG_H */
