#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {unsigned int i_frequency; int i_bandwidth; } ;
typedef  TYPE_3__ scan_tuner_config_t ;
struct TYPE_13__ {int i_min; int i_max; } ;
struct TYPE_12__ {int i_step; } ;
struct TYPE_15__ {TYPE_2__ bandwidth; TYPE_1__ frequency; scalar_t__ b_exhaustive; } ;
typedef  TYPE_4__ scan_parameter_t ;
struct TYPE_16__ {unsigned int i_index; } ;
typedef  TYPE_5__ scan_enumeration_t ;

/* Variables and functions */
 int Scan_Next_DVB_SpectrumExhaustive (TYPE_4__ const*,TYPE_5__*,TYPE_3__*,double*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ __MIN (int const,int const) ; 

__attribute__((used)) static int Scan_Next_DVBT( const scan_parameter_t *p_params, scan_enumeration_t *p_spectrum,
                           scan_tuner_config_t *p_cfg, double *pf_pos )
{
    if( p_params->b_exhaustive )
        return Scan_Next_DVB_SpectrumExhaustive( p_params, p_spectrum, p_cfg, pf_pos );

    unsigned i_frequency_step = p_params->frequency.i_step ? p_params->frequency.i_step : 166667;

    unsigned i_bandwidth_min = p_params->bandwidth.i_min ? p_params->bandwidth.i_min : 6;
    unsigned i_bandwidth_max = p_params->bandwidth.i_max ? p_params->bandwidth.i_max : 8;
    unsigned i_bandwidth_count = i_bandwidth_max - i_bandwidth_min + 1;

    static const int i_band_count = 2;
    static const struct
    {
        const char *psz_name;
        int i_min;
        int i_max;
    }
    band[2] =
    {
        { "VHF", 174, 230 },
        { "UHF", 470, 862 },
    };
    const int i_offset_count = 5;
    const int i_mhz = 1000000;

    /* We will probe the whole band divided in all bandwidth possibility trying 
     * i_offset_count offset around the position
     */
    for( ;; p_spectrum->i_index++ )
    {

        const int i_bi = p_spectrum->i_index % i_bandwidth_count;
        const int i_oi = (p_spectrum->i_index / i_bandwidth_count) % i_offset_count;
        const int i_fi = (p_spectrum->i_index / i_bandwidth_count) / i_offset_count;

        const int i_bandwidth = i_bandwidth_min + i_bi;
        int i;

        for( i = 0; i < i_band_count; i++ )
        {
            if( i_fi >= band[i].i_min && i_fi <= band[i].i_max )
                break;
        }
        if( i >=i_band_count )
        {
            if( i_fi > band[i_band_count-1].i_max )
            {
                p_spectrum->i_index++;
                return VLC_EGENERIC;
            }
            continue;
        }

        const unsigned i_frequency_min = band[i].i_min*i_mhz + i_bandwidth*i_mhz/2;
        const unsigned i_frequency_base = i_fi*i_mhz;

        if( i_frequency_base >= i_frequency_min && ( i_frequency_base - i_frequency_min ) % ( i_bandwidth*i_mhz ) == 0 )
        {
            const unsigned i_frequency = i_frequency_base + ( i_oi - i_offset_count/2 ) * i_frequency_step;

            p_cfg->i_frequency = i_frequency;
            p_cfg->i_bandwidth = i_bandwidth;

            int i_current = 0, i_total = 0;
            for( i = 0; i < i_band_count; i++ )
            {
                const int i_frag = band[i].i_max-band[i].i_min;

                if( i_fi >= band[i].i_min )
                    i_current += __MIN( i_fi - band[i].i_min, i_frag );
                i_total += i_frag;
            }

            *pf_pos = (double)( i_current + (double)i_oi / i_offset_count ) / i_total;
            p_spectrum->i_index++;
            return VLC_SUCCESS;
        }
    }
}