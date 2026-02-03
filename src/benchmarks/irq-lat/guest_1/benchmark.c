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

#define TIMER_INTERVAL (TIME_MS(1))
#define NUM_SAMPLES 1000

volatile unsigned c = 1000;
volatile unsigned long irq_lat = 0;
volatile unsigned long irq_lat_samples[NUM_SAMPLES] = {0};

void timer_handler(unsigned int id){
    char str[50];
    unsigned long latency = timer_get() - TIMER_INTERVAL;
    irq_lat_samples[NUM_SAMPLES - c] = latency;
    if(c>0){
        c--;
        timer_set(TIMER_INTERVAL);
    }
}

void benchmark_entry(void){
    timer_enable();
    irq_set_handler(TIMER_IRQ_ID, timer_handler);
    irq_enable(TIMER_IRQ_ID);
    timer_set(TIMER_INTERVAL);
    while(c){ }

    for(unsigned int i=NUM_SAMPLES; i>0; i--){
        print("Sample %u:\t%u\n", i, irq_lat_samples[NUM_SAMPLES - i]);
    }
}
