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
 int NUM_PARTITIONS ; 

__attribute__((used)) static int GetBinIdForEntropy(double min, double max, double val) {
  const double range = max - min;
  if (range > 0.) {
    const double delta = val - min;
    return (int)((NUM_PARTITIONS - 1e-6) * delta / range);
  } else {
    return 0;
  }
}