#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_8__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_9__ {int i_seekpoint; int /*<<< orphan*/  i_update; TYPE_1__* p_title; } ;
typedef  TYPE_4__ demux_sys_t ;
struct TYPE_7__ {scalar_t__ i_time_offset; } ;
struct TYPE_6__ {int i_seekpoint; TYPE_2__** seekpoint; } ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_UPDATE_SEEKPOINT ; 

__attribute__((used)) static void UpdateSeekPoint( demux_t *p_demux, vlc_tick_t i_time )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    int i;

    if( !p_sys->p_title )
        return;

    for( i = 0; i < p_sys->p_title->i_seekpoint; i++ )
    {
        if( i_time < p_sys->p_title->seekpoint[i]->i_time_offset )
            break;
    }
    i--;

    if( i != p_sys->i_seekpoint && i >= 0 )
    {
        p_sys->i_seekpoint = i;
        p_sys->i_update |= INPUT_UPDATE_SEEKPOINT;
    }
}