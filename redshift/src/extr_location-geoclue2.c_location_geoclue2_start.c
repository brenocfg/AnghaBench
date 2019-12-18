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
struct TYPE_4__ {int pipe_fd_read; int pipe_fd_write; int /*<<< orphan*/  thread; int /*<<< orphan*/  lock; scalar_t__ longitude; scalar_t__ latitude; scalar_t__ error; scalar_t__ available; } ;
typedef  TYPE_1__ location_geoclue2_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_thread_new (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int pipeutils_create_nonblocking (int*) ; 
 int /*<<< orphan*/  pipeutils_signal (int) ; 
 int /*<<< orphan*/  run_geoclue2_loop ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
location_geoclue2_start(location_geoclue2_state_t *state)
{
	state->pipe_fd_read = -1;
	state->pipe_fd_write = -1;

	state->available = 0;
	state->error = 0;
	state->latitude = 0;
	state->longitude = 0;

	int pipefds[2];
	int r = pipeutils_create_nonblocking(pipefds);
	if (r < 0) {
		fputs(_("Failed to start GeoClue2 provider!\n"), stderr);
		return -1;
	}

	state->pipe_fd_read = pipefds[0];
	state->pipe_fd_write = pipefds[1];

	pipeutils_signal(state->pipe_fd_write);

	g_mutex_init(&state->lock);
	state->thread = g_thread_new("geoclue2", run_geoclue2_loop, state);

	return 0;
}