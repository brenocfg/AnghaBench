#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_ticks_per_picture_minus_1; int num_units_in_display_tick; unsigned int time_scale; int /*<<< orphan*/  equal_picture_interval; } ;
struct TYPE_5__ {TYPE_1__ timing_info; int /*<<< orphan*/  timing_info_present_flag; } ;
typedef  TYPE_2__ av1_OBU_sequence_header_t ;

/* Variables and functions */

bool AV1_get_frame_rate(const av1_OBU_sequence_header_t *p_seq,
                        unsigned *num, unsigned *den)
{
    if(!p_seq->timing_info_present_flag ||
       !p_seq->timing_info.equal_picture_interval) /* need support for VFR */
        return false;
    *num = (1 + p_seq->timing_info.num_ticks_per_picture_minus_1) *
           p_seq->timing_info.num_units_in_display_tick;
    *den = p_seq->timing_info.time_scale;
    return true;
}