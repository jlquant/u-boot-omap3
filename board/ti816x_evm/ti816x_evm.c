/*
 * ti816x_evm.c
 *
 * TI816X SoC EVM/SIM setup ile.
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
#include <asm/cache.h>
#include <asm/arch/clocks.h>
#include <asm/arch/cpu.h>
#include <asm/arch/hardware.h>
#include <asm/arch/mem.h>
#include <asm/arch/mux.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/nand.h>
#include <linux/mtd/nand_ecc.h>
#include <nand.h>


#define __raw_readl(a)    (*(volatile unsigned int *)(a))
#define __raw_writel(v, a) (*(volatile unsigned int *)(a) = (v))
#define __raw_readw(a)    (*(volatile unsigned short *)(a))
#define __raw_writew(v, a) (*(volatile unsigned short *)(a) = (v))

DECLARE_GLOBAL_DATA_PTR;

void peripheral_enable(void);

#ifdef CONFIG_TI816X_VOLT_SCALE
#define NUM_VOLT_DATA 4

struct voltage_scale_data {
	u32 efuse_data;
	u8  gpio_val;
};

/*
 * TODO: Populate this table based on silicon characterization data
 */
static struct voltage_scale_data ti816x_volt_scale_data[NUM_VOLT_DATA] = {
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
};

static u8 voltage_scale_lookup(u32 efuse_data)
{
	int i;
	u8  gpio_val = 0;

	for (i=0; i < NUM_VOLT_DATA; i++) {
		if (ti816x_volt_scale_data[i].efuse_data == efuse_data) {
			gpio_val = ti816x_volt_scale_data[i].gpio_val;
			break;
		}
	}
	return gpio_val;
}

/*
 * The routine reads the efuse register and programs the GPIO
 * to adjust the TPS40041 core voltage.
 * Assumptions:
 * 1. The efuse data is programmed into TI816X_SMRT_SCALE_ADDR
 * 2. The efuse and gpio clocks are already enabled
 */
static void voltage_scale_init(void)
{
	u32 sr_efuse_data;
	u8  gpio_val;
	u32 gpio_reg_val;

	sr_efuse_data = __raw_readl(TI816X_SMRT_SCALE_ADDR);

	gpio_val = voltage_scale_lookup(sr_efuse_data);
	if (gpio_val != 0) {
		gpio_val &= 0xF;

		/* Enable Output on GPIO0[0:3] */
		gpio_reg_val = __raw_readl(TI816X_GPIO0_BASE + 0x134);
		gpio_reg_val &= 0xF;
		__raw_writel(gpio_reg_val, TI816X_GPIO0_BASE + 0x134);

		/* Clear any existing output data */
		gpio_reg_val = __raw_readl(TI816X_GPIO0_BASE + 0x190);
		gpio_reg_val &= 0xF;
		__raw_writel(gpio_reg_val, TI816X_GPIO0_BASE + 0x190);

		/* Program the GPIO to change the TPS40041 Voltage */
		gpio_reg_val = __raw_readl(TI816X_GPIO0_BASE + 0x194);
		gpio_reg_val &= gpio_val;
		__raw_writel(gpio_reg_val, TI816X_GPIO0_BASE + 0x194);
	}
}
#endif

/*******************************************************
 * Routine: delay
 * Description: spinning delay to use before udelay works
 ******************************************************/
static inline void delay(unsigned long loops)
{
	__asm__ volatile ("1:\n" "subs %0, %1, #1\n"
			  "bne 1b" : "=r" (loops) : "0"(loops));
}

/*
void udelay(unsigned long usecs)
{
	delay(usecs);
}
*/

/*
 * Basic board specific setup
 */
#ifndef CONFIG_TI816X_SIM
int board_init(void)
{
	u32 regVal;

	/* Get Timer and UART out of reset */

	/* UART softreset */
	regVal = __raw_readl(UART_SYSCFG);
	regVal |= 0x2;
	__raw_writel(regVal, UART_SYSCFG);
	while( (__raw_readl(UART_SYSSTS) & 0x1) != 0x1);

	/* Disable smart idle */
	regVal = __raw_readl(UART_SYSCFG);
	regVal |= (1<<3);
	__raw_writel(regVal, UART_SYSCFG);

	/* 
	 * XXX: Most of the code below should already be in the driver and
 	 * should be arranged with board/SoC level init
	 */
#if 0
	__raw_writel((regVal | 0x80), UART_LCR);
	__raw_writel(0, UART_DLL);
	__raw_writel(0, UART_DLH);

	__raw_writel(0xBF, UART_LCR);

	regVal = __raw_readl(UART_EFR);
	__raw_writel((regVal | 0x10), UART_EFR);

	__raw_writel(0x00, UART_LCR);

	regVal = __raw_readl(UART_MCR);
	__raw_writel((regVal | 0x40), UART_MCR);

	regVal = __raw_readl(UART_SCR);
	__raw_writel((regVal | 0x40), UART_SCR);

	__raw_writel(0x4D, UART_TCR);

	regVal = __raw_readl(UART_FCR);
	__raw_writel((regVal | 0x06), UART_FCR);

	regVal = __raw_readl(UART_FCR);
	__raw_writel(0, UART_FCR);

	__raw_writel(0xBF, UART_LCR);

	regVal = __raw_readl(UART_EFR);
	__raw_writel((regVal & 0x3F), UART_EFR);

	regVal = __raw_readl(UART_MCR);
	__raw_writel((regVal & 0xBF), UART_MCR);

	regVal = __raw_readl(UART_EFR);
	__raw_writel((regVal & 0xEF), UART_EFR);

	regVal = __raw_readl(UART_LCR);
	__raw_writel((regVal & 0x7F), UART_LCR);

	regVal = __raw_readl(UART_LCR);
	__raw_writel((regVal & 0xF8), UART_LCR);

	regVal = __raw_readl(UART_LCR);
	__raw_writel((regVal | 0x03), UART_LCR);

	regVal = __raw_readl(UART_LCR);
	__raw_writel((regVal & 0xF7), UART_LCR);

	regVal = __raw_readl(UART_LCR);
	__raw_writel((regVal & 0xFB), UART_LCR);

	regVal = __raw_readl(UART_LCR);

	__raw_writel((regVal | 0x80), UART_LCR);
	__raw_writel(0x07, UART_DLL);
	__raw_writel(((0 & 0xFF00)>>8), UART_DLH);

	regVal = __raw_readl(UART_LCR);
	__raw_writel((regVal & 0x7F), UART_LCR);

	regVal = __raw_readl(UART_MDR);
	__raw_writel((regVal & 0xF8), UART_MDR);

#endif
	gd->bd->bi_arch_number = MACH_TYPE_TI816X;

	/* address of boot parameters */
	gd->bd->bi_boot_params = PHYS_DRAM_1 + 0x100;

	gpmc_init(); 

	return 0;
}
#else
int board_init(void)
{
	gd->bd->bi_arch_number = MACH_TYPE_TI816X;

	/* address of boot parameters */
	gd->bd->bi_boot_params = PHYS_DRAM_1 + 0x100;

	return 0;
}
#endif

#ifdef CONFIG_DRIVER_TI_EMAC
int board_eth_init(bd_t *bis)
{
	/* TODO : read MAC address from EFUSE */
	davinci_emac_initialize();
	return 0;
}
#endif

/*
 * Configure DRAM banks
 *
 * Description: sets uboots idea of sdram size
 */
int dram_init(void)
{
	/* Fill up board info */
	gd->bd->bi_dram[0].start = PHYS_DRAM_1;
	gd->bd->bi_dram[0].size = PHYS_DRAM_1_SIZE;

	gd->bd->bi_dram[1].start = PHYS_DRAM_2;
	gd->bd->bi_dram[1].size = PHYS_DRAM_2_SIZE;

	return 0;
}


/*************************************************************
 *  get_device_type(): tell if GP/HS/EMU/TST
 *************************************************************/
u32 get_device_type(void)
{
	int mode;
	mode = __raw_readl(CONTROL_STATUS) & (DEVICE_MASK);
	return(mode >>= 8);
}

/************************************************
 * get_sysboot_value(void) - return SYS_BOOT[4:0]
 ************************************************/
u32 get_sysboot_value(void)
{
	int mode;
	mode = __raw_readl(CONTROL_STATUS) & (SYSBOOT_MASK);
	return mode;
}

/*************************************************************
 * Routine: get_mem_type(void) - returns the kind of memory connected
 * to GPMC that we are trying to boot form. Uses SYS BOOT settings.
 *************************************************************/
u32 get_mem_type(void)
{
	/* TODO: VB_ Check the values over here
	u32   mem_type = get_sysboot_value();
	switch (mem_type){
            case 0:
            case 2:
            case 4:
            case 16:
            case 22:    return GPMC_ONENAND;

            case 1:
            case 12:
            case 15:
            case 21:
            case 27:    return GPMC_NAND;

            case 3:
            case 6:     return MMC_ONENAND;

            case 8:
            case 11:
            case 14:
            case 20:
            case 26:    return GPMC_MDOC;

            case 17:
            case 18:
            case 24:	return MMC_NAND;

            case 7:
            case 10:
            case 13:
            case 19:
            case 25:
            default:    return GPMC_NOR;
        }*/
}

u32 is_cpu_family(void)
{
	u32 cpuid = 0, cpu_family = 816;

	/* TODO:VB__Revsisit
	__asm__ __volatile__("mrc p15, 0, %0, c0, c0, 0":"=r"(cpuid));
	if ((cpuid & 0xf) == 0x0) {
		cpu_family = CPU_OMAP34XX;
	} else {
		cpuid = __raw_readl(OMAP34XX_CONTROL_ID);
		}
	}
	*/

	return cpu_family;
}

/******************************************
 * cpu_is_ti816x(void) - returns true for ti816x
 ******************************************/
u32 cpu_is_ti816x(void)
{
	return 1;
}

#ifdef CONFIG_TI816X_EVM_DDR

/*********************************************************************
 * config_ti816x_sdram_ddr() - Init DDR on TI816X EVM
 *********************************************************************/
void config_ti816x_sdram_ddr(void)
{
	__raw_writel(0x2, CM_DEFAULT_FW_CLKCTRL);	/*Enable the EMIF FireWall Clocks*/
	__raw_writel(0x2, CM_DEFAULT_L3_FAST_CLKSTCTRL);/*Enable the Power Domain Transition of L3 Fast Domain Peripheral*/
	__raw_writel(0x2, CM_DEFAULT_EMIF_0_CLKCTRL); /*Enable EMIF0 Clock*/
	__raw_writel(0x2, CM_DEFAULT_EMIF_1_CLKCTRL); /*Enable EMIF1 Clock*/
	__raw_writel(0x2, CM_DEFAULT_DMM_CLKCTRL); /*Enable EMIF1 Clock*/
	wait_on_value(0x300, 0x300, CM_DEFAULT_L3_FAST_CLKSTCTRL, LDELAY);	/*Poll for L3_FAST_GCLK  & DDR_GCLK  are active*/
	wait_on_value(0x2, 0x2, CM_DEFAULT_EMIF_0_CLKCTRL, LDELAY);		/*Poll for Module is functional*/
	wait_on_value(0x2, 0x2, CM_DEFAULT_EMIF_1_CLKCTRL, LDELAY);		/*Poll for Module is functional*/
	wait_on_value(0x2, 0x2, CM_DEFAULT_DMM_CLKCTRL, LDELAY);		/*Poll for Module is functional*/

	/*Program the DMM to Access EMIF0*/
	__raw_writel(0x80600100, DMM_LISA_MAP__0);
	__raw_writel(0x80600100, DMM_LISA_MAP__1);

	/*Program the DMM to Access EMIF1*/
	__raw_writel(0xC0600200, DMM_LISA_MAP__2);
	__raw_writel(0xC0600200, DMM_LISA_MAP__3);

	/*Enable Tiled Access*/
	__raw_writel(0x80000000, DMM_PAT_BASE_ADDR);

	/*Program EMIF0 CFG Registers*/
	__raw_writel(0x4, EMIF4_0_DDR_PHY_CTRL_1);
	__raw_writel(0x4, EMIF4_0_DDR_PHY_CTRL_1_SHADOW);
	__raw_writel(0x0666a391, EMIF4_0_SDRAM_TIM_1);
	__raw_writel(0x0666a391, EMIF4_0_SDRAM_TIM_1_SHADOW);
	__raw_writel(0x001631fa, EMIF4_0_SDRAM_TIM_2);
	__raw_writel(0x001631fa, EMIF4_0_SDRAM_TIM_2_SHADOW);
	__raw_writel(0x10000618, EMIF4_0_SDRAM_REF_CTRL);
	__raw_writel(0x10000618, EMIF4_0_SDRAM_REF_CTRL_SHADOW);
	__raw_writel(0x4080143A, EMIF4_0_SDRAM_CONFIG);


	/*Program EMIF1 CFG Registers*/
	__raw_writel(0xA, EMIF4_1_DDR_PHY_CTRL_1);
	__raw_writel(0xA, EMIF4_1_DDR_PHY_CTRL_1_SHADOW);
	__raw_writel(0x0666a391, EMIF4_1_SDRAM_TIM_1);
	__raw_writel(0x0666a391, EMIF4_1_SDRAM_TIM_1_SHADOW);
	__raw_writel(0x001631fa, EMIF4_1_SDRAM_TIM_2);
	__raw_writel(0x001631fa, EMIF4_1_SDRAM_TIM_2_SHADOW);
	__raw_writel(0x10000618, EMIF4_1_SDRAM_REF_CTRL);
	__raw_writel(0x10000618, EMIF4_1_SDRAM_REF_CTRL_SHADOW);
	__raw_writel(0x4080143A, EMIF4_1_SDRAM_CONFIG);

}
#endif /* CFG_TI816X_EVM_DDR */


/*
 * TI816X specific functions
 */
static void main_pll_init_ti816x(u32 sil_index, u32 clk_index)
{
	dpll_param *ptr;

	/* Getting the base address of MAIN DPLL param table*/
	ptr = (dpll_param *)get_main_dpll_param();

	/* Sequence to be followed:
	 * 1. Put the PLL in bypass mode by setting BIT2 in its ctrl reg
	 * 2. Write the values of N,P in the CTRL reg
	 * 3. Program the freq values, divider values for the required output in the Control module reg
	 * 4. Note: Loading the freq value requires a particular bit to be set in the freq reg.
	 * 4. Program the CM divider value in the CM module reg
	 * 5. Enable the PLL by setting the appropriate bit in the CTRL reg of the PLL
	 */

	 /* Nothing to done right now as the registers have been pre-loaded @ reset and
	  * by the ROM code also (if applicable). Retaining this function for future
	  */
}

static void ddr_pll_init_ti816x(u32 sil_index, u32 clk_index)
{
	struct dpll_per_36x_param *ptr;

	/* Getting the base address to DDR DPLL param table*/
	ptr = (struct dpll_per_36x_param *)get_ddr_dpll_param();

	/* Nothing to done right now as the registers have been pre-loaded @ reset and
	 * by the ROM code also (if applicable). Retaining this function for future
	 */

}

static void video_pll_init_ti816x(u32 sil_index, u32 clk_index)
{
	dpll_param *ptr;

	/* Getting the base address to video DPLL param table*/
	ptr = (dpll_param *)get_video_dpll_param();

	/* Nothing to done right now as the registers have been pre-loaded @ reset and
	 * by the ROM code also (if applicable). Retaining this function for future
	 */
}

static void audio_pll_init_ti816x(u32 sil_index, u32 clk_index)
{
	dpll_param *ptr;

	/* Getting the base address to audio DPLL param table*/
	ptr = (dpll_param *)get_audio_dpll_param();

	/* Nothing to done right now as the registers have been pre-loaded @ reset and
	 * by the ROM code also (if applicable). Retaining this function for future
	 */
}

/******************************************************************************
 * prcm_init() - inits clocks for PRCM as defined in clocks.h
 *   -- called from SRAM, or Flash (using temp SRAM stack).
 *****************************************************************************/
void prcm_init(void)
{
	/* TODO:VB__Do we need sil_index for future? */
	u32 clk_index = 0, sil_index = 0;

	if (is_cpu_family() == CPU_TI816X) {
		//main_pll_init_ti816x(clk_index, sil_index);
		//ddr_pll_init_ti816x(clk_index, sil_index);
		//video_pll_init_ti816x(clk_index, sil_index);
		//audio_pll_init_ti816x(clk_index, sil_index);
	}

	/* Waiting for the clks to get stable will be done in individual funcs */

	/* With clk freqs setup to desired values, enable the required peripherals */
	peripheral_enable();
}

/**********************************************************
 * Routine: s_init
 * Description: Does early system init of muxing and clocks.
 * - Called at time when only stack is available.
 **********************************************************/

void s_init(void)
{
	l2_cache_enable();	/* Not strictly needed since A8 comes up with L2 enabled */
	watchdog_init();	/* Just a stub right now */
	set_muxconf_regs();	/* Just a stub right now */
	prcm_init();		/* Just a stub right now */
	//config_ti816x_sdram_ddr();
#ifdef CONFIG_TI816X_VOLT_SCALE
	/* FIXME: Probably need to move this as first step in init */ 
	//voltage_scale_init();
#endif
}

/*******************************************************
 * Routine: misc_init_r
 * Description: Init ethernet (done here so udelay works)
 ********************************************************/
int misc_init_r (void)
{
	#ifdef CONFIG_TI816X_ASCIIART
	int i = 0, j = 0;
	char ti816x[23][79] = {
":,;;:;:;;;;;;;;r;;:,;;:;:;;;;;;;;:,;;:;:;;;;;;;;:,;;:;:;;;;;;;;:;;;;;;;;:,;;:;:",
";,;:::;;;;r;;;rssiSiS552X5252525259GX2X9hX9X9XX2325S55252i5:,;;:;:;;;;;;;;:,;;:",
";:;;;;;;;rrssSsS52S22h52299GGAAMHMM#BBH#B#HMM#HMBA&&XX2255S2S5Si:,;;:;:;;;;;;;;",
";:;;r;;rsrrriiXS5S329&A&MH#BMB#A&9XXA252GXiSXX39AAMMMBB&G22S5i2SSiiiisi:,;;:;:;",
";;;;;r;rr2iisiih393HB#B#AA99i22irrrX3X52AGsisss2Xii2299HBMA&X2S5S5iSiisSsi:,;;:",
"r:r;rrsrsihXSi2&##MHB&Ahh3AGHGA9G9h&#H##@@@##MAMMXXX9SSS29&&HGGX2i5iisiiisisi:,",
";;rrrrsSiiiA&ABH&A9GAGhAhBAMHA9HM@@@@@@@@@@@@@@@@@@@HHhAh2S2SX9&Gh22SSiisiiisii",
"r:rrssisiS2XM##&h3AGAX&3GG3Ssr5H@M#HM2; ;2X&&&MHMB###GBB#B&XXSSs529XX55iSsisisi",
"r;rsrisSi2XHAhX99A3XXG&&XS;:,rH#HGhAS   @@@@3rs2XBM@@A552&&AHA2XiisSS252SSsisSs",
"r;issi5S22&&3iSSX292&hXsr;;:;h@&G339&S9@@@@2@MA&9&HB##Xris29ABMAAX2ir;rsSi5iss5",
"rrsSi2XhG&9GXh399&X99i;;;;;;r#H&293H9X#@@@@@@@B&9GhAH@XrrsrsiXABHB&HG2rr;rrSiSi",
";:rsisS599&AA9XG&3A35r;:::;,;BMh&&2iX5A@@@@@@@&392X5GB2;;;r;iSX393A##A&Xi:::rsi",
";:rss552222X553&XHMhir;;::,:,h#HhGSXhG3#@@@@#AXXS2XAHA;::;;;;ss55XShBA3239r:,;;",
"r;ii2S5SSi2i53hirsh2srr::,,,,;MMXX359&Ah3h&Si59SX99A#i:,::::;;sri2,.2r;:SGAr;,:",
";:;rrrrssiriXGSi::shs;;;,,,:,,rBBA9h5s5h5iS5isi2SAHB5:,,,:::;rrs5&SrisSX5Srrr:,",
";,r;;;;rsriSSrrrr;;5Xrr;;,:,,.,;9AA2SsisS5323XXXG9&i:.,,::;;r;;;srrrrrr;;:;::::",
":,;r;r;rrissrrr;:;::;s;;;;,:,,..,r293h222hXXAAGGGX;:,,,:,:,::;:;::,:,,,,...,,,,",
";,;;;;rrrrrrrrirr;,.,,:::::::,,,,.,;SX&ABAB2hhXir:,,.,,.,,:,,,,..,,,..,..,,,..:",
":.:;:;;;:;;;;r;rrs;:.. ,,:::::,:,:,,.::rrsrr;;,,.......,..,....,,,,,,,...,.,,:,",
":.:::,::::::;;r;rrr;:.......,.,.,,:::,,...............,,::.,,,,:,::,,:,:,,,:,;:",
",.::,:,,,,,;;;;;;;;r;;::,..............................;;;:;::::,:::::::,:,:,,,",
": ,,:,,,,,,,,,,,,,:;rrr;;:;,,,,,,,::,.,.:.,.,;s,:;;;;:;:;;;;;::::,:::,:::,:,:,:",
",.,,,,,,,...,,.,,....................................:,............:,,,:,:,,,,,"};

	for (i = 0; i<23; i++)
	{
		for(j = 0; j<79; j++)
			printf("%c",ti816x[i][j]);
			printf("\n");
	}
	printf("\n");
	#endif

	return 0;
}

/******************************************************
 * Routine: wait_for_command_complete
 * Description: Wait for posting to finish on watchdog
 ******************************************************/
void wait_for_command_complete(unsigned int wd_base)
{
	/*
	int pending = 1;
	do {
		pending = __raw_readl(wd_base + WWPS);
	} while (pending);
	*/
}

/****************************************
 * Routine: watchdog_init
 * Description: Shut down watch dogs
 *****************************************/
void watchdog_init(void)
{
	/* There are 2 watch dogs WD0=Secure, WD1=MPU. WD0 is
	 * either taken care of by ROM (HS/EMU) or not accessible (GP).
	 * We need to take care of WD1-MPU or take a PRCM reset.
	 */

	/* TODO: VB__Skipping this section for now
	sr32(CM_FCLKEN_WKUP, 5, 1, 1);
	sr32(CM_ICLKEN_WKUP, 5, 1, 1);
	wait_on_value(BIT5, 0x20, CM_IDLEST_WKUP, 5);
	*/ /* some issue here */

	/*
	__raw_writel(WD_UNLOCK1, WD1_BASE + WSPR);
	wait_for_command_complete(WD1_BASE);
	__raw_writel(WD_UNLOCK2, WD1_BASE + WSPR);
	*/
}

/*****************************************************************
 * Routine: peripheral_enable
 * Description: Enable the clks & power for perifs (TIMER1, UART0,...)
 *
 * TODO:VB__This we can probably split as ones needed to get U-Boot
 * and the ones needed to get the kernel up
 *
 ******************************************************************/
void peripheral_enable(void)
{
#ifndef CONFIG_TI816X_SIM
	/* DMTimers */
	__raw_writel(0x2, CM_ALWON_L3_SLOW_CLKSTCTRL);

	/* We need to select the proper clk input for the timers
	 * On reset the path is setup from external 32KHz clk
	 * Enable the clk and then setup the correct path
	 */

	/* First we need to enable the modules and setup the clk path
	 * Then the timers need to be configured by writing to their registers
	 * Note that to access the timer registers we need the module to be
	 * enabled which is what we do in the first step
	 */

	/* Note on Timers:
	 * There are 8 timers(0-7) out of which timer 0 is a secure timer.
	 * Timer 0 mux should not be changed
	 *
	 * For other timers, there are 3 inputs TCLKIN, 32KHz (external clk or SYSCLK18?) and CLKIN(27MHz)
	 *
	 * We select CLKIN and use that
	 */

	/* TIMER 1 */
	__raw_writel(0x2, CM_ALWON_TIMER_1_CLKCTRL);

	/* Selects CLKIN (27MHz) */
	__raw_writel(0x2, CM_TIMER1_CLKSEL);

	while(((__raw_readl(CM_ALWON_L3_SLOW_CLKSTCTRL) & (0x80000<<1)) >> (19+1)) != 1);

	while(((__raw_readl(CM_ALWON_TIMER_1_CLKCTRL) & 0x30000)>>16) !=0);


	__raw_writel(0x2,(DM_TIMER1_BASE_ADDR + 0x54));
	while(__raw_readl(DM_TIMER1_BASE_ADDR + 0x10) & 1);

	__raw_writel(0x1,(DM_TIMER1_BASE_ADDR + 0x38));
	//while(__raw_readl(DM_TIMER1_BASE_ADDR + 0x38) !=0x1);


	/* UARTs */
	/* Note: The clock has been set to correct rate before this step */
	__raw_writel(0x2, CM_ALWON_UART_0_CLKCTRL);
	while(__raw_readl(CM_ALWON_UART_0_CLKCTRL) != 0x2);

	__raw_writel(0x2, CM_ALWON_UART_1_CLKCTRL);
	while(__raw_readl(CM_ALWON_UART_1_CLKCTRL) != 0x2);

	__raw_writel(0x2, CM_ALWON_UART_2_CLKCTRL);
	while(__raw_readl(CM_ALWON_UART_2_CLKCTRL) != 0x2);

	while((__raw_readl(CM_ALWON_L3_SLOW_CLKSTCTRL) & 0x2100) != 0x2100);

	/* eFuse */
	__raw_writel(0x2, CM_ALWON_CUST_EFUSE_CLKCTRL);
	while(__raw_readl(CM_ALWON_CUST_EFUSE_CLKCTRL) != 0x2);

	/* GPIO0 */
	__raw_writel(0x2, CM_ALWON_GPIO_0_CLKCTRL);
	while(__raw_readl(CM_ALWON_GPIO_0_CLKCTRL) != 0x2);

	__raw_writel((BIT(8)), CM_ALWON_GPIO_0_OPTFCLKEN_DBCLK);

	/* Ethernet */
	__raw_writel(0x2, CM_ETHERNET_CLKSTCTRL);
	__raw_writel(0x2, CM_ALWON_ETHERNET_0_CLKCTRL);
	__raw_writel(0x2, CM_ALWON_ETHERNET_1_CLKCTRL);
//	while(__raw_readl(CM_ALWON_ETHERNET_0_CLKCTRL) != 0x2);
//	while(__raw_readl(CM_ALWON_ETHERNET_0_CLKCTRL) != 0x2);
#endif
}

/* MUX setting */

#define 	MUX_VAL(OFFSET,VALUE)\
		__raw_writew((VALUE), TI816X_CTRL_BASE + (OFFSET));

#define		CP(x)	(CONTROL_PADCONF_##x)
/*
 * IEN  - Input Enable -- redundant?
 * IDIS - Input Disable -- redundant?
 * PTD  - Pull type Down
 * PTU  - Pull type Up
 * DIS  - Pull type selection is inactive
 * EN   - Pull type selection is active
 * M0   - Mode 0
 * The commented string gives the final mux configuration for that pin
 * All the pads come up in Mode 0 hence nothing to be done for now
 * To enable some other device other modes need to be given over here
 */
#define MUX_DEFAULT()\
	MUX_VAL(CP(UART0_RXD),        (PTD | DIS | M0)) \
	MUX_VAL(CP(UART0_TXD),        (PTD | DIS | M0)) \
	MUX_VAL(CP(UART0_RTSN),        (PTD | DIS | M0)) \
	MUX_VAL(CP(UART0_CTSN),        (PTD | DIS | M0)) \
	MUX_VAL(CP(UART0_DTRN),        (PTD | DIS | M0)) \
	MUX_VAL(CP(UART0_DSRN),        (PTD | DIS | M0)) \
	MUX_VAL(CP(UART0_DCDN),        (PTD | DIS | M0)) \
	MUX_VAL(CP(UART0_RIN),        (PTD | DIS | M0))

/**********************************************************
 * Routine: set_muxconf_regs
 * Description: Setting up the configuration Mux registers
 *              specific to the hardware.
 *********************************************************/
void set_muxconf_regs(void)
{
	/* Nothing to be done right now. Default is Mode 0 for all the pins */

	/* MUX_DEFAULT(); */
}

/* optionally do something like blinking LED */
void board_hang (void)
{ while (0) {};}


#ifdef CONFIG_NAND_TI816X 
/******************************************************************************
 * Command to switch between NAND HW and SW ecc
 *****************************************************************************/
static int do_switch_ecc(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
	if (argc != 2)
		goto usage;
	if (strncmp(argv[1], "hw", 2) == 0)
		ti816x_nand_switch_ecc(NAND_ECC_HW, 0);
	else if (strncmp(argv[1], "sw", 2) == 0)
		ti816x_nand_switch_ecc(NAND_ECC_SOFT, 0);
	else
		goto usage;

	return 0;

usage:
	printf ("Usage: nandecc %s\n", cmdtp->usage);
	return 1;
}

U_BOOT_CMD(
	nandecc, 2, 1,	do_switch_ecc,
	"switch NAND ECC calculation algorithm",
	"[hw/sw] - Switch between NAND hardware (hw) or software (sw) ecc algorithm"
);

#endif /* CONFIG_NAND_OMAP_GPMC */

