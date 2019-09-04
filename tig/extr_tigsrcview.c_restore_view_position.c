#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ lineno; int /*<<< orphan*/  col; int /*<<< orphan*/  offset; } ;
struct view {scalar_t__ lines; TYPE_1__ prev_pos; TYPE_1__ pos; int /*<<< orphan*/  win; scalar_t__ pipe; } ;

/* Variables and functions */
 scalar_t__ check_position (TYPE_1__*) ; 
 int /*<<< orphan*/  clear_position (TYPE_1__*) ; 
 int goto_view_line (struct view*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ view_is_displayed (struct view*) ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
restore_view_position(struct view *view)
{
	/* Ensure that the view position is in a valid state. */
	if (!check_position(&view->prev_pos) ||
	    (view->pipe && view->lines <= view->prev_pos.lineno))
		return goto_view_line(view, view->pos.offset, view->pos.lineno);

	/* Changing the view position cancels the restoring. */
	/* FIXME: Changing back to the first line is not detected. */
	if (check_position(&view->pos)) {
		clear_position(&view->prev_pos);
		return false;
	}

	if (goto_view_line(view, view->prev_pos.offset, view->prev_pos.lineno) &&
	    view_is_displayed(view))
		werase(view->win);

	view->pos.col = view->prev_pos.col;
	clear_position(&view->prev_pos);

	return true;
}