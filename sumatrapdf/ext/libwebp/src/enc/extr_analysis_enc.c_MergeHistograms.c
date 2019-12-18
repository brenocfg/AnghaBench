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
struct TYPE_4__ {scalar_t__ max_value; scalar_t__ last_non_zero; } ;
typedef  TYPE_1__ VP8Histogram ;

/* Variables and functions */

__attribute__((used)) static void MergeHistograms(const VP8Histogram* const in,
                            VP8Histogram* const out) {
  if (in->max_value > out->max_value) {
    out->max_value = in->max_value;
  }
  if (in->last_non_zero > out->last_non_zero) {
    out->last_non_zero = in->last_non_zero;
  }
}