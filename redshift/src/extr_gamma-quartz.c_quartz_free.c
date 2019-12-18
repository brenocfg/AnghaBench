#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int display_count; struct TYPE_4__* displays; struct TYPE_4__* saved_ramps; } ;
typedef  TYPE_1__ quartz_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
quartz_free(quartz_state_t *state)
{
	if (state->displays != NULL) {
		for (int i = 0; i < state->display_count; i++) {
			free(state->displays[i].saved_ramps);
		}
	}
	free(state->displays);
	free(state);
}