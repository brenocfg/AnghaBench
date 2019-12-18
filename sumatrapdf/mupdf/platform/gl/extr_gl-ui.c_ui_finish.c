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
struct TYPE_2__ {int /*<<< orphan*/  overlay_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  glDeleteLists (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glutExit () ; 
 TYPE_1__ ui ; 
 int /*<<< orphan*/  ui_finish_fonts () ; 

void ui_finish(void)
{
	glDeleteLists(ui.overlay_list, 1);
	ui_finish_fonts();
	glutExit();
}