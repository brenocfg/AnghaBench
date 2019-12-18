#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ i_rate; scalar_t__ i_bytes_per_frame; int /*<<< orphan*/  i_physical_channels; int /*<<< orphan*/  i_chan_mode; int /*<<< orphan*/  i_frame_length; int /*<<< orphan*/  i_channels; } ;
struct TYPE_22__ {int /*<<< orphan*/  i_bitrate; TYPE_3__ audio; } ;
struct TYPE_24__ {TYPE_4__ fmt_out; TYPE_7__* p_sys; } ;
typedef  TYPE_6__ decoder_t ;
struct TYPE_18__ {scalar_t__ i_divider_num; } ;
struct TYPE_23__ {scalar_t__ i_rate; scalar_t__ i_size; int /*<<< orphan*/  i_samples; int /*<<< orphan*/  i_bitrate; int /*<<< orphan*/  i_channels_conf; int /*<<< orphan*/  i_chan_mode; int /*<<< orphan*/  i_channels; } ;
struct TYPE_20__ {TYPE_1__* p_block; } ;
struct TYPE_25__ {scalar_t__ i_prev_bytestream_pts; TYPE_10__ end_date; TYPE_5__ frame; TYPE_2__ bytestream; int /*<<< orphan*/  i_input_size; } ;
typedef  TYPE_7__ decoder_sys_t ;
struct TYPE_26__ {scalar_t__ i_pts; scalar_t__ i_dts; scalar_t__ i_length; int /*<<< orphan*/  i_nb_samples; } ;
typedef  TYPE_8__ block_t ;
struct TYPE_19__ {scalar_t__ i_pts; } ;

/* Variables and functions */
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_8__* block_Alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  date_Change (TYPE_10__*,scalar_t__,int) ; 
 scalar_t__ date_Get (TYPE_10__*) ; 
 scalar_t__ date_Increment (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  date_Init (TYPE_10__*,scalar_t__,int) ; 
 int /*<<< orphan*/  date_Set (TYPE_10__*,scalar_t__) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_6__*,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static block_t *GetOutBuffer( decoder_t *p_dec )
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    assert( p_sys->frame.i_rate > 0 );

    block_t *p_block = block_Alloc( p_sys->i_input_size );
    if( p_block == NULL )
        return NULL;

    if( p_dec->fmt_out.audio.i_rate != p_sys->frame.i_rate )
    {
        msg_Dbg( p_dec, "A/52 channels:%d samplerate:%d bitrate:%d",
                 p_sys->frame.i_channels, p_sys->frame.i_rate, p_sys->frame.i_bitrate );
        if( p_sys->end_date.i_divider_num )
            date_Change( &p_sys->end_date, p_sys->frame.i_rate, 1 );
        else
            date_Init( &p_sys->end_date, p_sys->frame.i_rate, 1 );
    }

    if( p_sys->bytestream.p_block->i_pts != date_Get( &p_sys->end_date ) &&
        p_sys->bytestream.p_block->i_pts != VLC_TICK_INVALID )
    {
        /* Make sure we don't reuse the same pts twice
         * as A/52 in PES sends multiple times the same pts */
        if( p_sys->bytestream.p_block->i_pts != p_sys->i_prev_bytestream_pts )
            date_Set( &p_sys->end_date, p_sys->bytestream.p_block->i_pts );
        p_sys->i_prev_bytestream_pts = p_sys->bytestream.p_block->i_pts;
        p_sys->bytestream.p_block->i_pts = VLC_TICK_INVALID;
    }

    p_dec->fmt_out.audio.i_rate     = p_sys->frame.i_rate;
    p_dec->fmt_out.audio.i_channels = p_sys->frame.i_channels;
    if( p_dec->fmt_out.audio.i_bytes_per_frame < p_sys->frame.i_size )
        p_dec->fmt_out.audio.i_bytes_per_frame = p_sys->frame.i_size;
    p_dec->fmt_out.audio.i_frame_length = p_sys->frame.i_samples;

    p_dec->fmt_out.audio.i_chan_mode = p_sys->frame.i_chan_mode;
    p_dec->fmt_out.audio.i_physical_channels = p_sys->frame.i_channels_conf;

    p_dec->fmt_out.i_bitrate = p_sys->frame.i_bitrate;

    p_block->i_nb_samples = p_sys->frame.i_samples;
    p_block->i_pts = p_block->i_dts = date_Get( &p_sys->end_date );
    if( p_block->i_pts != VLC_TICK_INVALID )
        p_block->i_length = date_Increment( &p_sys->end_date,
                                            p_block->i_nb_samples ) - p_block->i_pts;

    return p_block;
}