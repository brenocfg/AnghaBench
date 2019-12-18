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
struct TYPE_4__ {int /*<<< orphan*/  loop; int /*<<< orphan*/  pipe_fd_write; } ;
typedef  TYPE_1__ location_geoclue2_state_t ;
typedef  int /*<<< orphan*/  guint ;
typedef  int /*<<< orphan*/  GSourceFunc ;
typedef  int /*<<< orphan*/  GSource ;
typedef  int /*<<< orphan*/  GMainContext ;
typedef  int /*<<< orphan*/  GIOChannel ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  G_BUS_NAME_WATCHER_FLAGS_AUTO_START ; 
 int /*<<< orphan*/  G_BUS_TYPE_SYSTEM ; 
 int G_IO_ERR ; 
 int G_IO_HUP ; 
 int G_IO_IN ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_bus_unwatch_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_bus_watch_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_io_channel_unix_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_io_channel_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_io_create_watch (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * g_main_context_new () ; 
 int /*<<< orphan*/  g_main_context_push_thread_default (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_main_context_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_main_loop_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_main_loop_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_main_loop_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_source_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_source_set_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_source_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_name_appeared ; 
 int /*<<< orphan*/  on_name_vanished ; 
 scalar_t__ on_pipe_closed ; 

__attribute__((used)) static void *
run_geoclue2_loop(void *state_)
{
	location_geoclue2_state_t *state = state_;

	GMainContext *context = g_main_context_new();
	g_main_context_push_thread_default(context);
	state->loop = g_main_loop_new(context, FALSE);

	guint watcher_id = g_bus_watch_name(
		G_BUS_TYPE_SYSTEM,
		"org.freedesktop.GeoClue2",
		G_BUS_NAME_WATCHER_FLAGS_AUTO_START,
		on_name_appeared,
		on_name_vanished,
		state, NULL);

	/* Listen for closure of pipe */
	GIOChannel *pipe_channel = g_io_channel_unix_new(state->pipe_fd_write);
	GSource *pipe_source = g_io_create_watch(
		pipe_channel, G_IO_IN | G_IO_HUP | G_IO_ERR);
        g_source_set_callback(
		pipe_source, (GSourceFunc)on_pipe_closed, state, NULL);
        g_source_attach(pipe_source, context);

	g_main_loop_run(state->loop);

	g_source_unref(pipe_source);
	g_io_channel_unref(pipe_channel);
	close(state->pipe_fd_write);

	g_bus_unwatch_name(watcher_id);

	g_main_loop_unref(state->loop);
	g_main_context_unref(context);

	return NULL;
}