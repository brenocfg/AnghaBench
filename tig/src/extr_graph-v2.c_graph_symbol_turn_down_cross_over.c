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
struct graph_symbol {scalar_t__ merge; scalar_t__ flanked; int /*<<< orphan*/  parent_right; int /*<<< orphan*/  continued_right; int /*<<< orphan*/  continued_down; } ;

/* Variables and functions */

__attribute__((used)) static bool
graph_symbol_turn_down_cross_over(const struct graph_symbol *symbol)
{
	if (!symbol->continued_down)
		return false;

	if (!symbol->continued_right)
		return false;

	if (!symbol->parent_right && !symbol->flanked)
		return false;

	if (symbol->flanked)
		return true;

	if (symbol->merge)
		return true;

	return false;
}