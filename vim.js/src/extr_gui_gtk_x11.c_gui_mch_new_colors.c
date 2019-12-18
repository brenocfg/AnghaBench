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
struct TYPE_7__ {TYPE_1__* drawarea; int /*<<< orphan*/  back_pixel; } ;
struct TYPE_6__ {int /*<<< orphan*/  pixel; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int /*<<< orphan*/ * window; } ;
typedef  TYPE_2__ GdkColor ;

/* Variables and functions */
 int /*<<< orphan*/  gdk_window_set_background (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_3__ gui ; 

void
gui_mch_new_colors(void)
{
    if (gui.drawarea != NULL && gui.drawarea->window != NULL)
    {
	GdkColor color = { 0, 0, 0, 0 };

	color.pixel = gui.back_pixel;
	gdk_window_set_background(gui.drawarea->window, &color);
    }
}