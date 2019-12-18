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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int BPS ; 

__attribute__((used)) static void Mean16x4_C(const uint8_t* ref, uint32_t dc[4]) {
  int k, x, y;
  for (k = 0; k < 4; ++k) {
    uint32_t avg = 0;
    for (y = 0; y < 4; ++y) {
      for (x = 0; x < 4; ++x) {
        avg += ref[x + y * BPS];
      }
    }
    dc[k] = avg;
    ref += 4;   // go to next 4x4 block.
  }
}