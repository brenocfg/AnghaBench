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
struct grid_cell {scalar_t__ fg; scalar_t__ bg; int attr; } ;
struct style {scalar_t__ align; struct grid_cell gc; } ;

/* Variables and functions */
 int STYLE_ATTR_MASK ; 

int
style_equal(struct style *sy1, struct style *sy2)
{
	struct grid_cell	*gc1 = &sy1->gc;
	struct grid_cell	*gc2 = &sy2->gc;

	if (gc1->fg != gc2->fg)
		return (0);
	if (gc1->bg != gc2->bg)
		return (0);
	if ((gc1->attr & STYLE_ATTR_MASK) != (gc2->attr & STYLE_ATTR_MASK))
		return (0);
	if (sy1->align != sy2->align)
		return (0);
	return (1);
}