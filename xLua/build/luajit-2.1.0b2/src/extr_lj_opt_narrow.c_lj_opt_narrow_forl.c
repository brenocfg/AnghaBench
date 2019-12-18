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
typedef  scalar_t__ lua_Number ;
typedef  int /*<<< orphan*/  jit_State ;
typedef  int /*<<< orphan*/  cTValue ;
typedef  int /*<<< orphan*/  IRType ;

/* Variables and functions */
 size_t FORL_IDX ; 
 size_t FORL_STEP ; 
 size_t FORL_STOP ; 
 int /*<<< orphan*/  IRT_INT ; 
 int /*<<< orphan*/  IRT_NUM ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 scalar_t__ narrow_forl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ numberVnum (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnumber (int /*<<< orphan*/ *) ; 

IRType lj_opt_narrow_forl(jit_State *J, cTValue *tv)
{
  lua_assert(tvisnumber(&tv[FORL_IDX]) &&
	     tvisnumber(&tv[FORL_STOP]) &&
	     tvisnumber(&tv[FORL_STEP]));
  /* Narrow only if the runtime values of start/stop/step are all integers. */
  if (narrow_forl(J, &tv[FORL_IDX]) &&
      narrow_forl(J, &tv[FORL_STOP]) &&
      narrow_forl(J, &tv[FORL_STEP])) {
    /* And if the loop index can't possibly overflow. */
    lua_Number step = numberVnum(&tv[FORL_STEP]);
    lua_Number sum = numberVnum(&tv[FORL_STOP]) + step;
    if (0 <= step ? (sum <= 2147483647.0) : (sum >= -2147483648.0))
      return IRT_INT;
  }
  return IRT_NUM;
}