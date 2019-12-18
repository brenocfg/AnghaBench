#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* p; } ;
typedef  TYPE_2__ vout_thread_t ;
struct TYPE_6__ {int /*<<< orphan*/  window; } ;
struct TYPE_8__ {int /*<<< orphan*/  window_lock; TYPE_1__ display_cfg; int /*<<< orphan*/  dummy; } ;
typedef  TYPE_3__ vout_thread_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_UpdateWindowSizeLocked (TYPE_2__*) ; 
 int /*<<< orphan*/  vout_window_UnsetFullScreen (int /*<<< orphan*/ ) ; 

void vout_ChangeWindowed(vout_thread_t *vout)
{
    assert(!vout->p->dummy);
    vlc_mutex_lock(&vout->p->window_lock);
    vout_thread_sys_t *sys = vout->p;
    vout_window_UnsetFullScreen(sys->display_cfg.window);
    /* Attempt to reset the intended window size */
    vout_UpdateWindowSizeLocked(vout);
    vlc_mutex_unlock(&vout->p->window_lock);
}