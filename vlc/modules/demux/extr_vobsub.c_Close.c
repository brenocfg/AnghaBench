#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_5__ {int i_tracks; struct TYPE_5__* track; struct TYPE_5__* p_subtitles; scalar_t__ p_vobsub_stream; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_stream_Delete (scalar_t__) ; 

__attribute__((used)) static void Close( vlc_object_t *p_this )
{
    demux_t *p_demux = (demux_t*)p_this;
    demux_sys_t *p_sys = p_demux->p_sys;

    if( p_sys->p_vobsub_stream )
        vlc_stream_Delete( p_sys->p_vobsub_stream );

    /* Clean all subs from all tracks */
    for( int i = 0; i < p_sys->i_tracks; i++ )
        free( p_sys->track[i].p_subtitles );
    free( p_sys->track );
    free( p_sys );
}