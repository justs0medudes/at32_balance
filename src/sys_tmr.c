/*
 * @file    sys_tmr.c
 * @brief   TMR hardware timer config
 * @author  justsomedudes
 * @date    20 Feb 2026
 */

#include "sys_tmr.h"

#include "at32f403a_407_tmr.h"

void sys_tmr2_init(void) {
    tmr_cnt_dir_set(TMR2, TMR_COUNT_UP);
    tmr_clock_source_div_set(TMR2, TMR_CLOCK_DIV1);
    tmr_period_buffer_enable(TMR2, FALSE);
    tmr_base_init(TMR2, 999, 239);

    tmr_sub_sync_mode_set(TMR2, FALSE);
    tmr_primary_mode_select(TMR2, TMR_PRIMARY_SEL_RESET);

    tmr_interrupt_enable(TMR2, TMR_OVF_INT, TRUE);
    tmr_counter_enable(TMR2, TRUE);

}