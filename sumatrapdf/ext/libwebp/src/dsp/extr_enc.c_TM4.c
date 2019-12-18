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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  BPS ; 
 int /*<<< orphan*/  clip1 ; 

__attribute__((used)) static void TM4(uint8_t* dst, const uint8_t* top) {
  int x, y;
  const uint8_t* const clip = clip1 + 255 - top[-1];
  for (y = 0; y < 4; ++y) {
    const uint8_t* const clip_table = clip + top[-2 - y];
    for (x = 0; x < 4; ++x) {
      dst[x] = clip_table[top[x]];
    }
    dst += BPS;
  }
}