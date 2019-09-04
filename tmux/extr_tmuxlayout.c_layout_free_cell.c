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
struct layout_cell {int type; TYPE_1__* wp; int /*<<< orphan*/  cells; } ;
struct TYPE_2__ {int /*<<< orphan*/ * layout_cell; } ;

/* Variables and functions */
#define  LAYOUT_LEFTRIGHT 130 
#define  LAYOUT_TOPBOTTOM 129 
#define  LAYOUT_WINDOWPANE 128 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct layout_cell* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct layout_cell*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (struct layout_cell*) ; 

void
layout_free_cell(struct layout_cell *lc)
{
	struct layout_cell	*lcchild;

	switch (lc->type) {
	case LAYOUT_LEFTRIGHT:
	case LAYOUT_TOPBOTTOM:
		while (!TAILQ_EMPTY(&lc->cells)) {
			lcchild = TAILQ_FIRST(&lc->cells);
			TAILQ_REMOVE(&lc->cells, lcchild, entry);
			layout_free_cell(lcchild);
		}
		break;
	case LAYOUT_WINDOWPANE:
		if (lc->wp != NULL)
			lc->wp->layout_cell = NULL;
		break;
	}

	free(lc);
}