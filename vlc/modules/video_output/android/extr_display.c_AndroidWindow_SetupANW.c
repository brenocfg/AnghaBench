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
struct TYPE_9__ {TYPE_1__* anw; } ;
typedef  TYPE_3__ vout_display_sys_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_width; } ;
struct TYPE_10__ {int i_pic_count; int /*<<< orphan*/  i_android_hal; TYPE_2__ fmt; int /*<<< orphan*/  p_surface; } ;
typedef  TYPE_4__ android_window ;
struct TYPE_7__ {int (* setBuffersGeometry ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int AndroidWindow_SetupANW(vout_display_sys_t *sys,
                                  android_window *p_window)
{
    p_window->i_pic_count = 1;

    if (!sys->anw->setBuffersGeometry)
        return 0;
    return sys->anw->setBuffersGeometry(p_window->p_surface,
                                        p_window->fmt.i_width,
                                        p_window->fmt.i_height,
                                        p_window->i_android_hal);
}