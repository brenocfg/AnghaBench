#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  bitstream; } ;
typedef  TYPE_1__ WebPMuxFrameInfo ;
typedef  int /*<<< orphan*/  WebPMuxAnimDispose ;
struct TYPE_12__ {int /*<<< orphan*/  prev_rect_; } ;
typedef  TYPE_2__ WebPAnimEncoder ;
struct TYPE_15__ {size_t size; } ;
struct TYPE_14__ {scalar_t__ evaluate_; TYPE_5__ mem_; int /*<<< orphan*/  rect_; TYPE_1__ info_; } ;
struct TYPE_13__ {TYPE_1__ sub_frame_; TYPE_1__ key_frame_; } ;
typedef  TYPE_3__ EncodedFrame ;
typedef  TYPE_4__ Candidate ;

/* Variables and functions */
 int CANDIDATE_COUNT ; 
 int /*<<< orphan*/  GetEncodedData (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int LL_DISP_NONE ; 
 int LOSSY_DISP_NONE ; 
 int /*<<< orphan*/  SetPreviousDisposeMethod (TYPE_2__* const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  WEBP_MUX_DISPOSE_BACKGROUND ; 
 int /*<<< orphan*/  WEBP_MUX_DISPOSE_NONE ; 
 int /*<<< orphan*/  WebPMemoryWriterClear (TYPE_5__*) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void PickBestCandidate(WebPAnimEncoder* const enc,
                              Candidate* const candidates, int is_key_frame,
                              EncodedFrame* const encoded_frame) {
  int i;
  int best_idx = -1;
  size_t best_size = ~0;
  for (i = 0; i < CANDIDATE_COUNT; ++i) {
    if (candidates[i].evaluate_) {
      const size_t candidate_size = candidates[i].mem_.size;
      if (candidate_size < best_size) {
        best_idx = i;
        best_size = candidate_size;
      }
    }
  }
  assert(best_idx != -1);
  for (i = 0; i < CANDIDATE_COUNT; ++i) {
    if (candidates[i].evaluate_) {
      if (i == best_idx) {
        WebPMuxFrameInfo* const dst = is_key_frame
                                      ? &encoded_frame->key_frame_
                                      : &encoded_frame->sub_frame_;
        *dst = candidates[i].info_;
        GetEncodedData(&candidates[i].mem_, &dst->bitstream);
        if (!is_key_frame) {
          // Note: Previous dispose method only matters for non-keyframes.
          // Also, we don't want to modify previous dispose method that was
          // selected when a non key-frame was assumed.
          const WebPMuxAnimDispose prev_dispose_method =
              (best_idx == LL_DISP_NONE || best_idx == LOSSY_DISP_NONE)
                  ? WEBP_MUX_DISPOSE_NONE
                  : WEBP_MUX_DISPOSE_BACKGROUND;
          SetPreviousDisposeMethod(enc, prev_dispose_method);
        }
        enc->prev_rect_ = candidates[i].rect_;  // save for next frame.
      } else {
        WebPMemoryWriterClear(&candidates[i].mem_);
        candidates[i].evaluate_ = 0;
      }
    }
  }
}