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
typedef  int uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ LJ_UNLIKELY (int) ; 
 int* ndigits_dec_threshold ; 

__attribute__((used)) static uint32_t nd_add_m10e(uint32_t* nd, uint32_t ndhi, uint8_t m, int32_t e)
{
  uint32_t i, carry;
  if (e >= 0) {
    i = (uint32_t)e/9;
    carry = m * (ndigits_dec_threshold[e - (int32_t)i*9] + 1);
  } else {
    int32_t f = (e-8)/9;
    i = (uint32_t)(64 + f);
    carry = m * (ndigits_dec_threshold[e - f*9] + 1);
  }
  for (;;) {
    uint32_t val = nd[i] + carry;
    if (LJ_UNLIKELY(val >= 1000000000)) {
      val -= 1000000000;
      nd[i] = val;
      if (LJ_UNLIKELY(i == ndhi)) {
	ndhi = (ndhi + 1) & 0x3f;
	nd[ndhi] = 1;
	break;
      }
      carry = 1;
      i = (i + 1) & 0x3f;
    } else {
      nd[i] = val;
      break;
    }
  }
  return ndhi;
}