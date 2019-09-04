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
struct graph_row {int size; TYPE_1__* columns; } ;
struct TYPE_2__ {char const* id; } ;

/* Variables and functions */

__attribute__((used)) static void
graph_row_clear_commit(struct graph_row *row, const char *id)
{
	int i;

	for (i = 0; i < row->size; i++) {
		if (row->columns[i].id == id) {
			row->columns[i].id = NULL;
		}
	}
}