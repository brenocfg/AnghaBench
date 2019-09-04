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

__attribute__((used)) static bool
flanked(struct graph_row *row, int pos, int commit_pos, const char *commit_id)
{
	int i, start, end;

	if (pos < commit_pos) {
		start = 0;
		end = pos;
	} else {
		start = pos + 1;
		end = row->size;
	}

	for (i = start; i < end; i++) {
		if (row->columns[i].id == commit_id)
			return true;
	}

	return false;
}