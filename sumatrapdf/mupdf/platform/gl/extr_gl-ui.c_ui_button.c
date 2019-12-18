#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int x0; int x1; scalar_t__ y0; } ;
typedef  TYPE_1__ fz_irect ;
struct TYPE_7__ {char const* hot; char const* active; scalar_t__ down; int /*<<< orphan*/  gridsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  UI_COLOR_BUTTON ; 
 int /*<<< orphan*/  UI_COLOR_TEXT_FG ; 
 int /*<<< orphan*/  glColorHex (int /*<<< orphan*/ ) ; 
 TYPE_5__ ui ; 
 int /*<<< orphan*/  ui_draw_bevel_rect (TYPE_1__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ui_draw_string (int,scalar_t__,char const*) ; 
 int ui_measure_string (char const*) ; 
 scalar_t__ ui_mouse_inside (TYPE_1__) ; 
 TYPE_1__ ui_pack (int,int /*<<< orphan*/ ) ; 

int ui_button(const char *label)
{
	int width = ui_measure_string(label);
	fz_irect area = ui_pack(width + 20, ui.gridsize);
	int text_x = area.x0 + ((area.x1 - area.x0) - width) / 2;
	int pressed;

	if (ui_mouse_inside(area))
	{
		ui.hot = label;
		if (!ui.active && ui.down)
			ui.active = label;
	}

	pressed = (ui.hot == label && ui.active == label && ui.down);
	ui_draw_bevel_rect(area, UI_COLOR_BUTTON, pressed);
	glColorHex(UI_COLOR_TEXT_FG);
	ui_draw_string(text_x + pressed, area.y0+3 + pressed, label);

	return ui.hot == label && ui.active == label && !ui.down;
}