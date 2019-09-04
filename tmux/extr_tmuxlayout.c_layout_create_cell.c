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
struct layout_cell {int /*<<< orphan*/ * wp; void* yoff; void* xoff; void* sy; void* sx; int /*<<< orphan*/  cells; struct layout_cell* parent; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAYOUT_WINDOWPANE ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 void* UINT_MAX ; 
 struct layout_cell* xmalloc (int) ; 

struct layout_cell *
layout_create_cell(struct layout_cell *lcparent)
{
	struct layout_cell	*lc;

	lc = xmalloc(sizeof *lc);
	lc->type = LAYOUT_WINDOWPANE;
	lc->parent = lcparent;

	TAILQ_INIT(&lc->cells);

	lc->sx = UINT_MAX;
	lc->sy = UINT_MAX;

	lc->xoff = UINT_MAX;
	lc->yoff = UINT_MAX;

	lc->wp = NULL;

	return (lc);
}