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
struct TYPE_3__ {size_t start_; size_t size_; int /*<<< orphan*/ * encoded_frames_; } ;
typedef  TYPE_1__ WebPAnimEncoder ;
typedef  int /*<<< orphan*/  EncodedFrame ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static EncodedFrame* GetFrame(const WebPAnimEncoder* const enc,
                              size_t position) {
  assert(enc->start_ + position < enc->size_);
  return &enc->encoded_frames_[enc->start_ + position];
}