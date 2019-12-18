#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct view_column_data {int /*<<< orphan*/  member_0; } ;
struct sort_state {scalar_t__ reverse; } ;
struct line {int dummy; } ;
typedef  enum view_column_type { ____Placeholder_view_column_type } view_column_type ;
struct TYPE_7__ {TYPE_1__* ops; struct sort_state sort; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* get_column_data ) (TYPE_2__*,struct line const*,struct view_column_data*) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int compare_view_column (int,int,struct line const*,struct view_column_data*,struct line const*,struct view_column_data*) ; 
 int get_sort_field (TYPE_2__*) ; 
 TYPE_2__* sorting_view ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct line const*,struct view_column_data*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,struct line const*,struct view_column_data*) ; 
 int* view_column_order ; 

__attribute__((used)) static int
sort_view_compare(const void *l1, const void *l2)
{
	const struct line *line1 = l1;
	const struct line *line2 = l2;
	struct view_column_data column_data1 = {0};
	struct view_column_data column_data2 = {0};
	struct sort_state *sort = &sorting_view->sort;
	enum view_column_type column = get_sort_field(sorting_view);
	int cmp;
	int i;

	if (!sorting_view->ops->get_column_data(sorting_view, line1, &column_data1))
		return -1;
	else if (!sorting_view->ops->get_column_data(sorting_view, line2, &column_data2))
		return 1;

	cmp = compare_view_column(column, true, line1, &column_data1, line2, &column_data2);

	/* Ensure stable sorting by ordering by the other
	 * columns if the selected column values are equal. */
	for (i = 0; !cmp && i < ARRAY_SIZE(view_column_order); i++)
		if (column != view_column_order[i])
			cmp = compare_view_column(view_column_order[i], false,
						  line1, &column_data1,
						  line2, &column_data2);

	return sort->reverse ? -cmp : cmp;
}