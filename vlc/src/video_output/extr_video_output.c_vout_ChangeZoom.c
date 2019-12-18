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
struct TYPE_8__ {TYPE_1__ zoom; } ;
struct TYPE_10__ {int /*<<< orphan*/  display_lock; int /*<<< orphan*/ * display; int /*<<< orphan*/  window_lock; TYPE_2__ display_cfg; int /*<<< orphan*/  dummy; } ;
typedef  TYPE_4__ vout_thread_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_ureduce (unsigned int*,unsigned int*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vout_SetDisplayZoom (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vout_UpdateWindowSizeLocked (TYPE_3__*) ; 

void vout_ChangeZoom(vout_thread_t *vout, unsigned num, unsigned den)
{
    vout_thread_sys_t *sys = vout->p;
    assert(!sys->dummy);

    if (num != 0 && den != 0) {
        vlc_ureduce(&num, &den, num, den, 0);
    } else {
        num = 1;
        den = 1;
    }

    if (num * 10 < den) {
        num = 1;
        den = 10;
    } else if (num > den * 10) {
        num = 10;
        den = 1;
    }

    vlc_mutex_lock(&sys->window_lock);
    sys->display_cfg.zoom.num = num;
    sys->display_cfg.zoom.den = den;

    vout_UpdateWindowSizeLocked(vout);

    vlc_mutex_lock(&sys->display_lock);
    vlc_mutex_unlock(&sys->window_lock);

    if (sys->display != NULL)
        vout_SetDisplayZoom(sys->display, num, den);
    vlc_mutex_unlock(&sys->display_lock);
}