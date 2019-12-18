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
struct TYPE_3__ {int eos_; scalar_t__ bit_pos_; } ;
typedef  TYPE_1__ VP8LBitReader ;

/* Variables and functions */

__attribute__((used)) static void VP8LSetEndOfStream(VP8LBitReader* const br) {
  br->eos_ = 1;
  br->bit_pos_ = 0;  // To avoid undefined behaviour with shifts.
}