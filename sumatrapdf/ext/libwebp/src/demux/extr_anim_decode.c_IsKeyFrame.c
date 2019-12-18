#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int frame_num; scalar_t__ blend_method; scalar_t__ dispose_method; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  has_alpha; } ;
typedef  TYPE_1__ WebPIterator ;

/* Variables and functions */
 scalar_t__ IsFullFrame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ WEBP_MUX_DISPOSE_BACKGROUND ; 
 scalar_t__ WEBP_MUX_NO_BLEND ; 

__attribute__((used)) static int IsKeyFrame(const WebPIterator* const curr,
                      const WebPIterator* const prev,
                      int prev_frame_was_key_frame,
                      int canvas_width, int canvas_height) {
  if (curr->frame_num == 1) {
    return 1;
  } else if ((!curr->has_alpha || curr->blend_method == WEBP_MUX_NO_BLEND) &&
             IsFullFrame(curr->width, curr->height,
                         canvas_width, canvas_height)) {
    return 1;
  } else {
    return (prev->dispose_method == WEBP_MUX_DISPOSE_BACKGROUND) &&
           (IsFullFrame(prev->width, prev->height, canvas_width,
                        canvas_height) ||
            prev_frame_was_key_frame);
  }
}