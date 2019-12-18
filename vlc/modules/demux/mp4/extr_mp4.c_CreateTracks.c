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
typedef  int /*<<< orphan*/  mp4_track_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_5__ {unsigned int i_tracks; int /*<<< orphan*/  p_root; int /*<<< orphan*/ * track; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_BoxGet (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  MP4_TrackInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int SIZE_MAX ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/ * vlc_alloc (unsigned int,int) ; 

__attribute__((used)) static int CreateTracks( demux_t *p_demux, unsigned i_tracks )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    if( SIZE_MAX / i_tracks < sizeof(mp4_track_t) )
        return VLC_EGENERIC;

    p_sys->track = vlc_alloc( i_tracks, sizeof(mp4_track_t)  );
    if( p_sys->track == NULL )
        return VLC_ENOMEM;
    p_sys->i_tracks = i_tracks;

    for( unsigned i=0; i<i_tracks; i++ )
    {
        MP4_TrackInit( &p_sys->track[i],
                       MP4_BoxGet( p_sys->p_root, "/moov/trak[%d]", i ) );
    }

    return VLC_SUCCESS;
}