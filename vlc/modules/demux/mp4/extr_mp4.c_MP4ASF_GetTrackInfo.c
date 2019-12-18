#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  asfinfo; } ;
typedef  TYPE_1__ mp4_track_t ;
typedef  int /*<<< orphan*/  asf_track_info_t ;
typedef  int /*<<< orphan*/  asf_packet_sys_t ;

/* Variables and functions */
 TYPE_1__* MP4ASF_GetTrack (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static asf_track_info_t * MP4ASF_GetTrackInfo( asf_packet_sys_t *p_packetsys,
                                               uint8_t i_stream_number )
{
    mp4_track_t *p_track = MP4ASF_GetTrack( p_packetsys, i_stream_number );
    if ( p_track )
        return &p_track->asfinfo;
    else
        return NULL;
}