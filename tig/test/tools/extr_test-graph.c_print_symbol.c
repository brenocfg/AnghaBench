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
struct graph_symbol {int dummy; } ;
struct graph {int dummy; } ;

/* Variables and functions */
 char* graph_fn (struct graph_symbol const*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static bool
print_symbol(void *__, const struct graph *graph, const struct graph_symbol *symbol, int color_id, bool first)
{
	const char *chars = graph_fn(symbol);

	printf("%s", chars + !!first);
	return false;
}