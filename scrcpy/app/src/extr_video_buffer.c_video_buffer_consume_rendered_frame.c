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
struct video_buffer {int rendering_frame_consumed; int /*<<< orphan*/  const* rendering_frame; int /*<<< orphan*/  rendering_frame_consumed_cond; scalar_t__ render_expired_frames; int /*<<< orphan*/  fps_counter; } ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_assert (int) ; 
 int /*<<< orphan*/  cond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fps_counter_add_rendered_frame (int /*<<< orphan*/ ) ; 

const AVFrame *
video_buffer_consume_rendered_frame(struct video_buffer *vb) {
    SDL_assert(!vb->rendering_frame_consumed);
    vb->rendering_frame_consumed = true;
    fps_counter_add_rendered_frame(vb->fps_counter);
    if (vb->render_expired_frames) {
        // unblock video_buffer_offer_decoded_frame()
        cond_signal(vb->rendering_frame_consumed_cond);
    }
    return vb->rendering_frame;
}