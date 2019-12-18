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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t
xorshift128(uint32_t seed[4])
{ 
  uint32_t x = seed[0];
  uint32_t y = seed[1];
  uint32_t z = seed[2];
  uint32_t w = seed[3]; 
  uint32_t t;
 
  t = x ^ (x << 11);
  x = y; y = z; z = w;
  w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
  seed[0] = x;
  seed[1] = y;
  seed[2] = z;
  seed[3] = w;
  return w;
}