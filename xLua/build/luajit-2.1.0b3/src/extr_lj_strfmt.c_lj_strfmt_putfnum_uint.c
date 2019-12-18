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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  double lua_Number ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  SFormat ;
typedef  int /*<<< orphan*/  SBuf ;

/* Variables and functions */
 int /*<<< orphan*/ * lj_strfmt_putfxint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SBuf *lj_strfmt_putfnum_uint(SBuf *sb, SFormat sf, lua_Number n)
{
  int64_t k;
  if (n >= 9223372036854775808.0)
    k = (int64_t)(n - 18446744073709551616.0);
  else
    k = (int64_t)n;
  return lj_strfmt_putfxint(sb, sf, (uint64_t)k);
}