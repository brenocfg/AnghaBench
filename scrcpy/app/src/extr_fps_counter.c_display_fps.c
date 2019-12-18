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
struct fps_counter {int nr_rendered; int /*<<< orphan*/  nr_skipped; } ;

/* Variables and functions */
 int FPS_COUNTER_INTERVAL_MS ; 
 int /*<<< orphan*/  LOGI (char*,unsigned int,...) ; 

__attribute__((used)) static void
display_fps(struct fps_counter *counter) {
    unsigned rendered_per_second =
        counter->nr_rendered * 1000 / FPS_COUNTER_INTERVAL_MS;
    if (counter->nr_skipped) {
        LOGI("%u fps (+%u frames skipped)", rendered_per_second,
                                            counter->nr_skipped);
    } else {
        LOGI("%u fps", rendered_per_second);
    }
}