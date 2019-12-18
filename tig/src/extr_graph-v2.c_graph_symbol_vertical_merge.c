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
struct graph_symbol {int /*<<< orphan*/  continued_right; scalar_t__ parent_down; scalar_t__ continued_left; scalar_t__ continued_up; scalar_t__ merge; int /*<<< orphan*/  matches_commit; scalar_t__ next_right; scalar_t__ continued_up_left; scalar_t__ shift_left; int /*<<< orphan*/  below_commit; int /*<<< orphan*/  new_column; scalar_t__ empty; } ;

/* Variables and functions */

__attribute__((used)) static bool
graph_symbol_vertical_merge(const struct graph_symbol *symbol)
{
	if (symbol->empty)
		return false;

	if (!symbol->continued_up && !symbol->new_column && !symbol->below_commit)
		return false;

	if (symbol->shift_left && symbol->continued_up_left)
		return false;

	if (symbol->next_right)
		return false;

	if (!symbol->matches_commit)
		return false;

	if (symbol->merge && symbol->continued_up && symbol->continued_left && symbol->parent_down && !symbol->continued_right)
		return true;

	return false;
}