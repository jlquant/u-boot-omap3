/*
 * timer.c
 *
 * TI816X SoC timer control.
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

#include <common.h>
#include <asm/io.h>

#include <asm/arch/hardware.h>

/* Up counter */
#define TIMER_LOAD_VAL		0

/* macro to read the 32 bit timer */
#define TIMER_REG(offset)	(CONFIG_SYS_TIMERBASE + offset)

static ulong timestamp;
static ulong lastdec;

#ifdef CONFIG_CPU_CORTEXA8
int interrupt_init(void)
#else
int timer_init(void)
#endif
{
	int ptv = 0;
	/* TODO: Select clock source? */
	/* TODO: Determine 'ptv' value */

	writel(TIMER_LOAD_VAL, TIMER_REG(REG_TIMER_TLDR));
	writel((ptv << TCLR_PTV_SHIFT) | TCLR_PRE
			| TCLR_AR | TCLR_ST, TIMER_REG(REG_TIMER_TCLR));

	reset_timer_masked();	/* init the timestamp and lastinc value */

	return 0;
}

/*
 * timer without interrupts
 */
void reset_timer(void)
{
	reset_timer_masked();
}

ulong get_timer(ulong base)
{
	return get_timer_masked() - base;
}

void set_timer(ulong t)
{
	timestamp = t;
}

/* delay x useconds AND perserve advance timstamp value  */
void __udelay(unsigned long usec)
{
}

void reset_timer_masked(void)
{
	/* reset time */
	/* lastdec = READ_TIMER;*/  /* capure current decrementer value time */
	timestamp = 0;	       /* start "advancing" time stamp from 0 */
}

ulong get_timer_masked(void)
{
	/* ulong now = READ_TIMER;*/		/* current tick value */

	return timestamp;
}

/* waits specified delay value and resets timestamp */
void udelay_masked(unsigned long usec)
{
}

/*
 * This function is derived from PowerPC code (read timebase as long long).
 * On ARM it just returns the timer value.
 */
unsigned long long get_ticks(void)
{
	return get_timer(0);
}

/*
 * This function is derived from PowerPC code (timebase clock frequency).
 * On ARM it returns the number of timer ticks per second.
 */
ulong get_tbclk(void)
{
	return CONFIG_SYS_HZ;
}

/*
 * Reset the cpu
 * 	- TODO: Use watchdog timer?
 * 	- TODO: Otherwise move to reset.S or something.
 */
void reset_cpu(ulong addr)
{
	while (1)
	;
}

#ifdef CONFIG_CPU_CORTEXA8
/* The functions below are taken from cpu/arm_cortexa8/omap3/board.c
 * TODO: Will move to an appropriate place later.
 */
/******************************************************************************
 * Dummy function to handle errors for EABI incompatibility
 *****************************************************************************/
void raise(void)
{
}

/******************************************************************************
 * Dummy function to handle errors for EABI incompatibility
 *****************************************************************************/
void abort(void)
{
}
#endif
