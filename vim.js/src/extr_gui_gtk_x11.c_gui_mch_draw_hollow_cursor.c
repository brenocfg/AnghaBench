#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  guicolor_T ;
struct TYPE_4__ {int char_width; scalar_t__ char_height; int /*<<< orphan*/  row; int /*<<< orphan*/  col; int /*<<< orphan*/  text_gc; TYPE_1__* drawarea; int /*<<< orphan*/  fgcolor; } ;
struct TYPE_3__ {int /*<<< orphan*/ * window; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILL_X (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILL_Y (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_draw_rectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  gdk_gc_set_foreground (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ gui ; 
 int /*<<< orphan*/  gui_mch_set_fg_color (int /*<<< orphan*/ ) ; 
 scalar_t__ mb_lefthalve (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
gui_mch_draw_hollow_cursor(guicolor_T color)
{
    int		i = 1;

    if (gui.drawarea->window == NULL)
	return;

    gui_mch_set_fg_color(color);

    gdk_gc_set_foreground(gui.text_gc, gui.fgcolor);
    if (mb_lefthalve(gui.row, gui.col))
	i = 2;
    gdk_draw_rectangle(gui.drawarea->window, gui.text_gc,
	    FALSE,
	    FILL_X(gui.col), FILL_Y(gui.row),
	    i * gui.char_width - 1, gui.char_height - 1);
}