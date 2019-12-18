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
typedef  size_t u_int ;
struct mode_tree_item {scalar_t__ tagged; } ;
struct mode_tree_data {size_t line_size; TYPE_1__* line_list; } ;
struct TYPE_2__ {struct mode_tree_item* item; } ;

/* Variables and functions */

u_int
mode_tree_count_tagged(struct mode_tree_data *mtd)
{
	struct mode_tree_item	*mti;
	u_int			 i, tagged;

	tagged = 0;
	for (i = 0; i < mtd->line_size; i++) {
		mti = mtd->line_list[i].item;
		if (mti->tagged)
			tagged++;
	}
	return (tagged);
}