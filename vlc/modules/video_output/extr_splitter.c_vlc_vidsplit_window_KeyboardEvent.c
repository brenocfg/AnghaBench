#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vout_window_t ;
struct TYPE_5__ {TYPE_1__* cfg; TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_display_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_3__ vout_display_sys_t ;
struct TYPE_4__ {int /*<<< orphan*/  window; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_object_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_window_ReportKeyPress (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void vlc_vidsplit_window_KeyboardEvent(vout_window_t *wnd, unsigned key)
{
    vout_display_t *vd = (vout_display_t *)vlc_object_parent(wnd);
    vout_display_sys_t *sys = vd->sys;

    vlc_mutex_lock(&sys->lock);
    vout_window_ReportKeyPress(vd->cfg->window, key);
    vlc_mutex_unlock(&sys->lock);
}