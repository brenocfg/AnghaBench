#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_12__ {scalar_t__ i_frame_rate_base; scalar_t__ i_frame_rate; } ;
struct TYPE_13__ {TYPE_3__ video; } ;
struct TYPE_10__ {scalar_t__ i_height; scalar_t__ i_width; scalar_t__ i_visible_width; scalar_t__ i_visible_height; } ;
struct TYPE_11__ {TYPE_1__ video; } ;
struct TYPE_14__ {TYPE_4__ fmt_in; TYPE_2__ fmt_out; TYPE_6__* p_sys; } ;
typedef  TYPE_5__ decoder_t ;
struct TYPE_15__ {int i_next_block_flags; int /*<<< orphan*/  date; } ;
typedef  TYPE_6__ decoder_sys_t ;
struct TYPE_16__ {int* p_buffer; int i_buffer; scalar_t__ i_dts; scalar_t__ i_pts; int i_flags; scalar_t__ i_length; } ;
typedef  TYPE_7__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_TYPE_I ; 
 int GetWBE (int const*) ; 
 scalar_t__ VLC_TICK_INVALID ; 
 void* date_Get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  date_Increment (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static block_t *PacketizeParse( void *p_private, bool *pb_ts_used, block_t *p_block )
{
    decoder_t *p_dec = p_private;
    decoder_sys_t *p_sys = p_dec->p_sys;

    const uint8_t *p_buf = &p_block->p_buffer[2];
    size_t i_buf = p_block->i_buffer - 2;

    while( i_buf > 4 && p_buf[0] == 0xFF )
    {
        size_t i_size = 2 + GetWBE( &p_buf[2] );
        if( i_size > i_buf )
            break;
        if( p_buf[1] == 0xC0 && i_buf > 9 )
        {
            uint16_t i_height = GetWBE( &p_buf[5] );
            uint16_t i_width = GetWBE( &p_buf[7] );
            if( i_height && i_width &&
                (p_dec->fmt_out.video.i_height != i_height ||
                 p_dec->fmt_out.video.i_width != i_width) )
            {
                p_dec->fmt_out.video.i_width =
                p_dec->fmt_out.video.i_visible_width = i_width;
                p_dec->fmt_out.video.i_height =
                p_dec->fmt_out.video.i_visible_height = i_height;
            }
            break;
        }
        i_buf -= i_size;
        p_buf += i_size;
    }

    if( p_block->i_dts == VLC_TICK_INVALID )
        p_block->i_dts = p_block->i_pts;
    else if( p_block->i_pts == VLC_TICK_INVALID )
        p_block->i_pts = p_block->i_dts;

    vlc_tick_t i_prev_dts = date_Get( &p_sys->date );
    if( p_block->i_dts != VLC_TICK_INVALID )
    {
        date_Set( &p_sys->date, p_block->i_dts );
    }
    else if( p_dec->fmt_in.video.i_frame_rate &&
             p_dec->fmt_in.video.i_frame_rate_base )
    {
        date_Increment( &p_sys->date, 1 );
        p_block->i_dts = p_block->i_pts = date_Get( &p_sys->date );
    }

    if( i_prev_dts != VLC_TICK_INVALID && p_block->i_dts != VLC_TICK_INVALID )
        p_block->i_length = p_block->i_dts - i_prev_dts;

    *pb_ts_used = true;

    p_block->i_flags = p_sys->i_next_block_flags | BLOCK_FLAG_TYPE_I;
    p_sys->i_next_block_flags = 0;

    return p_block;
}