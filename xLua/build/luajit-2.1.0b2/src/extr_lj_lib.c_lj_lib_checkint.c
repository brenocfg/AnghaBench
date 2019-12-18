#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * top; int /*<<< orphan*/ * base; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 scalar_t__ LJ_DUALNUM ; 
 scalar_t__ LJ_LIKELY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LUA_TNUMBER ; 
 int /*<<< orphan*/  intV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_err_argt (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_num2int (int /*<<< orphan*/ ) ; 
 scalar_t__ lj_strscan_numberobj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  numV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setintV (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvisint (int /*<<< orphan*/ *) ; 

int32_t lj_lib_checkint(lua_State *L, int narg)
{
  TValue *o = L->base + narg-1;
  if (!(o < L->top && lj_strscan_numberobj(o)))
    lj_err_argt(L, narg, LUA_TNUMBER);
  if (LJ_LIKELY(tvisint(o))) {
    return intV(o);
  } else {
    int32_t i = lj_num2int(numV(o));
    if (LJ_DUALNUM) setintV(o, i);
    return i;
  }
}