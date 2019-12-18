#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptrdiff_t ;
struct TYPE_15__ {int hookmask; TYPE_3__* ci; int /*<<< orphan*/  oldpc; } ;
typedef  TYPE_4__ lua_State ;
struct TYPE_16__ {int nresults; TYPE_3__* previous; int /*<<< orphan*/  func; } ;
struct TYPE_12__ {int /*<<< orphan*/  savedpc; } ;
struct TYPE_13__ {TYPE_1__ l; } ;
struct TYPE_14__ {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  StkId ;
typedef  TYPE_5__ CallInfo ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_HOOKRET ; 
 int LUA_MASKLINE ; 
 int LUA_MASKRET ; 
 int /*<<< orphan*/  luaD_hook (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int moveresults (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  restorestack (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  savestack (TYPE_4__*,int /*<<< orphan*/ ) ; 

int luaD_poscall (lua_State *L, CallInfo *ci, StkId firstResult, int nres) {
  StkId res;
  int wanted = ci->nresults;
  if (L->hookmask & (LUA_MASKRET | LUA_MASKLINE)) {
    if (L->hookmask & LUA_MASKRET) {
      ptrdiff_t fr = savestack(L, firstResult);  /* hook may change stack */
      luaD_hook(L, LUA_HOOKRET, -1);
      firstResult = restorestack(L, fr);
    }
    L->oldpc = ci->previous->u.l.savedpc;  /* 'oldpc' for caller function */
  }
  res = ci->func;  /* res == final position of 1st result */
  L->ci = ci->previous;  /* back to caller */
  /* move results to proper place */
  return moveresults(L, firstResult, res, nres, wanted);
}