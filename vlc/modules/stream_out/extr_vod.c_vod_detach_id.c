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
struct TYPE_3__ {int /*<<< orphan*/  rtsp; } ;
typedef  TYPE_1__ vod_media_t ;
typedef  int /*<<< orphan*/  sout_stream_id_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  RtspTrackDetach (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

void vod_detach_id(vod_media_t *p_media, const char *psz_session,
                   sout_stream_id_sys_t *sout_id)
{
    RtspTrackDetach(p_media->rtsp, psz_session, sout_id);
}