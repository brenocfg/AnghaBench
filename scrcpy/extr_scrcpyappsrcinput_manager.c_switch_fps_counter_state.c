#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ started; } ;
struct video_buffer {int /*<<< orphan*/  mutex; TYPE_1__ fps_counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGI (char*) ; 
 int /*<<< orphan*/  fps_counter_start (TYPE_1__*) ; 
 int /*<<< orphan*/  fps_counter_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
switch_fps_counter_state(struct video_buffer *vb) {
    mutex_lock(vb->mutex);
    if (vb->fps_counter.started) {
        LOGI("FPS counter stopped");
        fps_counter_stop(&vb->fps_counter);
    } else {
        LOGI("FPS counter started");
        fps_counter_start(&vb->fps_counter);
    }
    mutex_unlock(vb->mutex);
}