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
struct window {int /*<<< orphan*/  activity_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  WINDOW_ACTIVITY ; 
 int /*<<< orphan*/  alerts_queue (struct window*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
window_update_activity(struct window *w)
{
	gettimeofday(&w->activity_time, NULL);
	alerts_queue(w, WINDOW_ACTIVITY);
}