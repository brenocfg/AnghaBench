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
struct TYPE_5__ {int seq_profile; TYPE_1__* operating_points; } ;
typedef  TYPE_2__ av1_OBU_sequence_header_t ;
struct TYPE_4__ {int seq_level_idx; int seq_tier; } ;

/* Variables and functions */

void AV1_get_profile_level(const av1_OBU_sequence_header_t *p_seq,
                           int *pi_profile, int *pi_level, int *pi_tier)
{
    *pi_profile = p_seq->seq_profile;
    *pi_level = p_seq->operating_points[0].seq_level_idx;
    *pi_tier = p_seq->operating_points[0].seq_tier;
}