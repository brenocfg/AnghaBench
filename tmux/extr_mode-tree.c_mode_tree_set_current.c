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
typedef  scalar_t__ uint64_t ;
typedef  size_t u_int ;
struct mode_tree_data {size_t line_size; size_t current; int height; int offset; TYPE_2__* line_list; } ;
struct TYPE_4__ {TYPE_1__* item; } ;
struct TYPE_3__ {scalar_t__ tag; } ;

/* Variables and functions */

void
mode_tree_set_current(struct mode_tree_data *mtd, uint64_t tag)
{
	u_int	i;

	for (i = 0; i < mtd->line_size; i++) {
		if (mtd->line_list[i].item->tag == tag)
			break;
	}
	if (i != mtd->line_size) {
		mtd->current = i;
		if (mtd->current > mtd->height - 1)
			mtd->offset = mtd->current - mtd->height + 1;
		else
			mtd->offset = 0;
	} else {
		mtd->current = 0;
		mtd->offset = 0;
	}
}