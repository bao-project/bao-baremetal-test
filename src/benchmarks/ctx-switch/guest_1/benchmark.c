/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Sandro Pinto <sandro.pinto@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#include <core.h>
#include <stdlib.h>
#include <stdio.h>
#include <cpu.h>
#include <wfi.h>
#include <spinlock.h>
#include <plat.h>
#include <irq.h>
#include <uart.h>
#include <timer.h>
#include <bao.h>
#include <cycle_counter.h>

volatile struct {
    uint32_t context_switch_end_cnt;
} *shared_mem = (void*)0xFE170000;

void benchmark_entry(void){
    unsigned long before;
    unsigned long after;
    unsigned long elapsed;
    unsigned c = 1000;
    while(c--){
        cycle_counter_prepare();
        before = cycle_counter_get();
        bao_hypercall(BAO_YIELD_HYPCALL_ID);
        after = shared_mem->context_switch_end_cnt;
        elapsed = after - before;
    }
    printf("Ctx switch:\t%u\n", elapsed);
    printf("finished\n");
    while(1) wfi();
}
