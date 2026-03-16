/*
 * @file    sys_tmr.c
 * @brief   TMR hardware timer config
 * @author  justsomedudes
 * @date    20 Feb 2026
 */

#include "sys_tmr.h"
#include "at32f403a_407_tmr.h"

void sys_tmr1_init(void) {
    tmr_output_config_type tmr_output_struct;
    tmr_brkdt_config_type tmr_brkdt_config_struct;

    /* tmr1 configuration */
    /* time base configuration */
    tmr_base_init(TMR1, 6000, 0); // 120.000.000M/20.000Khz
    tmr_cnt_dir_set(TMR1, TMR_COUNT_TWO_WAY_1);

    /* channel 1, 2, 3 and 4 Configuration in output mode */
    tmr_output_default_para_init(&tmr_output_struct);
    tmr_output_struct.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_B;
    tmr_output_struct.oc_output_state = TRUE;
    tmr_output_struct.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
    tmr_output_struct.oc_idle_state = FALSE;
    tmr_output_struct.occ_output_state = TRUE;
    tmr_output_struct.occ_polarity = TMR_OUTPUT_ACTIVE_HIGH;
    tmr_output_struct.occ_idle_state = TRUE;

    /* channel 1 */
    tmr_output_channel_config(TMR1, TMR_SELECT_CHANNEL_1, &tmr_output_struct);
    tmr_channel_value_set(TMR1, TMR_SELECT_CHANNEL_1, TMR1->pr / 2);

    /* channel 2 */
    tmr_output_channel_config(TMR1, TMR_SELECT_CHANNEL_2, &tmr_output_struct);
    tmr_channel_value_set(TMR1, TMR_SELECT_CHANNEL_2, TMR1->pr / 2);

    /* channel 3 */
    tmr_output_channel_config(TMR1, TMR_SELECT_CHANNEL_3, &tmr_output_struct);
    tmr_channel_value_set(TMR1, TMR_SELECT_CHANNEL_3, TMR1->pr / 2);

    /* channel 4 */
    tmr_output_channel_config(TMR1, TMR_SELECT_CHANNEL_4, &tmr_output_struct);
    tmr_channel_value_set(TMR1, TMR_SELECT_CHANNEL_4, 1);

    /* automatic output enable, stop, dead time and lock configuration */
    tmr_brkdt_default_para_init(&tmr_brkdt_config_struct);
    tmr_brkdt_config_struct.brk_enable = FALSE;
    tmr_brkdt_config_struct.auto_output_enable = TRUE;
    tmr_brkdt_config_struct.deadtime = 48;
    tmr_brkdt_config_struct.fcsodis_state = TRUE;
    tmr_brkdt_config_struct.fcsoen_state = TRUE;
    tmr_brkdt_config_struct.brk_polarity = TMR_BRK_INPUT_ACTIVE_HIGH;
    tmr_brkdt_config_struct.wp_level = TMR_WP_LEVEL_3;
    tmr_brkdt_config(TMR1, &tmr_brkdt_config_struct);

    /* tmr1 output enable */
    tmr_output_enable(TMR1, TRUE);

    /* enable tmr1 */
    tmr_counter_enable(TMR1, TRUE);
}

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

void sys_tmr8_init(void) {
    tmr_output_config_type tmr_output_struct;
    tmr_brkdt_config_type tmr_brkdt_config_struct;

    /* tmr8 configuration */
    /* time base configuration */
    tmr_base_init(TMR8, 6000, 0); // 120.000.000M/20.000Khz
    tmr_cnt_dir_set(TMR8, TMR_COUNT_TWO_WAY_1);

    /* channel 1, 2, 3 and 4 Configuration in output mode */
    tmr_output_default_para_init(&tmr_output_struct);
    tmr_output_struct.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_B;
    tmr_output_struct.oc_output_state = TRUE;
    tmr_output_struct.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
    tmr_output_struct.oc_idle_state = TRUE;
    tmr_output_struct.occ_output_state = TRUE;
    tmr_output_struct.occ_polarity = TMR_OUTPUT_ACTIVE_HIGH;
    tmr_output_struct.occ_idle_state = TRUE;

    /* channel 1 */
    tmr_output_channel_config(TMR8, TMR_SELECT_CHANNEL_1, &tmr_output_struct);
    tmr_channel_value_set(TMR8, TMR_SELECT_CHANNEL_1, TMR8->pr / 2);

    /* channel 2 */
    tmr_output_channel_config(TMR8, TMR_SELECT_CHANNEL_2, &tmr_output_struct);
    tmr_channel_value_set(TMR8, TMR_SELECT_CHANNEL_2, TMR8->pr / 2);

    /* channel 3 */
    tmr_output_channel_config(TMR8, TMR_SELECT_CHANNEL_3, &tmr_output_struct);
    tmr_channel_value_set(TMR8, TMR_SELECT_CHANNEL_3, TMR8->pr / 2);

    /* channel 4 */
    tmr_output_channel_config(TMR8, TMR_SELECT_CHANNEL_4, &tmr_output_struct);
    tmr_channel_value_set(TMR8, TMR_SELECT_CHANNEL_4, 1);

    /* automatic output enable, break, dead time and lock configuration */
    tmr_brkdt_default_para_init(&tmr_brkdt_config_struct);
    tmr_brkdt_config_struct.brk_enable = FALSE;
    tmr_brkdt_config_struct.auto_output_enable = TRUE;
    tmr_brkdt_config_struct.deadtime = 48;
    tmr_brkdt_config_struct.fcsodis_state = TRUE;
    tmr_brkdt_config_struct.fcsoen_state = TRUE;
    tmr_brkdt_config_struct.brk_polarity = TMR_BRK_INPUT_ACTIVE_HIGH;
    tmr_brkdt_config_struct.wp_level = TMR_WP_LEVEL_3;
    tmr_brkdt_config(TMR8, &tmr_brkdt_config_struct);

    /* tmr8 output enable */
    tmr_output_enable(TMR8, TRUE);

    /* enable tmr8 */
    tmr_counter_enable(TMR8, TRUE);
}