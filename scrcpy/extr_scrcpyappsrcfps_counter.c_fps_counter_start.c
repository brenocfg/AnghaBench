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
struct fps_counter {int started; scalar_t__ nr_rendered; int /*<<< orphan*/  slice_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_GetTicks () ; 

void
fps_counter_start(struct fps_counter *counter) {
    counter->started = true;
    counter->slice_start = SDL_GetTicks();
    counter->nr_rendered = 0;
#ifdef SKIP_FRAMES
    counter->nr_skipped = 0;
#endif
}