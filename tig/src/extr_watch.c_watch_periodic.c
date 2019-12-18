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
typedef  scalar_t__ time_t ;

/* Variables and functions */
 int /*<<< orphan*/  WATCH_EVENT_PERIODIC ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watch_update (int /*<<< orphan*/ ) ; 
 scalar_t__ watches ; 

int
watch_periodic(int interval)
{
	static time_t last_update;
	int delay = -1;

	if (watches && interval > 0) {
		time_t now = time(NULL);

		if (!last_update || last_update + interval <= now) {
			watch_update(WATCH_EVENT_PERIODIC);
			last_update = now;
		}

		delay = (now - last_update + interval) * 1000;
	}

	return delay;
}