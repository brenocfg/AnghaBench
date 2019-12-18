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
struct TYPE_2__ {int scroll_x; int scroll_y; int /*<<< orphan*/  mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  glutGetModifiers () ; 
 int /*<<< orphan*/  run_main_loop () ; 
 TYPE_1__ ui ; 
 int /*<<< orphan*/  ui_invalidate () ; 

__attribute__((used)) static void on_wheel(int wheel, int direction, int x, int y)
{
	ui.scroll_x = wheel == 1 ? direction : 0;
	ui.scroll_y = wheel == 0 ? direction : 0;
	ui.mod = glutGetModifiers();
	run_main_loop();
	ui_invalidate(); // TODO: leave this to caller
	ui.scroll_x = ui.scroll_y = 0;
}