#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

__attribute__((used)) static double GetCombineCostFactor(int histo_size, int quality) {
  double combine_cost_factor = 0.16;
  if (quality < 90) {
    if (histo_size > 256) combine_cost_factor /= 2.;
    if (histo_size > 512) combine_cost_factor /= 2.;
    if (histo_size > 1024) combine_cost_factor /= 2.;
    if (quality <= 50) combine_cost_factor /= 2.;
  }
  return combine_cost_factor;
}