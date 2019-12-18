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
struct window_pane {int /*<<< orphan*/  resize_timer; } ;
struct timeval {int tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  evtimer_add (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  evtimer_pending (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
server_client_start_resize_timer(struct window_pane *wp)
{
	struct timeval	tv = { .tv_usec = 250000 };

	if (!evtimer_pending(&wp->resize_timer, NULL))
		evtimer_add(&wp->resize_timer, &tv);
}