#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_3__* p_overlay; } ;
typedef  TYPE_1__ bluray_spu_updater_sys_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void updater_unlock_overlay(bluray_spu_updater_sys_t *p_upd_sys)
{
    assert (p_upd_sys->p_overlay);

    vlc_mutex_unlock(&p_upd_sys->p_overlay->lock);
    vlc_mutex_unlock(&p_upd_sys->lock);
}