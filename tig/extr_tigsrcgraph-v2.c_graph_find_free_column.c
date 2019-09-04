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
struct graph_row {size_t size; int /*<<< orphan*/ * columns; } ;

/* Variables and functions */
 int /*<<< orphan*/  graph_column_has_commit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t
graph_find_free_column(struct graph_row *row)
{
	size_t i;

	for (i = 0; i < row->size; i++) {
		if (!graph_column_has_commit(&row->columns[i]))
			return i;
	}

	return row->size;
}