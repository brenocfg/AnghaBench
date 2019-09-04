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
typedef  int uint32_t ;
struct fps_counter {int slice_start; scalar_t__ nr_rendered; } ;

/* Variables and functions */
 int SDL_GetTicks () ; 
 int /*<<< orphan*/  display_fps (struct fps_counter*) ; 

__attribute__((used)) static void
check_expired(struct fps_counter *counter) {
    uint32_t now = SDL_GetTicks();
    if (now - counter->slice_start >= 1000) {
        display_fps(counter);
        // add a multiple of one second
        uint32_t elapsed_slices = (now - counter->slice_start) / 1000;
        counter->slice_start += 1000 * elapsed_slices;
        counter->nr_rendered = 0;
#ifdef SKIP_FRAMES
        counter->nr_skipped = 0;
#endif
    }
}