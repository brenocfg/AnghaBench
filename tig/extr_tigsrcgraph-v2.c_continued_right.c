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
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */

__attribute__((used)) static bool
continued_right(struct graph_row *row, int pos, int commit_pos)
{
	int i, end;

	if (pos < commit_pos)
		end = commit_pos;
	else
		end = row->size;

	for (i = pos + 1; i < end; i++) {
		if (row->columns[pos].id == row->columns[i].id)
			return true;
	}

	return false;
}