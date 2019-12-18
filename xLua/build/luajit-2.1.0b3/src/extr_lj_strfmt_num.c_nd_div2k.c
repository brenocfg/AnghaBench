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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  SFormat ;

/* Variables and functions */
 scalar_t__ STRFMT_FP (int /*<<< orphan*/ ) ; 
 scalar_t__ STRFMT_PREC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRFMT_T_FP_F ; 
 int lj_ffs (int) ; 
 int lj_fls (int) ; 

__attribute__((used)) static uint32_t nd_div2k(uint32_t* nd, uint32_t ndhi, uint32_t k, SFormat sf)
{
  uint32_t ndlo = 0, stop1 = ~0, stop2 = ~0;
  /* Performance hacks. */
  if (!ndhi) {
    if (!nd[0]) {
      return 0;
    } else {
      uint32_t s = lj_ffs(nd[0]);
      if (s >= k) { nd[0] >>= k; return 0; }
      nd[0] >>= s; k -= s;
    }
  }
  if (k > 18) {
    if (STRFMT_FP(sf) == STRFMT_FP(STRFMT_T_FP_F)) {
      stop1 = 63 - (int32_t)STRFMT_PREC(sf) / 9;
    } else {
      int32_t floorlog2 = ndhi * 29 + lj_fls(nd[ndhi]) - k;
      int32_t floorlog10 = (int32_t)(floorlog2 * 0.30102999566398114);
      stop1 = 62 + (floorlog10 - (int32_t)STRFMT_PREC(sf)) / 9;
      stop2 = 61 + ndhi - (int32_t)STRFMT_PREC(sf) / 8;
    }
  }
  /* Real logic. */
  while (k >= 9) {
    uint32_t i = ndhi, carry = 0;
    for (;;) {
      uint32_t val = nd[i];
      nd[i] = (val >> 9) + carry;
      carry = (val & 0x1ff) * 1953125;
      if (i == ndlo) break;
      i = (i - 1) & 0x3f;
    }
    if (ndlo != stop1 && ndlo != stop2) {
      if (carry) { ndlo = (ndlo - 1) & 0x3f; nd[ndlo] = carry; }
      if (!nd[ndhi]) { ndhi = (ndhi - 1) & 0x3f; stop2--; }
    } else if (!nd[ndhi]) {
      if (ndhi != ndlo) { ndhi = (ndhi - 1) & 0x3f; stop2--; }
      else return ndlo;
    }
    k -= 9;
  }
  if (k) {
    uint32_t mask = (1U << k) - 1, mul = 1000000000 >> k, i = ndhi, carry = 0;
    for (;;) {
      uint32_t val = nd[i];
      nd[i] = (val >> k) + carry;
      carry = (val & mask) * mul;
      if (i == ndlo) break;
      i = (i - 1) & 0x3f;
    }
    if (carry) { ndlo = (ndlo - 1) & 0x3f; nd[ndlo] = carry; }
  }
  return ndlo;
}