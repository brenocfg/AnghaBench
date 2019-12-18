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
typedef  size_t uint32_t ;
struct TYPE_6__ {scalar_t__ i_default_sample_duration; scalar_t__ i_default_sample_size; } ;
struct TYPE_8__ {TYPE_1__ context; } ;
typedef  TYPE_3__ mp4_track_t ;
struct TYPE_7__ {scalar_t__ i_current_box_type; int /*<<< orphan*/ * p_fragment_atom; } ;
struct TYPE_9__ {size_t i_tracks; TYPE_3__* track; TYPE_2__ context; int /*<<< orphan*/ * p_moov; } ;
typedef  TYPE_4__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_BoxFree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void FragResetContext( demux_sys_t *p_sys )
{
    if( p_sys->context.p_fragment_atom )
    {
        if( p_sys->context.p_fragment_atom != p_sys->p_moov )
            MP4_BoxFree( p_sys->context.p_fragment_atom );
        p_sys->context.p_fragment_atom = NULL;
    }
    p_sys->context.i_current_box_type = 0;

    for ( uint32_t i=0; i<p_sys->i_tracks; i++ )
    {
        mp4_track_t *p_track = &p_sys->track[i];
        p_track->context.i_default_sample_size = 0;
        p_track->context.i_default_sample_duration = 0;
    }
}