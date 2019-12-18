#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_5__ {scalar_t__ profile_idc; } ;
struct TYPE_6__ {scalar_t__ general_level_idc; TYPE_1__ general; } ;
struct TYPE_7__ {TYPE_2__ profile_tier_level; } ;
typedef  TYPE_3__ hevc_sequence_parameter_set_t ;

/* Variables and functions */

bool hevc_get_sps_profile_tier_level( const hevc_sequence_parameter_set_t *p_sps,
                                      uint8_t *pi_profile, uint8_t *pi_level)
{
    if(p_sps->profile_tier_level.general.profile_idc)
    {
        *pi_profile = p_sps->profile_tier_level.general.profile_idc;
        *pi_level = p_sps->profile_tier_level.general_level_idc;
        return true;
    }
    return false;
}