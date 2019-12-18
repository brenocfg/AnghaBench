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
struct TYPE_4__ {int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ location_geoclue2_state_t ;
typedef  TYPE_1__* gpointer ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GIOCondition ;
typedef  int /*<<< orphan*/  GIOChannel ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  g_main_loop_quit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean
on_pipe_closed(GIOChannel *channel, GIOCondition condition, gpointer user_data)
{
	location_geoclue2_state_t *state = user_data;
	g_main_loop_quit(state->loop);

	return FALSE;
}