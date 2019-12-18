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

int THSize_isSameSizeAs(const long *sizeA, long dimsA, const long *sizeB, long dimsB) {
  int d;
  if (dimsA != dimsB)
    return 0;
  for(d = 0; d < dimsA; ++d)
  {
    if(sizeA[d] != sizeB[d])
      return 0;
  }
  return 1;
}