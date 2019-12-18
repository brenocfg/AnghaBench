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
struct video_buffer {int /*<<< orphan*/  decoding_frame; int /*<<< orphan*/  rendering_frame; int /*<<< orphan*/  mutex; int /*<<< orphan*/  rendering_frame_consumed_cond; scalar_t__ render_expired_frames; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_DestroyCond (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_DestroyMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 

void
video_buffer_destroy(struct video_buffer *vb) {
    if (vb->render_expired_frames) {
        SDL_DestroyCond(vb->rendering_frame_consumed_cond);
    }
    SDL_DestroyMutex(vb->mutex);
    av_frame_free(&vb->rendering_frame);
    av_frame_free(&vb->decoding_frame);
}