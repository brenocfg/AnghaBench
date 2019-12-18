#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int low; int high; int out; scalar_t__ many; } ;
typedef  TYPE_1__ cmap_splay ;

/* Variables and functions */

__attribute__((used)) static void
count_node_types(cmap_splay *node, void *arg)
{
	int *counts = (int *)arg;

	if (node->many)
		counts[2]++;
	else if (node->low <= 0xffff && node->high <= 0xFFFF && node->out <= 0xFFFF)
		counts[0]++;
	else
		counts[1]++;
}