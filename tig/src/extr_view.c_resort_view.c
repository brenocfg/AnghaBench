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
struct view {size_t lines; TYPE_1__* line; } ;
struct TYPE_2__ {size_t lineno; } ;

/* Variables and functions */
 int /*<<< orphan*/  qsort (TYPE_1__*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort_view_compare ; 
 struct view* sorting_view ; 

void
resort_view(struct view *view, bool renumber)
{
	sorting_view = view;
	qsort(view->line, view->lines, sizeof(*view->line), sort_view_compare);

	if (renumber) {
		size_t i, lineno;

		for (i = 0, lineno = 1; i < view->lines; i++)
			if (view->line[i].lineno)
				view->line[i].lineno = lineno++;
	}
}