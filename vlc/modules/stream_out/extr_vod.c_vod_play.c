#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  p_vod; } ;
typedef  TYPE_1__ vod_media_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  VOD_MEDIA_PLAY ; 
 int /*<<< orphan*/  vod_MediaControl (int /*<<< orphan*/ ,TYPE_1__*,char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ vod_check_range (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vod_play(vod_media_t *p_media, const char *psz_session,
              int64_t *start, int64_t end)
{
    if (vod_check_range(p_media, psz_session, *start, end) != VLC_SUCCESS)
        return;

    /* We're passing the #vod{} sout chain here */
    vod_MediaControl(p_media->p_vod, p_media, psz_session,
                     VOD_MEDIA_PLAY, "vod", start);
}