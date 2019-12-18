#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_19__ {TYPE_6__* p_fmt; int /*<<< orphan*/  p_fifo; scalar_t__ p_sys; } ;
typedef  TYPE_7__ sout_input_t ;
struct TYPE_16__ {TYPE_3__* p_first; } ;
struct TYPE_17__ {TYPE_4__ chain_pes; } ;
struct TYPE_20__ {TYPE_5__ state; } ;
typedef  TYPE_8__ sout_input_sys_t ;
struct TYPE_21__ {scalar_t__ i_dts; int i_flags; scalar_t__ i_length; int i_buffer; } ;
typedef  TYPE_9__ block_t ;
struct TYPE_14__ {int i_bytes_per_frame; int i_frame_length; } ;
struct TYPE_13__ {scalar_t__ i_frame_rate_base; scalar_t__ i_frame_rate; } ;
struct TYPE_18__ {scalar_t__ i_cat; scalar_t__ i_codec; TYPE_2__ audio; TYPE_1__ video; } ;
struct TYPE_15__ {int i_length; } ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 int BLOCK_FLAG_DISCONTINUITY ; 
 scalar_t__ SPU_ES ; 
 scalar_t__ VIDEO_ES ; 
 scalar_t__ VLC_CODEC_SUBT ; 
 void* VLC_TICK_FROM_MS (int) ; 
 scalar_t__ block_FifoCount (int /*<<< orphan*/ ) ; 
 TYPE_9__* block_FifoShow (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_tick_from_samples (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void SetBlockDuration( sout_input_t *p_input, block_t *p_data )
{
    sout_input_sys_t *p_stream = (sout_input_sys_t*) p_input->p_sys;

    if( p_input->p_fmt->i_cat != SPU_ES &&
        block_FifoCount( p_input->p_fifo ) > 0 )
    {
        block_t *p_next = block_FifoShow( p_input->p_fifo );
        vlc_tick_t i_diff = p_next->i_dts - p_data->i_dts;
        if( i_diff > 0 &&
                (p_next->i_flags & BLOCK_FLAG_DISCONTINUITY) == 0 )
        {
            p_data->i_length = i_diff;
        }
        else if ( p_data->i_length == 0 )
        {
            /* Try rates */
            if( p_input->p_fmt->i_cat == VIDEO_ES &&
                p_input->p_fmt->video.i_frame_rate &&
                p_input->p_fmt->video.i_frame_rate_base )
            {
                p_data->i_length = vlc_tick_from_samples(
                                   p_input->p_fmt->video.i_frame_rate,
                                   p_input->p_fmt->video.i_frame_rate_base);
            }
            else if( p_input->p_fmt->i_cat == AUDIO_ES &&
                     p_input->p_fmt->audio.i_bytes_per_frame &&
                     p_input->p_fmt->audio.i_frame_length )
            {
                p_data->i_length = p_data->i_buffer *
                                   p_input->p_fmt->audio.i_frame_length /
                                   p_input->p_fmt->audio.i_bytes_per_frame;
            }
            /* Try a previous duration */
            else if( p_stream->state.chain_pes.p_first )
                p_data->i_length = p_stream->state.chain_pes.p_first->i_length;
            /* Or next */
            else if( p_next->i_length > 0 )
                p_data->i_length = p_next->i_length;
            /* or worse */
            else
                p_data->i_length = VLC_TICK_FROM_MS(1);
        }
    }
    else if( p_input->p_fmt->i_codec != VLC_CODEC_SUBT )
    {
        p_data->i_length = VLC_TICK_FROM_MS(1);
    }
}