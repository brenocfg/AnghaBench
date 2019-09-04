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
struct view {int /*<<< orphan*/  pos; scalar_t__ lines; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPEN_DEFAULT ; 
 int /*<<< orphan*/  OPEN_RELOAD ; 
 int /*<<< orphan*/  clear_position (int /*<<< orphan*/ *) ; 
 scalar_t__ grep_prompt () ; 
 struct view grep_view ; 
 scalar_t__ is_initial_view (struct view*) ; 
 int /*<<< orphan*/  open_view (struct view*,struct view*,int /*<<< orphan*/ ) ; 

void
open_grep_view(struct view *prev)
{
	struct view *view = &grep_view;
	bool in_grep_view = prev == view;

	if ((!prev && is_initial_view(view)) || (view->lines && !in_grep_view)) {
		open_view(prev, view, OPEN_DEFAULT);
	} else {
		if (grep_prompt()) {
			clear_position(&view->pos);
			open_view(prev, view, OPEN_RELOAD);
		}
	}
}