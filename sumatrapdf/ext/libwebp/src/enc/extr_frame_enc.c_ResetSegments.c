#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int mb_w_; int mb_h_; TYPE_1__* mb_info_; } ;
typedef  TYPE_2__ VP8Encoder ;
struct TYPE_4__ {scalar_t__ segment_; } ;

/* Variables and functions */

__attribute__((used)) static void ResetSegments(VP8Encoder* const enc) {
  int n;
  for (n = 0; n < enc->mb_w_ * enc->mb_h_; ++n) {
    enc->mb_info_[n].segment_ = 0;
  }
}