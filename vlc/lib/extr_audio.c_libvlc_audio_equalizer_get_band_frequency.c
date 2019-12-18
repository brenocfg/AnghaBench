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

/* Variables and functions */
 unsigned int EQZ_BANDS_MAX ; 
 float* f_iso_frequency_table_10b ; 

float libvlc_audio_equalizer_get_band_frequency( unsigned u_index )
{
    if ( u_index >= EQZ_BANDS_MAX )
        return -1.f;

    return f_iso_frequency_table_10b[ u_index ];
}