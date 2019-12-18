#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lon; int /*<<< orphan*/  lat; } ;
typedef  TYPE_1__ location_t ;
struct TYPE_6__ {int error; int available; int /*<<< orphan*/  lock; int /*<<< orphan*/  longitude; int /*<<< orphan*/  latitude; int /*<<< orphan*/  pipe_fd_read; } ;
typedef  TYPE_2__ location_geoclue2_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  g_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pipeutils_handle_signal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
location_geoclue2_handle(
	location_geoclue2_state_t *state,
	location_t *location, int *available)
{
	pipeutils_handle_signal(state->pipe_fd_read);

	g_mutex_lock(&state->lock);

	int error = state->error;
	location->lat = state->latitude;
	location->lon = state->longitude;
	*available = state->available;

	g_mutex_unlock(&state->lock);

	if (error) return -1;

	return 0;
}