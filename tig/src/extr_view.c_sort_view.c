#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sort_state {int reverse; TYPE_3__* current; } ;
struct view {TYPE_3__* columns; struct sort_state sort; } ;
struct TYPE_4__ {int /*<<< orphan*/  display; } ;
struct TYPE_5__ {TYPE_1__ id; } ;
struct TYPE_6__ {TYPE_2__ opt; struct TYPE_6__* next; } ;

/* Variables and functions */
 scalar_t__ VIEW_COLUMN_ID ; 
 scalar_t__ get_sort_field (struct view*) ; 
 int /*<<< orphan*/  resort_view (struct view*,int) ; 

void
sort_view(struct view *view, bool change_field)
{
	struct sort_state *state = &view->sort;

	if (change_field) {
		while (true) {
			state->current = state->current->next
				? state->current->next : view->columns;
			if (get_sort_field(view) == VIEW_COLUMN_ID &&
			    !state->current->opt.id.display)
				continue;
			break;
		}
	} else {
		state->reverse = !state->reverse;
	}

	resort_view(view, false);
}