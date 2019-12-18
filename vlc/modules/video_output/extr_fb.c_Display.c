#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_7__ {scalar_t__ xoffset; scalar_t__ yoffset; } ;
struct TYPE_6__ {int /*<<< orphan*/  picture; TYPE_3__ var_info; int /*<<< orphan*/  fd; scalar_t__ has_pan; } ;
typedef  TYPE_2__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  picture_t ;

/* Variables and functions */
 int /*<<< orphan*/  FBIOPAN_DISPLAY ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  picture_Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Display(vout_display_t *vd, picture_t *picture)
{
    vout_display_sys_t *sys = vd->sys;

    /* swap the two Y offsets if the drivers supports panning */
    if (sys->has_pan) {
        sys->var_info.yoffset = 0;
        /*vd->sys->var_info.yoffset = vd->sys->var_info.yres; */

        /* the X offset should be 0, but who knows ...
         * some other app might have played with the framebuffer */
        sys->var_info.xoffset = 0;

        /* FIXME 'static' is damn wrong and it's dead code ... */
        static int panned = 0;
        if (panned < 0) {
            ioctl(sys->fd, FBIOPAN_DISPLAY, &sys->var_info);
            panned++;
        }
    }

    picture_Copy(sys->picture, picture);
}