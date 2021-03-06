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
struct graph_symbol {scalar_t__ shift_left; scalar_t__ matches_commit; scalar_t__ below_commit; scalar_t__ new_column; scalar_t__ continued_up; scalar_t__ continue_shift; int /*<<< orphan*/  continued_down; scalar_t__ continued_right; } ;

/* Variables and functions */

__attribute__((used)) static bool
graph_symbol_turn_left(const struct graph_symbol *symbol)
{
	if (symbol->matches_commit && symbol->continued_right && !symbol->continued_down)
		return false;

	if (symbol->continue_shift)
		return false;

	if (symbol->continued_up || symbol->new_column || symbol->below_commit) {
		if (symbol->matches_commit)
			return true;

		if (symbol->shift_left)
			return true;
	}

	return false;
}