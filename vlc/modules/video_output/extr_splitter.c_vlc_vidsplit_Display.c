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
struct TYPE_6__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_display_t ;
struct TYPE_5__ {int i_output; } ;
struct TYPE_7__ {int /*<<< orphan*/ ** pictures; struct vlc_vidsplit_part* parts; TYPE_1__ splitter; } ;
typedef  TYPE_3__ vout_display_sys_t ;
struct vlc_vidsplit_part {int /*<<< orphan*/  lock; int /*<<< orphan*/  display; } ;
typedef  int /*<<< orphan*/  picture_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_display_Display (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlc_vidsplit_Display(vout_display_t *vd, picture_t *picture)
{
    vout_display_sys_t *sys = vd->sys;

    for (int i = 0; i < sys->splitter.i_output; i++) {
        struct vlc_vidsplit_part *part = &sys->parts[i];

        if (sys->pictures[i] != NULL)
            vout_display_Display(part->display, sys->pictures[i]);
        vlc_sem_post(&part->lock);
    }

    (void) picture;
}