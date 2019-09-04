#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct window_pane {int dummy; } ;
struct window {int /*<<< orphan*/  sy; int /*<<< orphan*/  sx; struct layout_cell* layout_root; } ;
struct layout_cell {int dummy; } ;

/* Variables and functions */
 struct layout_cell* layout_create_cell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  layout_fix_panes (struct window*) ; 
 int /*<<< orphan*/  layout_make_leaf (struct layout_cell*,struct window_pane*) ; 
 int /*<<< orphan*/  layout_set_size (struct layout_cell*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
layout_init(struct window *w, struct window_pane *wp)
{
	struct layout_cell	*lc;

	lc = w->layout_root = layout_create_cell(NULL);
	layout_set_size(lc, w->sx, w->sy, 0, 0);
	layout_make_leaf(lc, wp);
	layout_fix_panes(w);
}