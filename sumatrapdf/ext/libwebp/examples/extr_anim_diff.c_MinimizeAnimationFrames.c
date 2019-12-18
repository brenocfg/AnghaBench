#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_7__ {int num_frames; TYPE_1__* frames; int /*<<< orphan*/  canvas_height; int /*<<< orphan*/  canvas_width; } ;
struct TYPE_6__ {scalar_t__ duration; int /*<<< orphan*/ * rgba; } ;
typedef  TYPE_1__ DecodedFrame ;
typedef  TYPE_2__ AnimatedImage ;

/* Variables and functions */
 scalar_t__ AdditionWillOverflow (scalar_t__,scalar_t__) ; 
 int FramesAreEqual (int /*<<< orphan*/  const* const,int /*<<< orphan*/  const* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FramesAreSimilar (int /*<<< orphan*/  const* const,int /*<<< orphan*/  const* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memmove (TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static void MinimizeAnimationFrames(AnimatedImage* const img, int max_diff) {
  uint32_t i;
  for (i = 1; i < img->num_frames; ++i) {
    DecodedFrame* const frame1 = &img->frames[i - 1];
    DecodedFrame* const frame2 = &img->frames[i];
    const uint8_t* const rgba1 = frame1->rgba;
    const uint8_t* const rgba2 = frame2->rgba;
    int should_merge_frames = 0;
    // If merging frames will result in integer overflow for 'duration',
    // skip merging.
    if (AdditionWillOverflow(frame1->duration, frame2->duration)) continue;
    if (max_diff > 0) {
      should_merge_frames = FramesAreSimilar(rgba1, rgba2, img->canvas_width,
                                             img->canvas_height, max_diff);
    } else {
      should_merge_frames =
          FramesAreEqual(rgba1, rgba2, img->canvas_width, img->canvas_height);
    }
    if (should_merge_frames) {  // Merge 'i+1'th frame into 'i'th frame.
      frame1->duration += frame2->duration;
      if (i + 1 < img->num_frames) {
        memmove(&img->frames[i], &img->frames[i + 1],
                (img->num_frames - i - 1) * sizeof(*img->frames));
      }
      --img->num_frames;
      --i;
    }
  }
}