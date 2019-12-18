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
struct graph_symbol {scalar_t__ merge; scalar_t__ initial; scalar_t__ boundary; scalar_t__ commit; } ;

/* Variables and functions */
 scalar_t__ graph_symbol_cross_merge (struct graph_symbol const*) ; 
 scalar_t__ graph_symbol_cross_over (struct graph_symbol const*) ; 
 scalar_t__ graph_symbol_forks (struct graph_symbol const*) ; 
 scalar_t__ graph_symbol_horizontal_bar (struct graph_symbol const*) ; 
 scalar_t__ graph_symbol_merge (struct graph_symbol const*) ; 
 scalar_t__ graph_symbol_multi_branch (struct graph_symbol const*) ; 
 scalar_t__ graph_symbol_multi_merge (struct graph_symbol const*) ; 
 scalar_t__ graph_symbol_turn_down (struct graph_symbol const*) ; 
 scalar_t__ graph_symbol_turn_down_cross_over (struct graph_symbol const*) ; 
 scalar_t__ graph_symbol_turn_left (struct graph_symbol const*) ; 
 scalar_t__ graph_symbol_vertical_bar (struct graph_symbol const*) ; 
 scalar_t__ graph_symbol_vertical_merge (struct graph_symbol const*) ; 

__attribute__((used)) static const char *
graph_symbol_to_ascii(const struct graph_symbol *symbol)
{
	if (symbol->commit) {
		if (symbol->boundary)
			return " o";
		else if (symbol->initial)
			return " I";
		else if (symbol->merge)
			return " M";
		return " *";
	}

	if (graph_symbol_cross_merge(symbol))
		return "-+";

	if (graph_symbol_vertical_merge(symbol))
		return "-|";

	if (graph_symbol_cross_over(symbol))
		return "-|";

	if (graph_symbol_vertical_bar(symbol))
		return " |";

	if (graph_symbol_turn_left(symbol))
		return "-'";

	if (graph_symbol_multi_branch(symbol))
		return "-+";

	if (graph_symbol_horizontal_bar(symbol))
		return "--";

	if (graph_symbol_forks(symbol))
		return " +";

	if (graph_symbol_turn_down_cross_over(symbol))
		return "-.";

	if (graph_symbol_turn_down(symbol))
		return " .";

	if (graph_symbol_merge(symbol))
		return "-.";

	if (graph_symbol_multi_merge(symbol))
		return "-+";

	return "  ";
}