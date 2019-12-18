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
struct TYPE_4__ {struct vlc_vidsplit_part* sys; } ;
struct TYPE_5__ {TYPE_1__ owner; } ;
typedef  TYPE_2__ vout_window_t ;
typedef  int /*<<< orphan*/  vout_display_t ;
struct vlc_vidsplit_part {int /*<<< orphan*/  lock; int /*<<< orphan*/ * display; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_display_Delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlc_vidsplit_window_Closed(vout_window_t *wnd)
{
    struct vlc_vidsplit_part *part = wnd->owner.sys;
    vout_display_t *display;

    vlc_sem_wait(&part->lock);
    display = part->display;
    part->display = NULL;
    vlc_sem_post(&part->lock);

    if (display != NULL)
        vout_display_Delete(display);
}