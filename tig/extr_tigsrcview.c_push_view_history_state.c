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
struct view_state {struct view_state* data; struct position position; struct view_state* prev; } ;
struct view_history {scalar_t__ state_alloc; int /*<<< orphan*/  position; struct view_state* stack; } ;

/* Variables and functions */
 struct view_state* calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  clear_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (struct view_state*,void*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct view_state*,void*,scalar_t__) ; 

struct view_state *
push_view_history_state(struct view_history *history, struct position *position, void *data)
{
	struct view_state *state = history->stack;

	if (state && data && history->state_alloc &&
	    !memcmp(state->data, data, history->state_alloc))
		return NULL;

	state = calloc(1, sizeof(*state) + history->state_alloc);
	if (!state)
		return NULL;

	state->prev = history->stack;
	history->stack = state;
	clear_position(&history->position);
	state->position = *position;
	state->data = &state[1];
	if (data && history->state_alloc)
		memcpy(state->data, data, history->state_alloc);
	return state;
}