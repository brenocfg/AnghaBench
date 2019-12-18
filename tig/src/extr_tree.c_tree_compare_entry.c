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
struct line {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ LINE_DIRECTORY ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_path (struct line const*) ; 

__attribute__((used)) static int
tree_compare_entry(const struct line *line1, const struct line *line2)
{
	if (line1->type != line2->type)
		return line1->type == LINE_DIRECTORY ? -1 : 1;
	return strcmp(tree_path(line1), tree_path(line2));
}