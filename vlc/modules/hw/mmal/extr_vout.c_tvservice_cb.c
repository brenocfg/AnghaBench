#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_4__ {int need_configure_display; int /*<<< orphan*/  manage_mutex; } ;
typedef  TYPE_2__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tvservice_cb(void *callback_data, uint32_t reason, uint32_t param1, uint32_t param2)
{
    VLC_UNUSED(reason);
    VLC_UNUSED(param1);
    VLC_UNUSED(param2);

    vout_display_t *vd = (vout_display_t *)callback_data;
    vout_display_sys_t *sys = vd->sys;

    vlc_mutex_lock(&sys->manage_mutex);
    sys->need_configure_display = true;
    vlc_mutex_unlock(&sys->manage_mutex);
}