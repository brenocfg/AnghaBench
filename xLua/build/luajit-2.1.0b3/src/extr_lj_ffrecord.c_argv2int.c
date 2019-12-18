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
typedef  int /*<<< orphan*/  jit_State ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_TRERR_BADTYPE ; 
 int /*<<< orphan*/  intV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_num2int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_strscan_numberobj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_trace_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  numV (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisint (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int32_t argv2int(jit_State *J, TValue *o)
{
  if (!lj_strscan_numberobj(o))
    lj_trace_err(J, LJ_TRERR_BADTYPE);
  return tvisint(o) ? intV(o) : lj_num2int(numV(o));
}