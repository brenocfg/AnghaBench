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
struct view_state {struct position position; int /*<<< orphan*/  data; struct view_state* prev; } ;
struct view_history {int /*<<< orphan*/  state_alloc; struct view_state* stack; struct position position; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct view_state*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ view_history_is_empty (struct view_history*) ; 

bool
pop_view_history_state(struct view_history *history, struct position *position, void *data)
{
	struct view_state *state = history->stack;

	if (view_history_is_empty(history))
		return false;

	history->position = state->position;
	history->stack = state->prev;

	if (data && history->state_alloc)
		memcpy(data, state->data, history->state_alloc);
	if (position)
		*position = state->position;

	free(state);
	return true;
}