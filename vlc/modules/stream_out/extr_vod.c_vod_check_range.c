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
struct TYPE_3__ {scalar_t__ i_length; } ;
typedef  TYPE_1__ vod_media_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 

int vod_check_range(vod_media_t *p_media, const char *psz_session,
                    int64_t start, int64_t end)
{
    (void) psz_session;

    if (p_media->i_length > 0 && (start > p_media->i_length
                                  || end > p_media->i_length))
        return VLC_EGENERIC;

    return VLC_SUCCESS;
}