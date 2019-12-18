#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ request_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; TYPE_2__* picture; } ;
typedef  TYPE_1__ vout_snapshot_t ;
typedef  int /*<<< orphan*/  video_format_t ;
struct TYPE_8__ {struct TYPE_8__* p_next; int /*<<< orphan*/  format; } ;
typedef  TYPE_2__ picture_t ;

/* Variables and functions */
 TYPE_2__* picture_Clone (TYPE_2__*) ; 
 int /*<<< orphan*/  video_format_CopyCrop (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  vlc_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void vout_snapshot_Set(vout_snapshot_t *snap,
                       const video_format_t *fmt,
                       picture_t *picture)
{
    if (snap == NULL)
        return;

    if (!fmt)
        fmt = &picture->format;

    vlc_mutex_lock(&snap->lock);
    while (snap->request_count > 0) {
        picture_t *dup = picture_Clone(picture);
        if (!dup)
            break;

        video_format_CopyCrop( &dup->format, fmt );

        dup->p_next = snap->picture;
        snap->picture = dup;
        snap->request_count--;
    }
    vlc_cond_broadcast(&snap->wait);
    vlc_mutex_unlock(&snap->lock);
}