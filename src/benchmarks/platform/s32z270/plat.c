/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */
#include <fences.h>
#include <cpu.h>
#include <plat_regs.h>

SYSREG_GEN_ACCESSORS(hactlr, 4, c1, c0, 1)
SYSREG_GEN_ACCESSORS(hactlr2, 4, c1, c0, 3)
SYSREG_GEN_ACCESSORS_MERGE(actlr_el2, hactlr, hactlr2) // hactlr
SYSREG_GEN_ACCESSORS(imp_periphregionr, 0, c15, c0, 0) // imp_periphregionr

volatile struct siul2_hw* siul2_0 = (struct siul2_hw*)SIUL2_0_BASE;
volatile struct mc_cgm_hw* mc_cgm_0 = (struct mc_cgm_hw*)MC_CGM_0_BASE;

extern void bsp_entrypoint(void);

static void plat_uart0_iomux(void)
{
    /* Configure IOMUX settings for console (UART TX Pin) */
    /* Configure SIUL2 settings for console (UART TX Pin) */
    siul2_0->MSCR[UART0_TX_PIN] = SIUL2_MSCR_TX;
    /* Configure SIUL2 settings for console (UART RX Pin) */
    siul2_0->MSCR[UART0_RX_PIN] = SIUL2_MSCR_RX;
    siul2_0->IMCR[SIUL2_IMCR_UART0_RX_OFF] = SIUL2_IMCR_RX;
}

static void plat_uart0_clock(void)
{
    /* Configure clock settings for console */
    /* Configure clock source for console (FIRC_CLK)*/
    mc_cgm_0->MUX_4_CSC = MC_CGM_0_MUX_4_CSC_SAFE;

    while ((mc_cgm_0->MUX_4_CSS & MC_CGM_0_MUX_4_CSS_SWIP) != 0);

    /* Enable divider */
    mc_cgm_0->MUX_4_DC_0 = MC_CGM_0_MUX_4_DC_0_DE;
}

void plat_early_init(void)
{
    uint64_t actlr = sysreg_actlr_el2_read();
    actlr |= ACTLR_PERIPHPREGIONR;
    sysreg_actlr_el2_write(actlr);

    uint32_t reg = sysreg_imp_periphregionr_read();
    reg |= IMP_PERIPHPREGIONR_ENABLEEL10 | IMP_PERIPHPREGIONR_ENABLEEL2;
    sysreg_imp_periphregionr_write(reg);

    ISB();

    /* Set counter div to zero */
    volatile uint32_t* rtu_gpr_cntdv = (volatile uint32_t*)RTU_GPR_CFG_CNTDV;
    *rtu_gpr_cntdv = 0;

    /* Set the timer frequency to 40MHz */
    sysreg_cntfrq_el0_write(40000000);
}

void plat_init(void)
{
    /* Configure UART0 IO pins */
    plat_uart0_iomux();
    /* Configure UART0 clock */
    plat_uart0_clock();
    /* Call BSP entrypoint to allow clock platform initialization to 1GHz */
    bsp_entrypoint();
}