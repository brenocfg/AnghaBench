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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  timedelta_t ;

/* Variables and functions */
 int /*<<< orphan*/  timer_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
time_func(timedelta_t *timer, uint64_t nwarmup, uint64_t niter,
    void (*func)(void)) {
	uint64_t i;

	for (i = 0; i < nwarmup; i++) {
		func();
	}
	timer_start(timer);
	for (i = 0; i < niter; i++) {
		func();
	}
	timer_stop(timer);
}