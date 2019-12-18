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
struct TYPE_2__ {scalar_t__ in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR ; 
 int HL_ALL ; 
 int HL_BOLD ; 
 int HL_INVERSE ; 
 int HL_UNDERLINE ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  redraw_all_later (int /*<<< orphan*/ ) ; 
 int screen_attr ; 

void
redraw_later_clear()
{
    redraw_all_later(CLEAR);
#ifdef FEAT_GUI
    if (gui.in_use)
	/* Use a code that will reset gui.highlight_mask in
	 * gui_stop_highlight(). */
	screen_attr = HL_ALL + 1;
    else
#endif
	/* Use attributes that is very unlikely to appear in text. */
	screen_attr = HL_BOLD | HL_UNDERLINE | HL_INVERSE;
}