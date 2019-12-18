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
typedef  scalar_t__ uint32_t ;
struct fps_counter {scalar_t__ next_timestamp; int /*<<< orphan*/  mutex; int /*<<< orphan*/  state_cond; int /*<<< orphan*/  started; int /*<<< orphan*/  interrupted; } ;

/* Variables and functions */
 scalar_t__ SDL_AtomicGet (int /*<<< orphan*/ *) ; 
 scalar_t__ SDL_GetTicks () ; 
 int /*<<< orphan*/  SDL_assert (int) ; 
 int /*<<< orphan*/  check_interval_expired (struct fps_counter*,scalar_t__) ; 
 int /*<<< orphan*/  cond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_wait_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
run_fps_counter(void *data) {
    struct fps_counter *counter = data;

    mutex_lock(counter->mutex);
    while (!counter->interrupted) {
        while (!counter->interrupted && !SDL_AtomicGet(&counter->started)) {
            cond_wait(counter->state_cond, counter->mutex);
        }
        while (!counter->interrupted && SDL_AtomicGet(&counter->started)) {
            uint32_t now = SDL_GetTicks();
            check_interval_expired(counter, now);

            SDL_assert(counter->next_timestamp > now);
            uint32_t remaining = counter->next_timestamp - now;

            // ignore the reason (timeout or signaled), we just loop anyway
            cond_wait_timeout(counter->state_cond, counter->mutex, remaining);
        }
    }
    mutex_unlock(counter->mutex);
    return 0;
}