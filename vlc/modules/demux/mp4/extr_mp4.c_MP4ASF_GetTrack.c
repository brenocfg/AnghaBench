#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_9__ {TYPE_5__* (* BOXDATA ) (int /*<<< orphan*/ ) ;scalar_t__ p_asf; } ;
typedef  TYPE_2__ mp4_track_t ;
struct TYPE_10__ {unsigned int i_tracks; TYPE_2__* track; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_11__ {TYPE_1__* p_demux; } ;
typedef  TYPE_4__ asf_packet_sys_t ;
struct TYPE_12__ {scalar_t__ i_stream_number; } ;
struct TYPE_8__ {TYPE_3__* p_sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  p_asf ; 
 TYPE_5__* stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) inline static mp4_track_t *MP4ASF_GetTrack( asf_packet_sys_t *p_packetsys,
                                            uint8_t i_stream_number )
{
    demux_sys_t *p_sys = p_packetsys->p_demux->p_sys;
    for ( unsigned int i=0; i<p_sys->i_tracks; i++ )
    {
        if ( p_sys->track[i].p_asf &&
             i_stream_number == p_sys->track[i].BOXDATA(p_asf)->i_stream_number )
        {
            return &p_sys->track[i];
        }
    }
    return NULL;
}