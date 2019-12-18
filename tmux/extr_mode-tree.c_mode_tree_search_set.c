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
typedef  int /*<<< orphan*/  uint64_t ;
struct mode_tree_item {int expanded; struct mode_tree_item* parent; int /*<<< orphan*/  tag; } ;
struct mode_tree_data {TYPE_1__* wp; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PANE_REDRAW ; 
 int /*<<< orphan*/  mode_tree_build (struct mode_tree_data*) ; 
 int /*<<< orphan*/  mode_tree_draw (struct mode_tree_data*) ; 
 struct mode_tree_item* mode_tree_search_for (struct mode_tree_data*) ; 
 int /*<<< orphan*/  mode_tree_set_current (struct mode_tree_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mode_tree_search_set(struct mode_tree_data *mtd)
{
	struct mode_tree_item	*mti, *loop;
	uint64_t		 tag;

	mti = mode_tree_search_for(mtd);
	if (mti == NULL)
		return;
	tag = mti->tag;

	loop = mti->parent;
	while (loop != NULL) {
		loop->expanded = 1;
		loop = loop->parent;
	}

	mode_tree_build(mtd);
	mode_tree_set_current(mtd, tag);
	mode_tree_draw(mtd);
	mtd->wp->flags |= PANE_REDRAW;
}