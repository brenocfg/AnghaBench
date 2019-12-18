#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int x_offset; int y_offset; int dispose_method; int blend_method; } ;
typedef  TYPE_2__ WebPMuxFrameInfo ;
typedef  scalar_t__ WebPMuxError ;
struct TYPE_11__ {scalar_t__ verbose; } ;
struct TYPE_13__ {scalar_t__ flush_count_; scalar_t__ start_; int count_; scalar_t__ keyframe_; TYPE_4__* encoded_frames_; int /*<<< orphan*/  out_frame_count_; TYPE_1__ options_; int /*<<< orphan*/ * mux_; } ;
typedef  TYPE_3__ WebPAnimEncoder ;
struct TYPE_14__ {TYPE_2__ sub_frame_; TYPE_2__ key_frame_; scalar_t__ is_key_frame_; } ;
typedef  TYPE_4__ EncodedFrame ;

/* Variables and functions */
 int /*<<< orphan*/  FrameRelease (TYPE_4__* const) ; 
 TYPE_4__* GetFrame (TYPE_3__* const,int /*<<< orphan*/ ) ; 
 scalar_t__ KEYFRAME_NONE ; 
 int /*<<< orphan*/  MarkError2 (TYPE_3__* const,char*,scalar_t__) ; 
 scalar_t__ WEBP_MUX_OK ; 
 scalar_t__ WebPMuxPushFrame (int /*<<< orphan*/ *,TYPE_2__ const* const,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int FlushFrames(WebPAnimEncoder* const enc) {
  while (enc->flush_count_ > 0) {
    WebPMuxError err;
    EncodedFrame* const curr = GetFrame(enc, 0);
    const WebPMuxFrameInfo* const info =
        curr->is_key_frame_ ? &curr->key_frame_ : &curr->sub_frame_;
    assert(enc->mux_ != NULL);
    err = WebPMuxPushFrame(enc->mux_, info, 1);
    if (err != WEBP_MUX_OK) {
      MarkError2(enc, "ERROR adding frame. WebPMuxError", err);
      return 0;
    }
    if (enc->options_.verbose) {
      fprintf(stderr, "INFO: Added frame. offset:%d,%d dispose:%d blend:%d\n",
              info->x_offset, info->y_offset, info->dispose_method,
              info->blend_method);
    }
    ++enc->out_frame_count_;
    FrameRelease(curr);
    ++enc->start_;
    --enc->flush_count_;
    --enc->count_;
    if (enc->keyframe_ != KEYFRAME_NONE) --enc->keyframe_;
  }

  if (enc->count_ == 1 && enc->start_ != 0) {
    // Move enc->start to index 0.
    const int enc_start_tmp = (int)enc->start_;
    EncodedFrame temp = enc->encoded_frames_[0];
    enc->encoded_frames_[0] = enc->encoded_frames_[enc_start_tmp];
    enc->encoded_frames_[enc_start_tmp] = temp;
    FrameRelease(&enc->encoded_frames_[enc_start_tmp]);
    enc->start_ = 0;
  }
  return 1;
}