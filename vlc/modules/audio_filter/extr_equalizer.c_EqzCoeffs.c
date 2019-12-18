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
struct TYPE_5__ {int i_band; TYPE_1__* band; } ;
typedef  TYPE_2__ eqz_config_t ;
struct TYPE_4__ {float f_frequency; float f_alpha; float f_beta; float f_gamma; } ;

/* Variables and functions */
 int EQZ_BANDS_MAX ; 
 scalar_t__ M_PI ; 
 float cosf (float) ; 
 float* f_iso_frequency_table_10b ; 
 float* f_vlc_frequency_table_10b ; 
 float powf (float,float) ; 
 float sinf (float) ; 

__attribute__((used)) static void EqzCoeffs( int i_rate, float f_octave_percent,
                       bool b_use_vlc_freqs,
                       eqz_config_t *p_eqz_config )
{
    const float *f_freq_table_10b = b_use_vlc_freqs
                                  ? f_vlc_frequency_table_10b
                                  : f_iso_frequency_table_10b;
    float f_rate = (float) i_rate;
    float f_nyquist_freq = 0.5f * f_rate;
    float f_octave_factor = powf( 2.0f, 0.5f * f_octave_percent );
    float f_octave_factor_1 = 0.5f * ( f_octave_factor + 1.0f );
    float f_octave_factor_2 = 0.5f * ( f_octave_factor - 1.0f );

    p_eqz_config->i_band = EQZ_BANDS_MAX;

    for( int i = 0; i < EQZ_BANDS_MAX; i++ )
    {
        float f_freq = f_freq_table_10b[i];

        p_eqz_config->band[i].f_frequency = f_freq;

        if( f_freq <= f_nyquist_freq )
        {
            float f_theta_1 = ( 2.0f * (float) M_PI * f_freq ) / f_rate;
            float f_theta_2 = f_theta_1 / f_octave_factor;
            float f_sin     = sinf( f_theta_2 );
            float f_sin_prd = sinf( f_theta_2 * f_octave_factor_1 )
                            * sinf( f_theta_2 * f_octave_factor_2 );
            float f_sin_hlf = f_sin * 0.5f;
            float f_den     = f_sin_hlf + f_sin_prd;

            p_eqz_config->band[i].f_alpha = f_sin_prd / f_den;
            p_eqz_config->band[i].f_beta  = ( f_sin_hlf - f_sin_prd ) / f_den;
            p_eqz_config->band[i].f_gamma = f_sin * cosf( f_theta_1 ) / f_den;
        }
        else
        {
            /* Any frequency beyond the Nyquist frequency is no good... */
            p_eqz_config->band[i].f_alpha =
            p_eqz_config->band[i].f_beta  =
            p_eqz_config->band[i].f_gamma = 0.0f;
        }
    }
}