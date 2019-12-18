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
struct window {struct layout_cell* layout_root; } ;
struct layout_cell {scalar_t__ type; int /*<<< orphan*/  cells; struct layout_cell* parent; } ;

/* Variables and functions */
 scalar_t__ LAYOUT_TOPBOTTOM ; 
 struct layout_cell* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layout_cells ; 

__attribute__((used)) static int
layout_cell_is_bottom(struct window *w, struct layout_cell *lc)
{
	struct layout_cell	*next;

	while (lc != w->layout_root) {
		next = lc->parent;
		if (next->type == LAYOUT_TOPBOTTOM &&
		    lc != TAILQ_LAST(&next->cells, layout_cells))
			return (0);
		lc = next;
	}
	return (1);
}