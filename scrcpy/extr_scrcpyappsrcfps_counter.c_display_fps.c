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
struct fps_counter {int /*<<< orphan*/  nr_rendered; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGI (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
display_fps(struct fps_counter *counter) {
#ifdef SKIP_FRAMES
    if (counter->nr_skipped) {
        LOGI("%d fps (+%d frames skipped)", counter->nr_rendered,
                                            counter->nr_skipped);
    } else {
#endif
    LOGI("%d fps", counter->nr_rendered);
#ifdef SKIP_FRAMES
    }
#endif
}