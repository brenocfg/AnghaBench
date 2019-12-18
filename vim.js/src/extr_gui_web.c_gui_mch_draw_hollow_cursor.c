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
typedef  int /*<<< orphan*/  guicolor_T ;
struct TYPE_2__ {int /*<<< orphan*/  col; int /*<<< orphan*/  row; } ;

/* Variables and functions */
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_mch_set_fg_color (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vimjs_draw_hollow_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
gui_mch_draw_hollow_cursor(guicolor_T color)
{
    gui_mch_set_fg_color(color);
    vimjs_draw_hollow_cursor(gui.row, gui.col);
}