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
typedef  int /*<<< orphan*/  fz_irect ;
struct TYPE_2__ {int window_w; int window_h; } ;

/* Variables and functions */
 int /*<<< orphan*/  UI_COLOR_PANEL ; 
 int /*<<< orphan*/  fz_expand_irect (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_make_irect (int,int,int,int) ; 
 TYPE_1__ ui ; 
 int /*<<< orphan*/  ui_draw_bevel_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_pack_push (int /*<<< orphan*/ ) ; 

void ui_dialog_begin(int w, int h)
{
	fz_irect area;
	int x, y;
	w += 24 + 4;
	h += 24 + 4;
	if (w > ui.window_w) w = ui.window_w - 20;
	if (h > ui.window_h) h = ui.window_h - 20;
	x = (ui.window_w-w)/2;
	y = (ui.window_h-h)/3;
	area = fz_make_irect(x, y, x+w, y+h);
	ui_draw_bevel_rect(area, UI_COLOR_PANEL, 0);
	area = fz_expand_irect(area, -14);
	ui_pack_push(area);
}