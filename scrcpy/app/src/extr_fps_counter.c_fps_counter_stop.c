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
struct fps_counter {int /*<<< orphan*/  state_cond; int /*<<< orphan*/  started; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_AtomicSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_signal (int /*<<< orphan*/ ) ; 

void
fps_counter_stop(struct fps_counter *counter) {
    SDL_AtomicSet(&counter->started, 0);
    cond_signal(counter->state_cond);
}