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
 int /*<<< orphan*/  FilterLoop26_C (int /*<<< orphan*/ *,int,int,int,int,int,int) ; 

__attribute__((used)) static void VFilter16_C(uint8_t* p, int stride,
                        int thresh, int ithresh, int hev_thresh) {
  FilterLoop26_C(p, stride, 1, 16, thresh, ithresh, hev_thresh);
}