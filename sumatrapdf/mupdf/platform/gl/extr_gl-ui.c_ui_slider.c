#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int x1; int x0; int y1; int y0; int member_0; int member_2; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ fz_irect ;
struct TYPE_9__ {int* hot; int* active; scalar_t__ y; int x; scalar_t__ down; int /*<<< orphan*/  lineheight; } ;

/* Variables and functions */
 int /*<<< orphan*/  UI_COLOR_BUTTON ; 
 int fz_clamp (int,int,int) ; 
 TYPE_1__ fz_make_irect (int,scalar_t__,int,scalar_t__) ; 
 TYPE_6__ ui ; 
 int /*<<< orphan*/  ui_draw_bevel (TYPE_1__,int) ; 
 int /*<<< orphan*/  ui_draw_bevel_rect (TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ui_mouse_inside (TYPE_1__) ; 
 TYPE_1__ ui_pack (int,int /*<<< orphan*/ ) ; 

int ui_slider(int *value, int min, int max, int width)
{
	static int start_value = 0;
	fz_irect area = ui_pack(width, ui.lineheight);
	int m = 6;
	int w = area.x1 - area.x0 - m * 2;
	int h = area.y1 - area.y0;
	fz_irect gutter = { area.x0, area.y0+h/2-2, area.x1, area.y0+h/2+2 };
	fz_irect thumb;
	int x;

	if (ui_mouse_inside(area))
	{
		ui.hot = value;
		if (!ui.active && ui.down)
		{
			ui.active = value;
			start_value = *value;
		}
	}

	if (ui.active == value)
	{
		if (ui.y < area.y0 || ui.y > area.y1)
			*value = start_value;
		else
		{
			float v = (float)(ui.x - (area.x0+m)) / w;
			*value = fz_clamp(min + v * (max - min), min, max);
		}
	}

	x = ((*value - min) * w) / (max - min);
	thumb = fz_make_irect(area.x0+m + x-m, area.y0, area.x0+m + x+m, area.y1);

	ui_draw_bevel(gutter, 1);
	ui_draw_bevel_rect(thumb, UI_COLOR_BUTTON, 0);

	return *value != start_value && ui.active == value && !ui.down;
}