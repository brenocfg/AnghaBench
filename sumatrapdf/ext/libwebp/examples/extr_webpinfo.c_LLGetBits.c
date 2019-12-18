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
typedef  int uint64_t ;
typedef  size_t uint32_t ;

/* Variables and functions */

__attribute__((used)) static int LLGetBits(const uint8_t* const data, size_t data_size, size_t nb,
                     int* val, uint64_t* const bit_pos) {
  uint32_t i = 0;
  *val = 0;
  while (i < nb) {
    const uint64_t p = (*bit_pos)++;
    if ((p >> 3) >= data_size) {
      return 0;
    } else {
      const int bit = !!(data[p >> 3] & (1 << ((p & 7))));
      *val = *val | (bit << i);
      ++i;
    }
  }
  return 1;
}