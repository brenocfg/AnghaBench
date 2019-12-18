#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  more_data_arg; int /*<<< orphan*/  (* more_data ) (int /*<<< orphan*/ ,int) ;scalar_t__ kill_thread; int /*<<< orphan*/  complete; } ;
typedef  TYPE_1__ curlstate ;

/* Variables and functions */
 int /*<<< orphan*/  fetch_chunk (TYPE_1__*) ; 
 int /*<<< orphan*/  lock (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unlock (TYPE_1__*) ; 

__attribute__((used)) static void
fetcher_thread(curlstate *state)
{
	/* Keep fetching chunks on a background thread until
	 * either we have to kill the thread, or the fetch
	 * is complete. */
	while (1) {
		int complete;
		lock(state);
		complete = state->complete || state->kill_thread;
		unlock(state);
		if (complete)
			break;
		fetch_chunk(state);
		if (state->more_data)
			state->more_data(state->more_data_arg, 0);
	}
	if (state->more_data)
		state->more_data(state->more_data_arg, 1);
}