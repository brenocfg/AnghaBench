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
struct timer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPIN_LOCK (struct timer*) ; 
 int /*<<< orphan*/  SPIN_UNLOCK (struct timer*) ; 
 int /*<<< orphan*/  timer_execute (struct timer*) ; 
 int /*<<< orphan*/  timer_shift (struct timer*) ; 

__attribute__((used)) static void 
timer_update(struct timer *T) {
	SPIN_LOCK(T);

	// try to dispatch timeout 0 (rare condition)
	timer_execute(T);

	// shift time first, and then dispatch timer message
	timer_shift(T);

	timer_execute(T);

	SPIN_UNLOCK(T);
}