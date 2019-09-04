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
struct graph {int /*<<< orphan*/  (* foreach_symbol ) (struct graph*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct commit {int /*<<< orphan*/  canvas; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_symbol ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stub1 (struct graph*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_commit(struct graph *graph, struct commit *commit, const char *title)
{
	graph->foreach_symbol(graph, &commit->canvas, print_symbol, NULL);
	printf(" %s\n", title);
}