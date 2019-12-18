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
struct TYPE_10__ {int /*<<< orphan*/  audio; } ;
struct TYPE_9__ {int /*<<< orphan*/  audio; } ;
struct TYPE_11__ {TYPE_4__* p_sys; TYPE_2__ fmt_out; TYPE_1__ fmt_in; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_12__ {int* channel_map; } ;
typedef  TYPE_4__ filter_sys_t ;
struct TYPE_13__ {size_t i_nb_samples; unsigned int i_buffer; scalar_t__ p_buffer; } ;
typedef  TYPE_5__ block_t ;

/* Variables and functions */
 unsigned int aout_FormatNbChannels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (float*,float*,unsigned int) ; 

__attribute__((used)) static block_t *Downmix( filter_t *p_filter, block_t *p_buf )
{
    unsigned i_input_nb = aout_FormatNbChannels( &p_filter->fmt_in.audio );
    unsigned i_output_nb = aout_FormatNbChannels( &p_filter->fmt_out.audio );

    assert( i_input_nb >= i_output_nb );

    filter_sys_t *p_sys = p_filter->p_sys;

    float *p_dest = (float *)p_buf->p_buffer;
    const float *p_src = p_dest;
    const int *channel_map = p_sys->channel_map;
    /* Use an extra buffer to avoid overlapping */
    float buffer[i_output_nb];

    for( size_t i = 0; i < p_buf->i_nb_samples; i++ )
    {
        for( unsigned j = 0; j < i_output_nb; j++ )
            buffer[j] = channel_map[j] == -1 ? 0.f : p_src[channel_map[j]];
        memcpy( p_dest, buffer, i_output_nb * sizeof(float) );

        p_src += i_input_nb;
        p_dest += i_output_nb;
    }
    p_buf->i_buffer = p_buf->i_buffer * i_output_nb / i_input_nb;

    return p_buf;
}