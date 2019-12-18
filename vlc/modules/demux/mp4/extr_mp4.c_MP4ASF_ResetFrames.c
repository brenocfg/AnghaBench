#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * p_frame; } ;
struct TYPE_6__ {TYPE_1__ asfinfo; } ;
typedef  TYPE_2__ mp4_track_t ;
struct TYPE_7__ {unsigned int i_tracks; TYPE_2__* track; } ;
typedef  TYPE_3__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void MP4ASF_ResetFrames( demux_sys_t *p_sys )
{
    for ( unsigned int i=0; i<p_sys->i_tracks; i++ )
    {
        mp4_track_t *p_track = &p_sys->track[i];
        if( p_track->asfinfo.p_frame )
        {
            block_ChainRelease( p_track->asfinfo.p_frame );
            p_track->asfinfo.p_frame = NULL;
        }
    }
}