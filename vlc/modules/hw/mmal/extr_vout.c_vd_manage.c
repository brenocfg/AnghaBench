#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_display_t ;
struct TYPE_9__ {int need_configure_display; unsigned int display_width; unsigned int display_height; int /*<<< orphan*/  manage_mutex; TYPE_1__* last_cfg; int /*<<< orphan*/  dmx_handle; } ;
typedef  TYPE_3__ vout_display_sys_t ;
struct TYPE_7__ {int /*<<< orphan*/  window; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_dmx (TYPE_2__*) ; 
 scalar_t__ query_resolution (TYPE_2__*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  vc_dispmanx_display_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_window_ReportSize (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void vd_manage(vout_display_t *vd)
{
    vout_display_sys_t *sys = vd->sys;
    unsigned width, height;

    vlc_mutex_lock(&sys->manage_mutex);

    if (sys->need_configure_display) {
        close_dmx(vd);
        sys->dmx_handle = vc_dispmanx_display_open(0);

        if (query_resolution(vd, &width, &height) >= 0) {
            sys->display_width = width;
            sys->display_height = height;
            vout_window_ReportSize(sys->last_cfg->window, width, height);
        }

        sys->need_configure_display = false;
    }

    vlc_mutex_unlock(&sys->manage_mutex);
}