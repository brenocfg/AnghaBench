#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_9__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_13__ {scalar_t__ i_divider_num; } ;
struct TYPE_10__ {TYPE_7__ pts; TYPE_4__* p_context; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_12__ {int ticks_per_frame; } ;
struct TYPE_11__ {scalar_t__ repeat_pict; } ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ VLC_TICK_INVALID ; 
 scalar_t__ date_Get (TYPE_7__*) ; 
 scalar_t__ date_Increment (TYPE_7__*,scalar_t__) ; 

__attribute__((used)) static vlc_tick_t interpolate_next_pts( decoder_t *p_dec, AVFrame *frame )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    AVCodecContext *p_context = p_sys->p_context;

    if( p_sys->pts.i_divider_num == 0 ||
        date_Get( &p_sys->pts ) == VLC_TICK_INVALID )
        return VLC_TICK_INVALID;

    int i_tick = p_context->ticks_per_frame;
    if( i_tick <= 0 )
        i_tick = 1;

    /* interpolate the next PTS */
    return date_Increment( &p_sys->pts, i_tick + frame->repeat_pict );
}