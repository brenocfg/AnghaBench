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
typedef  int /*<<< orphan*/  uint32_t ;
struct fps_counter {int /*<<< orphan*/  mutex; int /*<<< orphan*/  nr_skipped; int /*<<< orphan*/  started; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_AtomicGet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_GetTicks () ; 
 int /*<<< orphan*/  check_interval_expired (struct fps_counter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 

void
fps_counter_add_skipped_frame(struct fps_counter *counter) {
    if (!SDL_AtomicGet(&counter->started)) {
        return;
    }

    mutex_lock(counter->mutex);
    uint32_t now = SDL_GetTicks();
    check_interval_expired(counter, now);
    ++counter->nr_skipped;
    mutex_unlock(counter->mutex);
}