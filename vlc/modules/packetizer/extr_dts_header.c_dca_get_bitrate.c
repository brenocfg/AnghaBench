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

__attribute__((used)) static unsigned int dca_get_bitrate( uint8_t i_rate )
{
    /* See ETSI TS 102 114, table 5-7 */
    const unsigned int p_dca_bitrates[32] = {
        32000,   56000,   64000,   96000,  112000,
        128000, 192000,  224000,  256000,  320000,
        384000, 448000,  512000,  576000,  640000,
        768000, 896000, 1024000, 1152000, 1280000,
        1344000, 1408000, 1411200, 1472000, 1536000,
        1920000, 2048000, 3072000, 3840000,
        /* FIXME: The following can't be put in a VLC audio_format_t:
         * 1: open, 2: variable, 3: lossless */
        0, 0, 0
    };

    if( i_rate >= 32 )
        return 0;
    return p_dca_bitrates[i_rate];
}