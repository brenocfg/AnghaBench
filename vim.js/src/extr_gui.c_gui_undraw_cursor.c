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
struct TYPE_2__ {scalar_t__ col; scalar_t__ cursor_col; scalar_t__ row; scalar_t__ cursor_row; scalar_t__ cursor_is_valid; int /*<<< orphan*/  back_pixel; int /*<<< orphan*/  norm_pixel; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int GUI_MON_IS_CURSOR ; 
 int GUI_MON_NOCLEAR ; 
 scalar_t__ composing_hangul ; 
 int /*<<< orphan*/  composing_hangul_buffer ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_outstr_nowrap (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gui_redraw_block (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 

void
gui_undraw_cursor()
{
    if (gui.cursor_is_valid)
    {
#ifdef FEAT_HANGULIN
	if (composing_hangul
		    && gui.col == gui.cursor_col && gui.row == gui.cursor_row)
	    (void)gui_outstr_nowrap(composing_hangul_buffer, 2,
		    GUI_MON_IS_CURSOR | GUI_MON_NOCLEAR,
		    gui.norm_pixel, gui.back_pixel, 0);
	else
	{
#endif
	if (gui_redraw_block(gui.cursor_row, gui.cursor_col,
			      gui.cursor_row, gui.cursor_col, GUI_MON_NOCLEAR)
		&& gui.cursor_col > 0)
	    (void)gui_redraw_block(gui.cursor_row, gui.cursor_col - 1,
			 gui.cursor_row, gui.cursor_col - 1, GUI_MON_NOCLEAR);
#ifdef FEAT_HANGULIN
	    if (composing_hangul)
		(void)gui_redraw_block(gui.cursor_row, gui.cursor_col + 1,
			gui.cursor_row, gui.cursor_col + 1, GUI_MON_NOCLEAR);
	}
#endif
	/* Cursor_is_valid is reset when the cursor is undrawn, also reset it
	 * here in case it wasn't needed to undraw it. */
	gui.cursor_is_valid = FALSE;
    }
}