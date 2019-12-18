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
struct mode_tree_data {scalar_t__ line_size; int /*<<< orphan*/ * line_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mode_tree_clear_lines(struct mode_tree_data *mtd)
{
	free(mtd->line_list);
	mtd->line_list = NULL;
	mtd->line_size = 0;
}