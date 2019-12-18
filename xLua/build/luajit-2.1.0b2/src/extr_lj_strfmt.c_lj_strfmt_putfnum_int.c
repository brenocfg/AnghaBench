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
typedef  int /*<<< orphan*/  lua_Number ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  scalar_t__ SFormat ;
typedef  int /*<<< orphan*/  SBuf ;

/* Variables and functions */
 scalar_t__ STRFMT_INT ; 
 scalar_t__ checki32 (scalar_t__) ; 
 int /*<<< orphan*/ * lj_strfmt_putfxint (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_strfmt_putint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

SBuf *lj_strfmt_putfnum_int(SBuf *sb, SFormat sf, lua_Number n)
{
  int64_t k = (int64_t)n;
  if (checki32(k) && sf == STRFMT_INT)
    return lj_strfmt_putint(sb, (int32_t)k);  /* Shortcut for plain %d. */
  else
    return lj_strfmt_putfxint(sb, sf, (uint64_t)k);
}