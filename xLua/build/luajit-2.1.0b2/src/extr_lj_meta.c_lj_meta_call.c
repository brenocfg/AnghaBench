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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  cTValue ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 int LJ_FR2 ; 
 int /*<<< orphan*/  MM_call ; 
 int /*<<< orphan*/  copyTV (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_err_optype_call (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lj_meta_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvisfunc (int /*<<< orphan*/ *) ; 

void lj_meta_call(lua_State *L, TValue *func, TValue *top)
{
  cTValue *mo = lj_meta_lookup(L, func, MM_call);
  TValue *p;
  if (!tvisfunc(mo))
    lj_err_optype_call(L, func);
  for (p = top; p > func+2*LJ_FR2; p--) copyTV(L, p, p-1);
  if (LJ_FR2) copyTV(L, func+2, func);
  copyTV(L, func, mo);
}