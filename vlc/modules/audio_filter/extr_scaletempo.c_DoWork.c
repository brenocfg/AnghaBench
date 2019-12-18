#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  i_rate; } ;
struct TYPE_20__ {TYPE_3__ audio; } ;
struct TYPE_17__ {scalar_t__ i_rate; } ;
struct TYPE_18__ {TYPE_1__ audio; } ;
struct TYPE_21__ {TYPE_4__ fmt_out; TYPE_2__ fmt_in; TYPE_6__* p_sys; } ;
typedef  TYPE_5__ filter_t ;
struct TYPE_22__ {scalar_t__ sample_rate; double scale; int bytes_stride_scaled; int bytes_stride; int frames_stride_scaled; int bytes_per_frame; scalar_t__ bytes_queued; scalar_t__ bytes_queue_max; scalar_t__ bytes_to_slide; } ;
typedef  TYPE_6__ filter_sys_t ;
struct TYPE_23__ {size_t i_buffer; size_t i_nb_samples; int /*<<< orphan*/  i_length; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; int /*<<< orphan*/ * p_buffer; } ;
typedef  TYPE_7__ block_t ;

/* Variables and functions */
 TYPE_7__* block_Alloc (size_t) ; 
 int /*<<< orphan*/  block_Release (TYPE_7__*) ; 
 size_t calculate_output_buffer_size (TYPE_5__*,size_t) ; 
 size_t fill_queue (TYPE_5__*,int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_5__*,char*,int,int,int,scalar_t__) ; 
 scalar_t__ transform_buffer (TYPE_5__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  vlc_tick_from_samples (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static block_t *DoWork( filter_t * p_filter, block_t * p_in_buf )
{
    filter_sys_t *p = p_filter->p_sys;

    if( p_filter->fmt_in.audio.i_rate == p->sample_rate )
        return p_in_buf;

    double scale = p_filter->fmt_in.audio.i_rate / (double)p->sample_rate;
    if( scale != p->scale ) {
        p->scale = scale;
        p->bytes_stride_scaled  = p->bytes_stride * p->scale;
        p->frames_stride_scaled = p->bytes_stride_scaled / p->bytes_per_frame;
        p->bytes_to_slide = 0;
        msg_Dbg( p_filter, "%.3f scale, %.3f stride_in, %i stride_out rate: %u",
                 p->scale, p->frames_stride_scaled,
                 (int)( p->bytes_stride / p->bytes_per_frame ), p->sample_rate );
    }

    block_t *p_out_buf = NULL;
    size_t i_outsize = calculate_output_buffer_size ( p_filter, p_in_buf->i_buffer );

    size_t offset_in = fill_queue( p_filter, p_in_buf->p_buffer,
                                   p_in_buf->i_buffer, 0 );
    if( i_outsize > 0 )
    {
        p_out_buf = block_Alloc( i_outsize );
        if( p_out_buf == NULL )
        {
            block_Release( p_in_buf );
            return NULL;
        }
        size_t bytes_out = 0;
        while( p->bytes_queued >= p->bytes_queue_max )
        {
            bytes_out += transform_buffer( p_filter,
                                           &p_out_buf->p_buffer[bytes_out],
                                           p_out_buf->i_buffer - bytes_out );
            offset_in += fill_queue( p_filter, p_in_buf->p_buffer,
                                     p_in_buf->i_buffer, offset_in );
        }
        p_out_buf->i_buffer     = bytes_out;
        p_out_buf->i_nb_samples = bytes_out / p->bytes_per_frame;
        p_out_buf->i_dts        = p_in_buf->i_dts;
        p_out_buf->i_pts        = p_in_buf->i_pts;
        p_out_buf->i_length = vlc_tick_from_samples(p_out_buf->i_nb_samples,
                                                    p_filter->fmt_out.audio.i_rate);
    }

    block_Release( p_in_buf );
    return p_out_buf;
}