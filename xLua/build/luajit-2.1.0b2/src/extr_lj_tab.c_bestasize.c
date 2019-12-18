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

__attribute__((used)) static uint32_t bestasize(uint32_t bins[], uint32_t *narray)
{
  uint32_t b, sum, na = 0, sz = 0, nn = *narray;
  for (b = 0, sum = 0; 2*nn > (1u<<b) && sum != nn; b++)
    if (bins[b] > 0 && 2*(sum += bins[b]) > (1u<<b)) {
      sz = (2u<<b)+1;
      na = sum;
    }
  *narray = sz;
  return na;
}