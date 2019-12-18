#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int i_frequency; scalar_t__ type; scalar_t__ i_bandwidth; } ;
typedef  TYPE_1__ scan_tuner_config_t ;

/* Variables and functions */
 scalar_t__ SCAN_DVB_T ; 
 int UINT32_MAX ; 

__attribute__((used)) static bool scan_tuner_config_StandardValidate( const scan_tuner_config_t *p_cfg )
{
    if( p_cfg->i_frequency == 0 ||
        p_cfg->i_frequency == UINT32_MAX / 10 ) /* Invalid / broken transponder info on French TNT */
        return false;

    if( p_cfg->type == SCAN_DVB_T && p_cfg->i_bandwidth == 0 )
        return false;

    return true;
}