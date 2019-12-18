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
struct TYPE_4__ {int i_rate; int i_bitspersample; int i_channels; int i_blockalign; } ;
struct TYPE_5__ {TYPE_1__ audio; } ;
typedef  TYPE_2__ es_format_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int WAV_CHAN_MAX ; 
 int __MAX (int,int) ; 

__attribute__((used)) static int FrameInfo_PCM( unsigned int *pi_size, int *pi_samples,
                          const es_format_t *p_fmt )
{
    int i_bytes;

    if( p_fmt->audio.i_rate > 352800
     || p_fmt->audio.i_bitspersample > 64
     || p_fmt->audio.i_channels > WAV_CHAN_MAX )
        return VLC_EGENERIC;

    /* read samples for 50ms of */
    *pi_samples = __MAX( p_fmt->audio.i_rate / 20, 1 );

    i_bytes = *pi_samples * p_fmt->audio.i_channels *
        ( (p_fmt->audio.i_bitspersample + 7) / 8 );

    if( p_fmt->audio.i_blockalign > 0 )
    {
        const int i_modulo = i_bytes % p_fmt->audio.i_blockalign;
        if( i_modulo > 0 )
            i_bytes += p_fmt->audio.i_blockalign - i_modulo;
    }

    *pi_size = i_bytes;
    return VLC_SUCCESS;
}