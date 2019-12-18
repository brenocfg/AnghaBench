#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* p; } ;
typedef  TYPE_3__ vout_thread_t ;
struct TYPE_7__ {unsigned int num; unsigned int den; } ;
struct TYPE_8__ {TYPE_1__ dar; } ;
struct TYPE_10__ {int /*<<< orphan*/  display_lock; int /*<<< orphan*/ * display; int /*<<< orphan*/  window_lock; TYPE_2__ source; int /*<<< orphan*/  dummy; } ;
typedef  TYPE_4__ vout_thread_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_SetDisplayAspect (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vout_UpdateWindowSizeLocked (TYPE_3__*) ; 

void vout_ChangeDisplayAspectRatio(vout_thread_t *vout,
                                   unsigned dar_num, unsigned dar_den)
{
    vout_thread_sys_t *sys = vout->p;
    assert(!sys->dummy);

    vlc_mutex_lock(&sys->window_lock);
    sys->source.dar.num = dar_num;
    sys->source.dar.den = dar_den;

    vout_UpdateWindowSizeLocked(vout);

    vlc_mutex_lock(&sys->display_lock);
    vlc_mutex_unlock(&sys->window_lock);

    if (sys->display != NULL)
        vout_SetDisplayAspect(sys->display, dar_num, dar_den);
    vlc_mutex_unlock(&sys->display_lock);
}