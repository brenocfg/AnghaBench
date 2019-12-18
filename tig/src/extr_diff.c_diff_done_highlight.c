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
struct diff_state {int /*<<< orphan*/  view_io; int /*<<< orphan*/  highlight; } ;

/* Variables and functions */
 int io_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_kill (int /*<<< orphan*/ *) ; 

bool
diff_done_highlight(struct diff_state *state)
{
	if (!state->highlight)
		return true;
	io_kill(&state->view_io);
	return io_done(&state->view_io);
}