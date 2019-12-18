#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {unsigned int i_frequency; int i_bandwidth; } ;
typedef  TYPE_3__ scan_tuner_config_t ;
struct TYPE_10__ {int i_max; int i_min; } ;
struct TYPE_9__ {int i_step; unsigned int i_max; unsigned int i_min; } ;
struct TYPE_12__ {TYPE_2__ bandwidth; TYPE_1__ frequency; } ;
typedef  TYPE_4__ scan_parameter_t ;
struct TYPE_13__ {unsigned int i_index; } ;
typedef  TYPE_5__ scan_enumeration_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int Scan_Next_DVB_SpectrumExhaustive( const scan_parameter_t *p_params, scan_enumeration_t *p_spectrum,
                                             scan_tuner_config_t *p_cfg, double *pf_pos )
{
    unsigned i_bandwidth_count = p_params->bandwidth.i_max - p_params->bandwidth.i_min + 1;
    unsigned i_frequency_step = p_params->frequency.i_step ? p_params->frequency.i_step : 166667;
    unsigned i_frequency_count = (p_params->frequency.i_max - p_params->frequency.i_min) / p_params->frequency.i_step;

    if( p_spectrum->i_index > i_frequency_count * i_bandwidth_count )
        return VLC_EGENERIC;

    const int i_bi = p_spectrum->i_index % i_bandwidth_count;
    const int i_fi = p_spectrum->i_index / i_bandwidth_count;

    p_cfg->i_frequency = p_params->frequency.i_min + i_fi * i_frequency_step;
    p_cfg->i_bandwidth = p_params->bandwidth.i_min + i_bi;

    *pf_pos = (double)p_spectrum->i_index / i_frequency_count;

    p_spectrum->i_index++;

    return VLC_SUCCESS;
}