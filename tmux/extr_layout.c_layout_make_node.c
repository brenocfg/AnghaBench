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
typedef  enum layout_type { ____Placeholder_layout_type } layout_type ;
struct TYPE_2__ {int /*<<< orphan*/ * layout_cell; } ;

/* Variables and functions */
 int LAYOUT_WINDOWPANE ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatalx (char*) ; 

void
layout_make_node(struct layout_cell *lc, enum layout_type type)
{
	if (type == LAYOUT_WINDOWPANE)
		fatalx("bad layout type");
	lc->type = type;

	TAILQ_INIT(&lc->cells);

	if (lc->wp != NULL)
		lc->wp->layout_cell = NULL;
	lc->wp = NULL;
}