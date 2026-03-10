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
#include <arch_events.h>

#define TIMER_INTERVAL   (TIME_MS(1))
#define TIMER_CYCLES     (PMU_FREQ_HZ / TIMER_FREQ) * TIMER_INTERVAL
#define WARMUP_SAMPLES   10
#define NUM_SAMPLES      1000

volatile unsigned warmup_remaining = WARMUP_SAMPLES;
volatile unsigned samples_remaining = NUM_SAMPLES;
static volatile uint32_t done = 0;

unsigned long irq_lat_events_samples[NUM_SAMPLES];
unsigned long irq_lat_timer_samples[NUM_SAMPLES];
uint64_t next_tick;
uint64_t curr_time;


volatile uint8_t loop_buffer[10] = {0};

void timer_handler(unsigned int id)
{
    timer_disable();
    uint64_t now_pmu = events_get_cycle_count();
    curr_time = timer_get();
    now_pmu = now_pmu - TIMER_CYCLES;

    if (warmup_remaining > 0) {
        warmup_remaining--;
    } else if (samples_remaining > 0) {
        irq_lat_events_samples[NUM_SAMPLES - samples_remaining] = now_pmu;
        irq_lat_timer_samples[NUM_SAMPLES - samples_remaining] = curr_time - next_tick;
        samples_remaining--;
        if (samples_remaining == 0) done = 1;
    }

    events_reset_cycle_count();
    timer_enable();
    next_tick = timer_set(TIMER_INTERVAL);
}

void benchmark_entry(void)
{
    irq_set_handler(TIMER_IRQ_ID, timer_handler);
    irq_set_prio(TIMER_IRQ_ID, TIMER_IRQ_PRIO);
    irq_enable(TIMER_IRQ_ID);

    events_start();
    events_enable_cycle_count();

    timer_enable();
    next_tick = timer_set(TIMER_INTERVAL);
    events_reset_cycle_count();

    while (!done){
        for(size_t i = 0; i < sizeof(loop_buffer); i++){
            loop_buffer[i] = i;
        }
    }

    for (unsigned i = 0; i < NUM_SAMPLES; i++) {
        // printf("[SAMPLE]\t%llu\n", (unsigned long long)irq_lat_events_samples[i]);
        printf("[SAMPLE]\t%llu\n", (unsigned long long)irq_lat_timer_samples[i]);
    }
}

