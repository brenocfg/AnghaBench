#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ started; } ;
struct video_buffer {int rendering_frame_consumed; int /*<<< orphan*/  const* rendering_frame; int /*<<< orphan*/  rendering_frame_consumed_cond; TYPE_1__ fps_counter; } ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_assert (int) ; 
 int /*<<< orphan*/  cond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fps_counter_add_rendered_frame (TYPE_1__*) ; 

const AVFrame *
video_buffer_consume_rendered_frame(struct video_buffer *vb) {
    SDL_assert(!vb->rendering_frame_consumed);
    vb->rendering_frame_consumed = true;
    if (vb->fps_counter.started) {
        fps_counter_add_rendered_frame(&vb->fps_counter);
    }
#ifndef SKIP_FRAMES
    // if SKIP_FRAMES is disabled, then notify the decoder the current frame is
    // consumed, so that it may push a new one
    cond_signal(vb->rendering_frame_consumed_cond);
#endif
    return vb->rendering_frame;
}