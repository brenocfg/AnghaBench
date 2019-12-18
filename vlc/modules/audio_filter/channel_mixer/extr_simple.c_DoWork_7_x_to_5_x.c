#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int i_physical_channels; } ;
struct TYPE_13__ {TYPE_3__ audio; } ;
struct TYPE_10__ {int i_physical_channels; } ;
struct TYPE_11__ {TYPE_1__ audio; } ;
struct TYPE_14__ {TYPE_4__ fmt_in; TYPE_2__ fmt_out; } ;
typedef  TYPE_5__ filter_t ;
struct TYPE_15__ {int i_nb_samples; scalar_t__ p_buffer; } ;
typedef  TYPE_6__ block_t ;

/* Variables and functions */
 int AOUT_CHAN_LFE ; 

__attribute__((used)) static void DoWork_7_x_to_5_x( filter_t * p_filter,  block_t * p_in_buf, block_t * p_out_buf ) {
    float *p_dest = (float *)p_out_buf->p_buffer;
    const float *p_src = (const float *)p_in_buf->p_buffer;
    for( int i = p_in_buf->i_nb_samples; i--; )
    {
        *p_dest++ = p_src[0];
        *p_dest++ = p_src[1];
        *p_dest++ = (p_src[2] + p_src[4]) * 0.5f;
        *p_dest++ = (p_src[3] + p_src[5]) * 0.5f;
        *p_dest++ = p_src[6];

        p_src += 7;

        if( p_filter->fmt_in.audio.i_physical_channels & AOUT_CHAN_LFE &&
            p_filter->fmt_out.audio.i_physical_channels & AOUT_CHAN_LFE )
            *p_dest++ = *p_src++;
        else if( p_filter->fmt_in.audio.i_physical_channels & AOUT_CHAN_LFE ) p_src++;
    }
}