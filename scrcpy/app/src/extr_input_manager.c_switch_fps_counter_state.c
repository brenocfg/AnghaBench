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
struct fps_counter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGE (char*) ; 
 int /*<<< orphan*/  LOGI (char*) ; 
 scalar_t__ fps_counter_is_started (struct fps_counter*) ; 
 scalar_t__ fps_counter_start (struct fps_counter*) ; 
 int /*<<< orphan*/  fps_counter_stop (struct fps_counter*) ; 

__attribute__((used)) static void
switch_fps_counter_state(struct fps_counter *fps_counter) {
    // the started state can only be written from the current thread, so there
    // is no ToCToU issue
    if (fps_counter_is_started(fps_counter)) {
        fps_counter_stop(fps_counter);
        LOGI("FPS counter stopped");
    } else {
        if (fps_counter_start(fps_counter)) {
            LOGI("FPS counter started");
        } else {
            LOGE("FPS counter starting failed");
        }
    }
}