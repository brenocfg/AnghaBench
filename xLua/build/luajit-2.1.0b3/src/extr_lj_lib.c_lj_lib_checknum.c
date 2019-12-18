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
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 scalar_t__ LJ_UNLIKELY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LUA_TNUMBER ; 
 int /*<<< orphan*/  intV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_err_argt (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lj_strscan_num (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  numV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setnumV (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvisint (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnumber (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisstr (int /*<<< orphan*/ *) ; 

lua_Number lj_lib_checknum(lua_State *L, int narg)
{
  TValue *o = L->base + narg-1;
  if (!(o < L->top &&
	(tvisnumber(o) || (tvisstr(o) && lj_strscan_num(strV(o), o)))))
    lj_err_argt(L, narg, LUA_TNUMBER);
  if (LJ_UNLIKELY(tvisint(o))) {
    lua_Number n = (lua_Number)intV(o);
    setnumV(o, n);
    return n;
  } else {
    return numV(o);
  }
}