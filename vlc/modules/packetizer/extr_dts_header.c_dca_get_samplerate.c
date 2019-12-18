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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static unsigned int dca_get_samplerate( uint8_t i_sfreq )
{
    /* See ETSI TS 102 114, table 5-5 */
    const unsigned int p_dca_samplerates[16] = {
        0, 8000, 16000, 32000, 0, 0, 11025, 22050, 44100, 0, 0,
        12000, 24000, 48000, 96000, 192000
    };

    if( i_sfreq >= 16 )
        return 0;
    return p_dca_samplerates[i_sfreq];
}