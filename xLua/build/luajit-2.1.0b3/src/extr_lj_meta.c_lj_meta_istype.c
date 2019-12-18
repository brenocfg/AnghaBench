#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int BCReg ;

/* Variables and functions */
 scalar_t__ LJ_DUALNUM ; 
 int LJ_TNUMX ; 
 int LJ_TSTR ; 
 int /*<<< orphan*/  curr_topL (TYPE_1__*) ; 
 int /*<<< orphan*/  lj_err_argtype (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_lib_checkint (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lj_lib_checknum (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lj_lib_checkstr (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * lj_obj_itypename ; 
 int /*<<< orphan*/  lua_assert (int) ; 

void lj_meta_istype(lua_State *L, BCReg ra, BCReg tp)
{
  L->top = curr_topL(L);
  ra++; tp--;
  lua_assert(LJ_DUALNUM || tp != ~LJ_TNUMX);  /* ISTYPE -> ISNUM broken. */
  if (LJ_DUALNUM && tp == ~LJ_TNUMX) lj_lib_checkint(L, ra);
  else if (tp == ~LJ_TNUMX+1) lj_lib_checknum(L, ra);
  else if (tp == ~LJ_TSTR) lj_lib_checkstr(L, ra);
  else lj_err_argtype(L, ra, lj_obj_itypename[tp]);
}