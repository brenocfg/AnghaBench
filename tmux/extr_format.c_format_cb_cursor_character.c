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
struct TYPE_4__ {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; int /*<<< orphan*/  grid; } ;
struct window_pane {TYPE_2__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; scalar_t__ size; } ;
struct grid_cell {int flags; TYPE_1__ data; } ;
struct format_tree {struct window_pane* wp; } ;
struct format_entry {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int GRID_FLAG_PADDING ; 
 int /*<<< orphan*/  grid_view_get_cell (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct grid_cell*) ; 
 int /*<<< orphan*/  xasprintf (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
format_cb_cursor_character(struct format_tree *ft, struct format_entry *fe)
{
	struct window_pane	*wp = ft->wp;
	struct grid_cell	 gc;

	if (wp == NULL)
		return;

	grid_view_get_cell(wp->base.grid, wp->base.cx, wp->base.cy, &gc);
	if (~gc.flags & GRID_FLAG_PADDING)
		xasprintf(&fe->value, "%.*s", (int)gc.data.size, gc.data.data);
}