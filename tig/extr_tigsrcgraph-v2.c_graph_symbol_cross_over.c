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
struct graph_symbol {scalar_t__ flanked; scalar_t__ merge; scalar_t__ parent_right; scalar_t__ shift_left; int /*<<< orphan*/  below_commit; int /*<<< orphan*/  new_column; int /*<<< orphan*/  continued_up; int /*<<< orphan*/  continued_down; scalar_t__ empty; } ;

/* Variables and functions */

__attribute__((used)) static bool
graph_symbol_cross_over(const struct graph_symbol *symbol)
{
	if (symbol->empty)
		return false;

	if (!symbol->continued_down)
		return false;

	if (!symbol->continued_up && !symbol->new_column && !symbol->below_commit)
		return false;

	if (symbol->shift_left)
		return false;

	if (symbol->parent_right && symbol->merge)
		return true;

	if (symbol->flanked)
		return true;

	return false;
}