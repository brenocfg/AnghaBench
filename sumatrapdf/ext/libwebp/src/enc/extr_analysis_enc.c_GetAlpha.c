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
struct TYPE_3__ {int max_value; int last_non_zero; } ;
typedef  TYPE_1__ VP8Histogram ;

/* Variables and functions */
 int const ALPHA_SCALE ; 

__attribute__((used)) static int GetAlpha(const VP8Histogram* const histo) {
  // 'alpha' will later be clipped to [0..MAX_ALPHA] range, clamping outer
  // values which happen to be mostly noise. This leaves the maximum precision
  // for handling the useful small values which contribute most.
  const int max_value = histo->max_value;
  const int last_non_zero = histo->last_non_zero;
  const int alpha =
      (max_value > 1) ? ALPHA_SCALE * last_non_zero / max_value : 0;
  return alpha;
}