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
struct mode_tree_data {int current; int height; int offset; } ;

/* Variables and functions */

__attribute__((used)) static void
mode_tree_check_selected(struct mode_tree_data *mtd)
{
	/*
	 * If the current line would now be off screen reset the offset to the
	 * last visible line.
	 */
	if (mtd->current > mtd->height - 1)
		mtd->offset = mtd->current - mtd->height + 1;
}