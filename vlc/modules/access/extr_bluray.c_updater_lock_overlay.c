#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; TYPE_2__* p_overlay; } ;
typedef  TYPE_1__ bluray_spu_updater_sys_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ bluray_overlay_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bluray_overlay_t *updater_lock_overlay(bluray_spu_updater_sys_t *p_upd_sys)
{
    /* this lock is held while vout accesses overlay. => overlay can't be closed. */
    vlc_mutex_lock(&p_upd_sys->lock);

    bluray_overlay_t *ov = p_upd_sys->p_overlay;
    if (ov) {
        /* this lock is held while vout accesses overlay. => overlay can't be modified. */
        vlc_mutex_lock(&ov->lock);
        return ov;
    }

    /* overlay has been closed */
    vlc_mutex_unlock(&p_upd_sys->lock);
    return NULL;
}