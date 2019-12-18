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
struct video_buffer {int interrupted; int /*<<< orphan*/  rendering_frame_consumed_cond; int /*<<< orphan*/  mutex; scalar_t__ render_expired_frames; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 

void
video_buffer_interrupt(struct video_buffer *vb) {
    if (vb->render_expired_frames) {
        mutex_lock(vb->mutex);
        vb->interrupted = true;
        mutex_unlock(vb->mutex);
        // wake up blocking wait
        cond_signal(vb->rendering_frame_consumed_cond);
    }
}