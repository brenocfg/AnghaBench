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
struct position {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pop_view_history_state (int /*<<< orphan*/ *,struct position*,char**) ; 
 int /*<<< orphan*/  tree_view_history ; 

__attribute__((used)) static void
pop_tree_stack_entry(struct position *position)
{
	char *path_position = NULL;

	pop_view_history_state(&tree_view_history, position, &path_position);
	path_position[0] = 0;
}