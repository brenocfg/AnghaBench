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
struct TYPE_7__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_8__ {unsigned int i_track; TYPE_4__** track; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_6__ {scalar_t__ i_size; } ;
struct TYPE_9__ {scalar_t__ i_idxposc; int b_eof; TYPE_1__ idx; } ;
typedef  TYPE_4__ avi_track_t ;

/* Variables and functions */

__attribute__((used)) static int AVI_TrackStopFinishedStreams( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    unsigned int i;
    int b_end = true;

    for( i = 0; i < p_sys->i_track; i++ )
    {
        avi_track_t *tk = p_sys->track[i];
        if( tk->i_idxposc >= tk->idx.i_size )
        {
            tk->b_eof = true;
        }
        else
        {
            b_end = false;
        }
    }
    return( b_end );
}