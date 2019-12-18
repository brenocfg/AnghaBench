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
struct TYPE_4__ {int pipe_fd_read; int /*<<< orphan*/  lock; int /*<<< orphan*/ * thread; } ;
typedef  TYPE_1__ location_geoclue2_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_mutex_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_thread_join (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
location_geoclue2_free(location_geoclue2_state_t *state)
{
	if (state->pipe_fd_read != -1) {
		close(state->pipe_fd_read);
	}

	/* Closing the pipe should cause the thread to exit. */
	g_thread_join(state->thread);
	state->thread = NULL;

	g_mutex_clear(&state->lock);

	free(state);
}