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
 int MAX_COEFF_THRESH ; 

void VP8SetHistogramData(const int distribution[MAX_COEFF_THRESH + 1],
                         VP8Histogram* const histo) {
  int max_value = 0, last_non_zero = 1;
  int k;
  for (k = 0; k <= MAX_COEFF_THRESH; ++k) {
    const int value = distribution[k];
    if (value > 0) {
      if (value > max_value) max_value = value;
      last_non_zero = k;
    }
  }
  histo->max_value = max_value;
  histo->last_non_zero = last_non_zero;
}