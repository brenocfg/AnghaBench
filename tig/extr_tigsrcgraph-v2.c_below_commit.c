#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* columns; } ;
struct TYPE_6__ {TYPE_1__* columns; } ;
struct graph_v2 {int prev_position; TYPE_4__ prev_row; TYPE_2__ row; } ;
struct TYPE_7__ {scalar_t__ id; } ;
struct TYPE_5__ {scalar_t__ id; } ;

/* Variables and functions */

__attribute__((used)) static bool
below_commit(int pos, struct graph_v2 *graph)
{
	if (pos != graph->prev_position)
		return false;

	if (graph->row.columns[pos].id != graph->prev_row.columns[pos].id)
		return false;

	return true;
}