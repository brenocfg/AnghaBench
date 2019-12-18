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
struct fps_counter {scalar_t__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_WaitThread (scalar_t__,int /*<<< orphan*/ *) ; 

void
fps_counter_join(struct fps_counter *counter) {
    if (counter->thread) {
        SDL_WaitThread(counter->thread, NULL);
    }
}