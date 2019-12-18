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
struct TYPE_4__ {TYPE_2__* p; } ;
typedef  TYPE_1__ vout_thread_t ;
struct TYPE_5__ {int /*<<< orphan*/  display_lock; int /*<<< orphan*/ * display; int /*<<< orphan*/  dummy; } ;
typedef  TYPE_2__ vout_thread_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_display_SetSize (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

void vout_ChangeDisplaySize(vout_thread_t *vout,
                            unsigned width, unsigned height)
{
    vout_thread_sys_t *sys = vout->p;

    assert(!sys->dummy);

    /* DO NOT call this outside the vout window callbacks */
    vlc_mutex_lock(&sys->display_lock);
    if (sys->display != NULL)
        vout_display_SetSize(sys->display, width, height);
    vlc_mutex_unlock(&sys->display_lock);
}