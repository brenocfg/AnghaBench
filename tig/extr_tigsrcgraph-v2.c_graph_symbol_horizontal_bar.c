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
struct graph_symbol {int /*<<< orphan*/  below_commit; int /*<<< orphan*/  continued_up_left; scalar_t__ continued_up; int /*<<< orphan*/  continued_right; int /*<<< orphan*/  parent_right; scalar_t__ continued_down; scalar_t__ shift_left; int /*<<< orphan*/  next_right; } ;

/* Variables and functions */

__attribute__((used)) static bool
graph_symbol_horizontal_bar(const struct graph_symbol *symbol)
{
	if (!symbol->next_right)
		return false;

	if (symbol->shift_left)
		return true;

	if (symbol->continued_down)
		return false;

	if (!symbol->parent_right && !symbol->continued_right)
		return false;

	if ((symbol->continued_up && !symbol->continued_up_left))
		return false;

	if (!symbol->below_commit)
		return true;

	return false;
}