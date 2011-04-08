/*
 * Configuration settings for the TI OMAP3 EVM board.
 *
 * Copyright (C) 2006-2010 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Author :
 *	Manikandan Pillai <mani.pillai@ti.com>
 * Derived from Beagle Board and 3430 SDP code by
 *	Richard Woodruff <r-woodruff2@ti.com>
 *	Syed Mohammed Khasim <khasim@ti.com>
 *
 * Manikandan Pillai <mani.pillai@ti.com>
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

#ifndef __OMAP3EVM_CONFIG_H
#define __OMAP3EVM_CONFIG_H

#include "omap3_evm_common.h"

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

/* -----------------------------------------------------------------------------
 * Board specific
 * -----------------------------------------------------------------------------
 */
/* Detect the DIE ID */
#define CONFIG_OMAP3_DIE_ID

/* Define the board revision statically */
/* #define CONFIG_STATIC_BOARD_REV	OMAP3EVM_BOARD_GEN_2 */

/* -----------------------------------------------------------------------------
 * U-boot features
 * -----------------------------------------------------------------------------
 */
#define CONFIG_SYS_LONGHELP		1
#define CONFIG_SYS_HUSH_PARSER		1

#define CONFIG_DISPLAY_CPUINFO		1
#define CONFIG_DISPLAY_BOARDINFO	1

#define CONFIG_ENV_OVERWRITE		1
#define CONFIG_AUTO_COMPLETE		1

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

#endif /* __OMAP3EVM_CONFIG_H */
