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
struct fps_counter {scalar_t__ next_timestamp; scalar_t__ nr_skipped; scalar_t__ nr_rendered; } ;

/* Variables and functions */
 scalar_t__ FPS_COUNTER_INTERVAL_MS ; 
 int /*<<< orphan*/  display_fps (struct fps_counter*) ; 

__attribute__((used)) static void
check_interval_expired(struct fps_counter *counter, uint32_t now) {
    if (now < counter->next_timestamp) {
        return;
    }

    display_fps(counter);
    counter->nr_rendered = 0;
    counter->nr_skipped = 0;
    // add a multiple of the interval
    uint32_t elapsed_slices =
        (now - counter->next_timestamp) / FPS_COUNTER_INTERVAL_MS + 1;
    counter->next_timestamp += FPS_COUNTER_INTERVAL_MS * elapsed_slices;
}