/*
 * ti816x_evm.h
 *
 * TI816X SoC EVM Config file.
 *
 * Copyright (C) 2009, Texas Instruments, Incorporated
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

#ifndef __CONFIG_TI816X_EVM_H
#define __CONFIG_TI816X_EVM_H


#define CONFIG_ENV_SIZE			0x2000


/*
 * These features are unsupported
 */
#undef CONFIG_USE_IRQ
#undef CONFIG_NET_MULTI
#undef CONFIG_NET_RETRY_COUNT

/*
 * Size of malloc() pool
 */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + (32 * 1024))
#define CONFIG_SYS_GBL_DATA_SIZE	128	/* size in bytes reserved for
						   initial data */

#define CONFIG_OMAP3_SPI
#define CONFIG_MTD_DEVICE
#define CONFIG_SPI_FLASH
#define CONFIG_SPI_FLASH_WINBOND
#define CONFIG_CMD_SF
#define CONFIG_CMD_NAND     /* NAND support         */
#define CONFIG_NAND_TI816X



#ifdef CONFIG_NOR_BOOT
# undef CONFIG_CMD_NAND
# undef CONFIG_NAND_TI816X
# ifdef CONFIG_SYS_MALLOC_LEN
#  undef CONFIG_SYS_MALLOC_LEN
# endif
# define CONFIG_SYS_FLASH_USE_BUFFER_WRITE 1
# define CONFIG_SYS_MALLOC_LEN		(0x100000)
# define CONFIG_SYS_FLASH_CFI
# define CONFIG_FLASH_CFI_DRIVER
# define CONFIG_FLASH_CFI_MTD
# define CONFIG_SYS_MAX_FLASH_SECT	512
# define CONFIG_SYS_MAX_FLASH_BANKS	1
# define CONFIG_SYS_FLASH_BASE		(0x08000000)
# define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_FLASH_BASE
# define CONFIG_ENV_IS_IN_FLASH		1
# define NOR_SECT_SIZE			(128 * 1024)
# define CONFIG_SYS_ENV_SECT_SIZE	(NOR_SECT_SIZE)
# define CONFIG_ENV_SECT_SIZE	(NOR_SECT_SIZE)
# define CONFIG_ENV_OFFSET		(2 * NOR_SECT_SIZE)
# define CONFIG_ENV_ADDR		(CONFIG_SYS_FLASH_BASE + CONFIG_ENV_OFFSET)
#endif

/* Only one the following two options (DDR3/DDR2) should be enabled */
//#define CONFIG_TI816X_EVM_DDR3			/* Configure DDR3 in U-Boot */
#define CONFIG_TI816X_EVM_DDR2			/* Configure DDR2 in U-Boot */
#define CONFIG_TI816X_TWO_EMIF		1
#define CONFIG_MISC_INIT_R
#define CONFIG_TI816X_ASCIIART			/* The eye */

#define CONFIG_CMDLINE_TAG        	1	/* enable passing of ATAGs  */
#define CONFIG_SETUP_MEMORY_TAGS  	1
#define CONFIG_INITRD_TAG	  	1	/* Required for ramdisk support */

/*
 * Board NAND Info.
 */

#ifdef CONFIG_NAND_TI816X
# define GPMC_NAND_ECC_LP_x16_LAYOUT 	1
# define NAND_BASE			(0x08000000)	/* FIXME not sure */
# define CONFIG_SYS_NAND_ADDR		NAND_BASE	/* physical address */
							/* to access nand */
# define CONFIG_SYS_NAND_BASE		NAND_BASE	/* physical address */
							/* to access nand at */
							/* CS0 */
# define CONFIG_SYS_MAX_NAND_DEVICE	1		/* Max number of NAND */
							/* devices */
# define CONFIG_ENV_IS_IN_NAND		1

# ifdef CONFIG_ENV_IS_IN_NAND
#  define CONFIG_SYS_MAX_FLASH_SECT	520		/* max number of sectors in a chip */
#  define CONFIG_SYS_MAX_FLASH_BANKS	2		/* max number of flash banks */
#  define CONFIG_SYS_MONITOR_LEN	(256 << 10)	/* Reserve 2 sectors */
#  define CONFIG_SYS_FLASH_BASE		boot_flash_base
/* Monitor at start of flash */
#  define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_FLASH_BASE
#  define MNAND_ENV_OFFSET		0x260000	/* environment starts here */
#  define CONFIG_SYS_ENV_SECT_SIZE	boot_flash_sec
#  define CONFIG_ENV_OFFSET		boot_flash_off
#  define CONFIG_ENV_ADDR		MNAND_ENV_OFFSET
#  define CONFIG_CMD_SAVEENV
#  define CONFIG_NOFLASH
#  undef CONFIG_ENV_IS_NOWHERE
# else
//#  define CONFIG_SYS_MONITOR_BASE	TEXT_BASE
#  define CONFIG_NOFLASH				/* Revisit: For boot modes without NOR */
# endif
#endif

#ifndef __ASSEMBLY__
extern unsigned int boot_flash_base;
extern volatile unsigned int boot_flash_env_addr;
extern unsigned int boot_flash_off;
extern unsigned int boot_flash_sec;
extern unsigned int boot_flash_type;
#endif


/* U-Boot default commands */
#include <config_cmd_default.h>

#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING

#ifdef CONFIG_NOETH
# undef CONFIG_CMD_NET
#endif

/*
 * REVISIT: If we move this before including config_cmd_default.h, we won't need
 * to explicitly remove CONFIG_CMD_IMLS.
 */
#ifdef CONFIG_NOFLASH
# define CONFIG_SYS_NO_FLASH
# undef CONFIG_CMD_IMLS
#endif

#define CONFIG_CMD_ASKENV
#define CONFIG_VERSION_VARIABLE
#define CONFIG_BOOTDELAY		3		/* set to negative value for no autoboot */
#define CONFIG_SYS_AUTOLOAD		"no"
#define	CONFIG_EXTRA_ENV_SETTINGS \
	"verify=yes\0" \
	"bootfile=uImage\0" \
	"ramdisk_file=ramdisk.gz\0" \
	"loadaddr=0x81000000\0" \
	"loadaddr_ramdisk=0x82000000\0" \
	"console=ttyS2,115200n8\0" \
	"bootargs_misc=mem=256M earlyprintk\0" \
	"ethaddr=00:00:00:00:00:00\0" \
	"nfsserver=0.0.0.0\0" \
	"serverip=0.0.0.0\0" \
	"nfspath=/opt/psp/nfs_root\0" \
	"addip=setenv bootargs ${bootargs} ip=${ipaddr}:${nfsserver}:${gatewayip}:${netmask}:${hostname}::off\0" \
	"addnfs=setenv bootargs ${bootargs} root=/dev/nfs nfsroot=${nfsserver}:${nfspath},nolock rw\0" \
	"ramdisk_root=/dev/ram rw\0" \
	"jffs2_root=/dev/mtdblock3 rw\0" \
	"rootfstype_nand=jffs2\0" \
	"bootargs_ramdisk=setenv bootargs console=${console} ${boot_misc} " \
		"root=${ramdisk_root} " \
		"initrd=${loadaddr_ramdisk},32M " \
		"ip=dhcp\0" \
	"bootargs_nand_jffs2=setenv bootargs console=${console} ${bootargs_misc} noinitrd " \
		"root=${nandroot_jffs2} " \
		"rootfstype=${nandrootfstype} "\
		"ip=dhcp\0" \
	"bootargs_nfs=setenv bootargs console=${console} ${bootargs_misc} noinitrd " \
		"root=/dev/nfs " \
		"nfsroot=${nfsserver}:${nfspath},nolock rw " \
		"ip=dhcp\0" \
	"network_boot_ramdisk=echo Downloading kernel and ramdisk image from TFTP server and booting...; " \
		"run bootargs_ramdisk; " \
		"dhcp; " \
		"tftp ${loadaddr} ${bootfile}; " \
		"tftp ${loadaddr_ramdisk} ${ramdisk_file}; " \
		"bootm ${loadaddr}\0" \
	"network_boot_nfs=echo Downloading kernel image from TFTP server and using NFS filesystem...;" \
		"run bootargs_nfs;" \
		"dhcp; " \
		"tftp ${loadaddr} ${bootfile}; " \
		"bootm ${loadaddr}\0" \
	"nand_boot_ramdisk=echo Booting from NAND using RAMDISK...; " \
		"run bootargs_ramdisk; " \
		"nand read ${loadaddr} 280000 170000; " \
		"nand read ${loadddr_ramdisk} 6C0000 320000; "\
		"bootm ${loadaddr}\0" \
	"nand_boot_jffs2=echo Booting from NAND using jffs2 filesystem...; " \
		"run bootargs_nand_jffs2; " \
		"nand read ${loadaddr} 280000 170000; " \
		"bootm ${loadaddr}\0" \

/*
 * Hardware drivers
 */


/**
 * Physical Memory Map
 */
#define CONFIG_NR_DRAM_BANKS		2		/* we have 2 banks of DRAM */
#define PHYS_DRAM_1			0x80000000	/* DRAM Bank #1 */
#define PHYS_DRAM_1_SIZE		0x40000000	/* 1 GB */
#define PHYS_DRAM_2			0xC0000000	/* DRAM Bank #2 */
#define PHYS_DRAM_2_SIZE		0x40000000	/* 1 GB */


/**
 * Platform/Board specific defs
 */
#define CONFIG_SYS_CLK_FREQ		27000000	/* TODO: Check! */
#define CONFIG_SYS_TIMERBASE		0x4802E000	/* TODO: Check! */
/* Timer 0 is secure timer. We use Timer 1. The clk freq is 27Mhz */

/*
 * NS16550 Configuration
 */
#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
#define CONFIG_SYS_NS16550_CLK		(48000000)
#define CONFIG_SYS_NS16550_COM1		0x48024000	/* Base EVM has UART2 */

#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{ 110, 300, 600, 1200, 2400, \
4800, 9600, 14400, 19200, 28800, 38400, 56000, 57600, 115200 }

/*
 * select serial console configuration
 */
#define CONFIG_SERIAL1			1
#define CONFIG_CONS_INDEX		1

#if 0
/**
 * Environment settings
 */
#ifdef CONFIG_NOFLASH
# ifndef CONFIG_ENV_IS_IN_NAND
#  define CONFIG_ENV_IS_NOWHERE
# endif
#endif
#endif
/* allow overwriting serial config and ethaddr */
#define CONFIG_ENV_OVERWRITE

/*
 * Miscellaneous configurable options
 */
/* Undef to save memory */
#define CONFIG_SYS_LONGHELP
/* Monitor Command Prompt */
#define CONFIG_SYS_PROMPT		"TI8168_EVM#"
/* Console I/O Buffer Size */
#define CONFIG_SYS_CBSIZE		512
/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE \
					+ sizeof(CONFIG_SYS_PROMPT) + 16)
/* max number of command args */
#define CONFIG_SYS_MAXARGS		32
/* Boot Argument Buffer Size */
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE

/* memtest works on 8 MB in DRAM after skipping 32MB from start addr of ram disk*/
#define CONFIG_SYS_MEMTEST_START	(PHYS_DRAM_1 + (64 *1024 *1024))

#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START \
					+ (8 * 1024 * 1024))

#undef  CONFIG_SYS_CLKS_IN_HZ				/* everything, incl board info, in Hz */

#define CONFIG_SYS_LOAD_ADDR		0x80700000  	/* Default load address */

#define CONFIG_SYS_HZ			1000        	/* 1ms clock */

#if defined(CONFIG_CMD_NET)
# define CONFIG_DRIVER_TI_EMAC
# define CONFIG_MII
# define CONFIG_BOOTP_DEFAULT
# define CONFIG_BOOTP_DNS
# define CONFIG_BOOTP_DNS2
# define CONFIG_BOOTP_SEND_HOSTNAME
# define CONFIG_BOOTP_GATEWAY
# define CONFIG_BOOTP_SUBNETMASK
# define CONFIG_NET_RETRY_COUNT 10
# define CONFIG_NET_MULTI
#endif

/* EEPROM definitions for EEPROM */
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN		3
#define CONFIG_SYS_I2C_EEPROM_ADDR		0x50
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	6
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	20

#define	CONFIG_CMD_I2C

#define CONFIG_HARD_I2C			1
#define CONFIG_SYS_I2C_SPEED		100000
#define CONFIG_SYS_I2C_SLAVE		1
#define CONFIG_SYS_I2C_BUS		0
#define CONFIG_SYS_I2C_BUS_SELECT	1
#define	CONFIG_DRIVER_TI816X_I2C	1

#endif	  /* ! __CONFIG_TI816X_EVM_H */
