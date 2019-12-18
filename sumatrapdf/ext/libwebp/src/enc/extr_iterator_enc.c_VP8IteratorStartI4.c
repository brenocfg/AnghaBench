#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int mb_w_; } ;
typedef  TYPE_1__ VP8Encoder ;
struct TYPE_6__ {int x_; int /*<<< orphan*/ * i4_boundary_; int /*<<< orphan*/ * y_top_; int /*<<< orphan*/ * y_left_; int /*<<< orphan*/ * i4_top_; scalar_t__ i4_; TYPE_1__* enc_; } ;
typedef  TYPE_2__ VP8EncIterator ;

/* Variables and functions */
 int /*<<< orphan*/  VP8IteratorNzToBytes (TYPE_2__* const) ; 
 int* VP8TopLeftI4 ; 

void VP8IteratorStartI4(VP8EncIterator* const it) {
  const VP8Encoder* const enc = it->enc_;
  int i;

  it->i4_ = 0;    // first 4x4 sub-block
  it->i4_top_ = it->i4_boundary_ + VP8TopLeftI4[0];

  // Import the boundary samples
  for (i = 0; i < 17; ++i) {    // left
    it->i4_boundary_[i] = it->y_left_[15 - i];
  }
  for (i = 0; i < 16; ++i) {    // top
    it->i4_boundary_[17 + i] = it->y_top_[i];
  }
  // top-right samples have a special case on the far right of the picture
  if (it->x_ < enc->mb_w_ - 1) {
    for (i = 16; i < 16 + 4; ++i) {
      it->i4_boundary_[17 + i] = it->y_top_[i];
    }
  } else {    // else, replicate the last valid pixel four times
    for (i = 16; i < 16 + 4; ++i) {
      it->i4_boundary_[17 + i] = it->i4_boundary_[17 + 15];
    }
  }
  VP8IteratorNzToBytes(it);  // import the non-zero context
}