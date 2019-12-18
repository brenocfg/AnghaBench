#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct graph_row {TYPE_2__* columns; } ;
struct TYPE_3__ {scalar_t__ shift_left; } ;
struct TYPE_4__ {scalar_t__ id; TYPE_1__ symbol; } ;

/* Variables and functions */

__attribute__((used)) static bool
continued_down(struct graph_row *row, struct graph_row *next_row, int pos)
{
	if (row->columns[pos].id != next_row->columns[pos].id)
		return false;

	if (row->columns[pos].symbol.shift_left)
		return false;

	return true;
}