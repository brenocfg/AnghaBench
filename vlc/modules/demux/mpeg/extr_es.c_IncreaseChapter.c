#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_9__ {int /*<<< orphan*/  s; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_8__ {int i_current; int i_count; TYPE_5__* p_entry; } ;
struct TYPE_10__ {int /*<<< orphan*/  i_demux_flags; TYPE_2__ chapters; } ;
typedef  TYPE_4__ demux_sys_t ;
struct TYPE_11__ {scalar_t__ i_offset; TYPE_1__* p_seekpoint; } ;
typedef  TYPE_5__ chap_entry_t ;
struct TYPE_7__ {scalar_t__ i_time_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_UPDATE_SEEKPOINT ; 
 scalar_t__ UINT32_MAX ; 
 scalar_t__ VLC_TICK_0 ; 
 scalar_t__ VLC_TICK_INVALID ; 
 scalar_t__ vlc_stream_Tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void IncreaseChapter( demux_t *p_demux, vlc_tick_t i_time )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    while( p_sys->chapters.i_current + 1 < p_sys->chapters.i_count )
    {
        const chap_entry_t *p = &p_sys->chapters.p_entry[p_sys->chapters.i_current + 1];
        if( (p->i_offset != UINT32_MAX && vlc_stream_Tell( p_demux->s ) < p->i_offset) ||
            (i_time == VLC_TICK_INVALID || p->p_seekpoint->i_time_offset + VLC_TICK_0 > i_time) )
            break;
        ++p_sys->chapters.i_current;
        p_sys->i_demux_flags |= INPUT_UPDATE_SEEKPOINT;
    }
}