#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  guicolor_T ;
struct TYPE_5__ {scalar_t__ char_height; int /*<<< orphan*/  row; scalar_t__ col; } ;
struct TYPE_4__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  HBRUSH ;

/* Variables and functions */
 scalar_t__ CURSOR_BAR_RIGHT ; 
 int /*<<< orphan*/  CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteBrush (int /*<<< orphan*/ ) ; 
 scalar_t__ FILL_X (scalar_t__) ; 
 scalar_t__ FILL_Y (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__ gui ; 
 int /*<<< orphan*/  s_hdc ; 

void
gui_mch_draw_part_cursor(
    int		w,
    int		h,
    guicolor_T	color)
{
    HBRUSH	hbr;
    RECT	rc;

    /*
     * Note: FillRect() excludes right and bottom of rectangle.
     */
    rc.left =
#ifdef FEAT_RIGHTLEFT
		/* vertical line should be on the right of current point */
		CURSOR_BAR_RIGHT ? FILL_X(gui.col + 1) - w :
#endif
		    FILL_X(gui.col);
    rc.top = FILL_Y(gui.row) + gui.char_height - h;
    rc.right = rc.left + w;
    rc.bottom = rc.top + h;
    hbr = CreateSolidBrush(color);
    FillRect(s_hdc, &rc, hbr);
    DeleteBrush(hbr);
}