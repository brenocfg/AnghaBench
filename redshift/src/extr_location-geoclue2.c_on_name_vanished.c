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
struct TYPE_4__ {int /*<<< orphan*/  pipe_fd_write; int /*<<< orphan*/  lock; scalar_t__ available; } ;
typedef  TYPE_1__ location_geoclue2_state_t ;
typedef  TYPE_1__* gpointer ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GDBusConnection ;

/* Variables and functions */
 int /*<<< orphan*/  g_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pipeutils_signal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
on_name_vanished(GDBusConnection *connection, const gchar *name,
		 gpointer user_data)
{
	location_geoclue2_state_t *state = user_data;

	g_mutex_lock(&state->lock);

	state->available = 0;

	g_mutex_unlock(&state->lock);

	pipeutils_signal(state->pipe_fd_write);
}