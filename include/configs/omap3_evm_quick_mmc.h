/*
 * Configuration settings for quick boot on OMAP3 EVM.
 * (Boot from MMC only)
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Author :
 *	Sanjeev Premi <premi@ti.com>
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

#ifndef __OMAP3_EVM_QUICK_MMC_H
#define __OMAP3_EVM_QUICK_MMC_H

#include "omap3_evm_common.h"

/*
 * MMC
 */
#define CONFIG_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_OMAP_HSMMC

#define CONFIG_DOS_PARTITION

/* -----------------------------------------------------------------------------
 * U-boot features
 * -----------------------------------------------------------------------------
 */
#define CONFIG_CMD_MMC
#define CONFIG_CMD_FAT

#define CONFIG_ENV_IS_NOWHERE

/* Boot immediately */
#define CONFIG_BOOTDELAY		0

/* Don't display messages on console */
#define CONFIG_SILENT_CONSOLE

/* -----------------------------------------------------------------------------
 * Exclude "extra" features
 * -----------------------------------------------------------------------------
 */

/*
 * Exclude support for unsupported OSes
 * (defined in config_default.h)
 */
#undef CONFIG_BOOTM_NETBSD
#undef CONFIG_BOOTM_RTEMS

/*
 * Exclude support for unused compression algorithms
 * (defined in config_default.h)
 */
#undef CONFIG_GZIP
#undef CONFIG_ZLIB

/* -----------------------------------------------------------------------------
 * Default environment
 * -----------------------------------------------------------------------------
 */

/* Additional environment settings
 * - Don't verify the kernel image
 */
#define CONFIG_EXTRA_ENV_SETTINGS	\
	"silent=1\0"	\
	"verify=no"

/* Default boot arguments
 * - Don't show messages on the console
 * - Set default console
 * - Set memory size
 * - Location of root filesystem
 */
#define CONFIG_BOOTARGS			\
	"quiet "			\
	"console=ttyO0,115200n8 "	\
	"mem=256M "			\
	"noinitrd "			\
	"root=/dev/mmcblk0p2 rw "	\
	"rootfstype=ext3 rootwait"

/* Default boot command */
#define CONFIG_BOOTCOMMAND			\
	"mmc rescan 0; "			\
	"fatload mmc 0 0x80000000 uImage; "	\
	"bootm 0x80000000;"

#endif /* __OMAP3_EVM_QUICK_MMC_H */
