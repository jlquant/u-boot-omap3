#
# config.mk
#
# Make configuration file for Netra Simulator.
#
# Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
#
# See file CREDITS for list of people who contributed to this
# project.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as 
# published by the Free Software Foundation version 2.
#
# This program is distributed "as is" WITHOUT ANY WARRANTY of any
# kind, whether express or implied; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#

#TEXT_BASE:= 0x40300000
TEXT_BASE:= 0x80e80000
CROSS_COMPILE:= arm-none-linux-gnueabi-
# Set libgcc patch to U-Boot implemenattion present in ./lib_arm directory. This
# is required to ensure that U-Boot implementation of libgcc functions is used,
# so that linking against toolchain provided library is avoided to prevent
# EABI mismatch errors (especially in NAND code).
USE_PRIVATE_LIBGCC = lib_arm
LDSCRIPT:=board/netra_evm/u-boot.lds
