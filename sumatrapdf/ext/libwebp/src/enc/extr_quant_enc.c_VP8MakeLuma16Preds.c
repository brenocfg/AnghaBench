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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  yuv_p_; int /*<<< orphan*/ * y_top_; scalar_t__ y_; int /*<<< orphan*/ * y_left_; scalar_t__ x_; } ;
typedef  TYPE_1__ VP8EncIterator ;

/* Variables and functions */
 int /*<<< orphan*/  VP8EncPredLuma16 (int /*<<< orphan*/ ,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const* const) ; 

void VP8MakeLuma16Preds(const VP8EncIterator* const it) {
  const uint8_t* const left = it->x_ ? it->y_left_ : NULL;
  const uint8_t* const top = it->y_ ? it->y_top_ : NULL;
  VP8EncPredLuma16(it->yuv_p_, left, top);
}