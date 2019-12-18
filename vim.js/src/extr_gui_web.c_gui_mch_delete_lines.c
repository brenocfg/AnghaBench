#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  scroll_region_right; int /*<<< orphan*/  scroll_region_left; int /*<<< orphan*/  scroll_region_bot; int /*<<< orphan*/  back_pixel; } ;

/* Variables and functions */
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_mch_set_bg_color (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vimjs_delete_lines (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
gui_mch_delete_lines(int row, int num_lines)
{
    gui_mch_set_bg_color(gui.back_pixel);
    vimjs_delete_lines(num_lines, row, gui.scroll_region_bot, gui.scroll_region_left, gui.scroll_region_right);
}