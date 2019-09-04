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
struct video_buffer {int rendering_frame_consumed; int /*<<< orphan*/  mutex; int /*<<< orphan*/  rendering_frame_consumed_cond; int /*<<< orphan*/  interrupted; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_buffer_swap_frames (struct video_buffer*) ; 

void
video_buffer_offer_decoded_frame(struct video_buffer *vb,
                                 bool *previous_frame_skipped) {
    mutex_lock(vb->mutex);
#ifndef SKIP_FRAMES
    // if SKIP_FRAMES is disabled, then the decoder must wait for the current
    // frame to be consumed
    while (!vb->rendering_frame_consumed && !vb->interrupted) {
        cond_wait(vb->rendering_frame_consumed_cond, vb->mutex);
    }
#else
    if (vb->fps_counter.started && !vb->rendering_frame_consumed) {
        fps_counter_add_skipped_frame(&vb->fps_counter);
    }
#endif

    video_buffer_swap_frames(vb);

    *previous_frame_skipped = !vb->rendering_frame_consumed;
    vb->rendering_frame_consumed = false;

    mutex_unlock(vb->mutex);
}