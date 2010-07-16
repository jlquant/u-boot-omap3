#
# config.mk
#
# Make configuration file for TI816X
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

sinclude $(OBJTREE)/board/$(BOARDDIR)/config.tmp

TEXT_BASE = 0x80300000
# Upper 128KB (20000) for stack setup in start.S
CROSS_COMPILE:= arm-none-linux-gnueabi-
# Set libgcc patch to U-Boot implemenattion present in ./lib_arm directory. This
# is required to ensure that U-Boot implementation of libgcc functions is used,
# so that linking against toolchain provided library is avoided to prevent
# EABI mismatch errors (especially in NAND code).
#USE_PRIVATE_LIBGCC = lib_arm
LDSCRIPT:=board/ti/ti816x/u-boot.lds
