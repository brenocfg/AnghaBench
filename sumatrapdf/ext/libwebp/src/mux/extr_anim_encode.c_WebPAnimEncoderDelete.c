#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t size_; int /*<<< orphan*/  mux_; struct TYPE_5__* encoded_frames_; int /*<<< orphan*/  prev_canvas_disposed_; int /*<<< orphan*/  prev_canvas_; int /*<<< orphan*/  curr_canvas_copy_; } ;
typedef  TYPE_1__ WebPAnimEncoder ;

/* Variables and functions */
 int /*<<< orphan*/  FrameRelease (TYPE_1__*) ; 
 int /*<<< orphan*/  WebPMuxDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WebPPictureFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPSafeFree (TYPE_1__*) ; 

void WebPAnimEncoderDelete(WebPAnimEncoder* enc) {
  if (enc != NULL) {
    WebPPictureFree(&enc->curr_canvas_copy_);
    WebPPictureFree(&enc->prev_canvas_);
    WebPPictureFree(&enc->prev_canvas_disposed_);
    if (enc->encoded_frames_ != NULL) {
      size_t i;
      for (i = 0; i < enc->size_; ++i) {
        FrameRelease(&enc->encoded_frames_[i]);
      }
      WebPSafeFree(enc->encoded_frames_);
    }
    WebPMuxDelete(enc->mux_);
    WebPSafeFree(enc);
  }
}