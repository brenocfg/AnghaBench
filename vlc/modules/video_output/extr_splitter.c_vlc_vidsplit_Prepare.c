#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_7__ {int i_output; } ;
struct TYPE_6__ {int /*<<< orphan*/ ** pictures; struct vlc_vidsplit_part* parts; TYPE_4__ splitter; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  subpicture_t ;
struct vlc_vidsplit_part {int /*<<< orphan*/  display; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  picture_t ;

/* Variables and functions */
 int /*<<< orphan*/  picture_Hold (int /*<<< orphan*/ *) ; 
 scalar_t__ video_splitter_Filter (TYPE_4__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vout_display_Prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlc_vidsplit_Prepare(vout_display_t *vd, picture_t *pic,
                                 subpicture_t *subpic, vlc_tick_t date)
{
    vout_display_sys_t *sys = vd->sys;

    picture_Hold(pic);
    (void) subpic;

    vlc_mutex_lock(&sys->lock);
    if (video_splitter_Filter(&sys->splitter, sys->pictures, pic)) {
        vlc_mutex_unlock(&sys->lock);

        for (int i = 0; i < sys->splitter.i_output; i++)
            sys->pictures[i] = NULL;
        return;
    }
    vlc_mutex_unlock(&sys->lock);

    for (int i = 0; i < sys->splitter.i_output; i++) {
        struct vlc_vidsplit_part *part = &sys->parts[i];

        vlc_sem_wait(&part->lock);
        sys->pictures[i] = vout_display_Prepare(part->display,
                                                sys->pictures[i], NULL, date);
    }
}