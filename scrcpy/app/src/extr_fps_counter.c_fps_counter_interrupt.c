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
struct fps_counter {int interrupted; int /*<<< orphan*/  state_cond; int /*<<< orphan*/  mutex; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 

void
fps_counter_interrupt(struct fps_counter *counter) {
    if (!counter->thread) {
        return;
    }

    mutex_lock(counter->mutex);
    counter->interrupted = true;
    mutex_unlock(counter->mutex);
    // wake up blocking wait
    cond_signal(counter->state_cond);
}