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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  DoFilter2_C (int /*<<< orphan*/ *,int) ; 
 scalar_t__ NeedsFilter_C (int /*<<< orphan*/ *,int,int const) ; 

__attribute__((used)) static void SimpleHFilter16_C(uint8_t* p, int stride, int thresh) {
  int i;
  const int thresh2 = 2 * thresh + 1;
  for (i = 0; i < 16; ++i) {
    if (NeedsFilter_C(p + i * stride, 1, thresh2)) {
      DoFilter2_C(p + i * stride, 1);
    }
  }
}