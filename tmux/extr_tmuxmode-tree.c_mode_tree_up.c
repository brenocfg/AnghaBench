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
struct mode_tree_data {scalar_t__ current; scalar_t__ line_size; scalar_t__ height; scalar_t__ offset; } ;

/* Variables and functions */

__attribute__((used)) static void
mode_tree_up(struct mode_tree_data *mtd, int wrap)
{
	if (mtd->current == 0) {
		if (wrap) {
			mtd->current = mtd->line_size - 1;
			if (mtd->line_size >= mtd->height)
				mtd->offset = mtd->line_size - mtd->height;
		}
	} else {
		mtd->current--;
		if (mtd->current < mtd->offset)
			mtd->offset--;
	}
}