#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct av1_decoder_model_info_s {void* frame_presentation_time_length_minus_1; void* buffer_removal_time_length_minus_1; void* num_units_in_decoding_tick; void* buffer_delay_length_minus_1; } ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 void* bs_read (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool av1_parse_decoder_model_info(bs_t *p_bs, struct av1_decoder_model_info_s *p_dm)
{
    p_dm->buffer_delay_length_minus_1 = bs_read(p_bs, 5);
    p_dm->num_units_in_decoding_tick = bs_read(p_bs, 32);
    p_dm->buffer_removal_time_length_minus_1 = bs_read(p_bs, 5);
    p_dm->frame_presentation_time_length_minus_1 = bs_read(p_bs, 5);
    return true;
}