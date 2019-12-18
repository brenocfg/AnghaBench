#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int should_try_; int empty_rect_allowed_; int /*<<< orphan*/  sub_frame_lossy_; int /*<<< orphan*/  sub_frame_ll_; } ;
typedef  TYPE_1__ SubFrameParams ;

/* Variables and functions */
 int /*<<< orphan*/  WebPPictureInit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int SubFrameParamsInit(SubFrameParams* const params,
                              int should_try, int empty_rect_allowed) {
  params->should_try_ = should_try;
  params->empty_rect_allowed_ = empty_rect_allowed;
  if (!WebPPictureInit(&params->sub_frame_ll_) ||
      !WebPPictureInit(&params->sub_frame_lossy_)) {
    return 0;
  }
  return 1;
}