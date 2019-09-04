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
struct layout_cell {scalar_t__ type; struct layout_cell* parent; int /*<<< orphan*/  cells; } ;

/* Variables and functions */
 scalar_t__ LAYOUT_LEFTRIGHT ; 
 struct layout_cell* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct layout_cell* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layout_cells ; 

__attribute__((used)) static int
layout_need_status(struct layout_cell *lc, int at_top)
{
	struct layout_cell	*first_lc;

	if (lc->parent != NULL) {
		if (lc->parent->type == LAYOUT_LEFTRIGHT)
			return (layout_need_status(lc->parent, at_top));

		if (at_top)
			first_lc = TAILQ_FIRST(&lc->parent->cells);
		else
			first_lc = TAILQ_LAST(&lc->parent->cells,layout_cells);
		if (lc == first_lc)
			return (layout_need_status(lc->parent, at_top));
		return (0);
	}
	return (1);
}