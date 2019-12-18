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
struct TYPE_7__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_display_t ;
struct TYPE_6__ {int bits_per_pixel; } ;
struct TYPE_8__ {scalar_t__ video_ptr; scalar_t__ fd; int /*<<< orphan*/  old_info; int /*<<< orphan*/ * palette; int /*<<< orphan*/  fb_cmap; TYPE_1__ var_info; int /*<<< orphan*/  video_size; } ;
typedef  TYPE_3__ vout_display_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClearScreen (TYPE_3__*) ; 
 int /*<<< orphan*/  FBIOPUTCMAP ; 
 int /*<<< orphan*/  FBIOPUT_VSCREENINFO ; 
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioctl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  munmap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_close (scalar_t__) ; 

__attribute__((used)) static void CloseDisplay(vout_display_t *vd)
{
    vout_display_sys_t *sys = vd->sys;

    if (sys->video_ptr != MAP_FAILED) {
        ClearScreen(sys);
        munmap(sys->video_ptr, sys->video_size);
    }

    if (sys->fd >= 0) {
        /* Restore palette */
        if (sys->var_info.bits_per_pixel == 8) {
            ioctl(sys->fd, FBIOPUTCMAP, &sys->fb_cmap);
            free(sys->palette);
            sys->palette = NULL;
        }

        /* Restore fb config */
        ioctl(sys->fd, FBIOPUT_VSCREENINFO, &sys->old_info);

        /* Close fb */
        vlc_close(sys->fd);
    }
}