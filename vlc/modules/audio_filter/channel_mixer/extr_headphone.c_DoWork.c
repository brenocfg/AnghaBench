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
typedef  float uint8_t ;
struct TYPE_11__ {int /*<<< orphan*/  audio; } ;
struct TYPE_10__ {int /*<<< orphan*/  audio; } ;
struct TYPE_13__ {TYPE_2__ fmt_out; TYPE_1__ fmt_in; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_14__ {size_t i_overflow_buffer_size; unsigned int i_nb_atomic_operations; TYPE_3__* p_atomic_operations; scalar_t__ p_overflow_buffer; } ;
typedef  TYPE_5__ filter_sys_t ;
struct TYPE_15__ {size_t i_buffer; unsigned int i_nb_samples; scalar_t__ p_buffer; } ;
typedef  TYPE_6__ block_t ;
struct TYPE_12__ {int i_source_channel_offset; int i_dest_channel_offset; unsigned int i_delay; double d_amplitude_factor; } ;

/* Variables and functions */
 size_t __MIN (size_t,size_t) ; 
 int aout_FormatNbChannels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (float*,float*,size_t) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void DoWork( filter_t * p_filter,
                    block_t * p_in_buf, block_t * p_out_buf )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    int i_input_nb = aout_FormatNbChannels( &p_filter->fmt_in.audio );
    int i_output_nb = aout_FormatNbChannels( &p_filter->fmt_out.audio );

    float * p_in = (float*) p_in_buf->p_buffer;
    float * p_out;
    uint8_t * p_overflow;
    uint8_t * p_end_overflow;
    uint8_t * p_slide;

    size_t i_overflow_size;     /* in bytes */
    size_t i_out_size;          /* in bytes */

    unsigned int i, j;

    int i_source_channel_offset;
    int i_dest_channel_offset;
    unsigned int i_delay;
    double d_amplitude_factor;

    p_out = (float *)p_out_buf->p_buffer;
    i_out_size = p_out_buf->i_buffer;

    /* Slide the overflow buffer */
    p_overflow = (uint8_t *) p_sys->p_overflow_buffer;
    i_overflow_size = p_sys->i_overflow_buffer_size;
    p_end_overflow = p_overflow + i_overflow_size;

    memset( p_out, 0, i_out_size );
    memcpy( p_out, p_overflow, __MIN( i_out_size, i_overflow_size ) );

    p_slide = (uint8_t *) p_sys->p_overflow_buffer;
    while( p_slide < p_end_overflow )
    {
        size_t i_bytes_copied;

        if( p_slide + i_out_size < p_end_overflow )
        {
            memset( p_slide, 0, i_out_size );
            if( p_slide + 2 * i_out_size < p_end_overflow )
                i_bytes_copied = i_out_size;
            else
                i_bytes_copied = p_end_overflow - ( p_slide + i_out_size );
            memcpy( p_slide, p_slide + i_out_size, i_bytes_copied );
        }
        else
        {
            i_bytes_copied = p_end_overflow - p_slide;
            memset( p_slide, 0, i_bytes_copied );
        }
        p_slide += i_bytes_copied;
    }

    /* apply the atomic operations */
    for( i = 0; i < p_sys->i_nb_atomic_operations; i++ )
    {
        /* shorter variable names */
        i_source_channel_offset
            = p_sys->p_atomic_operations[i].i_source_channel_offset;
        i_dest_channel_offset
            = p_sys->p_atomic_operations[i].i_dest_channel_offset;
        i_delay = p_sys->p_atomic_operations[i].i_delay;
        d_amplitude_factor
            = p_sys->p_atomic_operations[i].d_amplitude_factor;

        if( p_out_buf->i_nb_samples > i_delay )
        {
            /* current buffer coefficients */
            for( j = 0; j < p_out_buf->i_nb_samples - i_delay; j++ )
            {
                ((float*)p_out)[ (i_delay+j)*i_output_nb + i_dest_channel_offset ]
                    += p_in[ j * i_input_nb + i_source_channel_offset ]
                       * d_amplitude_factor;
            }

            /* overflow buffer coefficients */
            for( j = 0; j < i_delay; j++ )
            {
                ((float*)p_overflow)[ j*i_output_nb + i_dest_channel_offset ]
                    += p_in[ (p_out_buf->i_nb_samples - i_delay + j)
                       * i_input_nb + i_source_channel_offset ]
                       * d_amplitude_factor;
            }
        }
        else
        {
            /* overflow buffer coefficients only */
            for( j = 0; j < p_out_buf->i_nb_samples; j++ )
            {
                ((float*)p_overflow)[ (i_delay - p_out_buf->i_nb_samples + j)
                                        * i_output_nb + i_dest_channel_offset ]
                    += p_in[ j * i_input_nb + i_source_channel_offset ]
                       * d_amplitude_factor;
            }
        }
    }
}