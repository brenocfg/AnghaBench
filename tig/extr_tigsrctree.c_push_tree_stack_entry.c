#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct view_state {int dummy; } ;
struct view {TYPE_1__* env; } ;
struct position {int dummy; } ;
struct TYPE_2__ {char* directory; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_position (struct position*) ; 
 int /*<<< orphan*/  pop_tree_stack_entry (int /*<<< orphan*/ *) ; 
 struct view_state* push_view_history_state (int /*<<< orphan*/ *,struct position*,char**) ; 
 int /*<<< orphan*/  string_format_from (char*,size_t*,char*,char const*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  tree_view_history ; 

__attribute__((used)) static void
push_tree_stack_entry(struct view *view, const char *name, struct position *position)
{
	size_t pathlen = strlen(view->env->directory);
	char *path_position = view->env->directory + pathlen;
	struct view_state *state = push_view_history_state(&tree_view_history, position, &path_position);

	if (!state)
		return;

	if (!string_format_from(view->env->directory, &pathlen, "%s/", name)) {
		pop_tree_stack_entry(NULL);
		return;
	}

	clear_position(position);
}