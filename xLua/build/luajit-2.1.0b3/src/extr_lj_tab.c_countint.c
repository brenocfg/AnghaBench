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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ lua_Number ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  cTValue ;

/* Variables and functions */
 scalar_t__ LJ_MAX_ASIZE ; 
 size_t lj_fls (scalar_t__) ; 
 int lj_num2int (scalar_t__) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 scalar_t__ numV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvisint (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnum (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t countint(cTValue *key, uint32_t *bins)
{
  lua_assert(!tvisint(key));
  if (tvisnum(key)) {
    lua_Number nk = numV(key);
    int32_t k = lj_num2int(nk);
    if ((uint32_t)k < LJ_MAX_ASIZE && nk == (lua_Number)k) {
      bins[(k > 2 ? lj_fls((uint32_t)(k-1)) : 0)]++;
      return 1;
    }
  }
  return 0;
}