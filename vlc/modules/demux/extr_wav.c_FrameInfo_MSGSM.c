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
struct TYPE_4__ {int i_blockalign; int i_rate; } ;
struct TYPE_5__ {int i_bitrate; TYPE_1__ audio; } ;
typedef  TYPE_2__ es_format_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int FrameInfo_MSGSM( unsigned int *pi_size, int *pi_samples,
                            const es_format_t *p_fmt )
{
    if( p_fmt->i_bitrate <= 0 )
        return VLC_EGENERIC;

    *pi_samples = ( p_fmt->audio.i_blockalign * p_fmt->audio.i_rate * 8)
                    / p_fmt->i_bitrate;
    *pi_size = p_fmt->audio.i_blockalign;

    return VLC_SUCCESS;
}