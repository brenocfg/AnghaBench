#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ count; scalar_t__ interval; scalar_t__* burst; int /*<<< orphan*/  lock; scalar_t__ start; } ;
typedef  TYPE_1__ zfs_ratelimit_t ;
typedef  scalar_t__ hrtime_t ;

/* Variables and functions */
 scalar_t__ NSEC2SEC (scalar_t__) ; 
 scalar_t__ gethrtime () ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

int
zfs_ratelimit(zfs_ratelimit_t *rl)
{
	hrtime_t now;

	hrtime_t elapsed;
	int error = 1;

	mutex_enter(&rl->lock);

	now = gethrtime();
	elapsed = now - rl->start;

	rl->count++;
	if (NSEC2SEC(elapsed) >= rl->interval) {
		rl->start = now;
		rl->count = 0;
	} else {
		if (rl->count >= *rl->burst) {
			error = 0; /* We're ratelimiting */
		}
	}
	mutex_exit(&rl->lock);

	return (error);
}