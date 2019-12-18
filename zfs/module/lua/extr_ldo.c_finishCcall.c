#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ nny; scalar_t__ top; int /*<<< orphan*/  errfunc; TYPE_4__* ci; } ;
typedef  TYPE_3__ lua_State ;
struct TYPE_12__ {int (* k ) (TYPE_3__*) ;scalar_t__ status; int /*<<< orphan*/  old_errfunc; } ;
struct TYPE_13__ {TYPE_1__ c; } ;
struct TYPE_15__ {int callstatus; TYPE_2__ u; int /*<<< orphan*/  nresults; } ;
typedef  TYPE_4__ CallInfo ;

/* Variables and functions */
 int CIST_STAT ; 
 int CIST_YIELDED ; 
 int CIST_YPCALL ; 
 scalar_t__ LUA_OK ; 
 scalar_t__ LUA_YIELD ; 
 int /*<<< orphan*/  adjustresults (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  api_checknelems (TYPE_3__*,int) ; 
 int /*<<< orphan*/  luaD_poscall (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  lua_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  lua_unlock (TYPE_3__*) ; 
 int stub1 (TYPE_3__*) ; 

__attribute__((used)) static void finishCcall (lua_State *L) {
  CallInfo *ci = L->ci;
  int n;
  lua_assert(ci->u.c.k != NULL);  /* must have a continuation */
  lua_assert(L->nny == 0);
  if (ci->callstatus & CIST_YPCALL) {  /* was inside a pcall? */
    ci->callstatus &= ~CIST_YPCALL;  /* finish 'lua_pcall' */
    L->errfunc = ci->u.c.old_errfunc;
  }
  /* finish 'lua_callk'/'lua_pcall' */
  adjustresults(L, ci->nresults);
  /* call continuation function */
  if (!(ci->callstatus & CIST_STAT))  /* no call status? */
    ci->u.c.status = LUA_YIELD;  /* 'default' status */
  lua_assert(ci->u.c.status != LUA_OK);
  ci->callstatus = (ci->callstatus & ~(CIST_YPCALL | CIST_STAT)) | CIST_YIELDED;
  lua_unlock(L);
  n = (*ci->u.c.k)(L);
  lua_lock(L);
  api_checknelems(L, n);
  /* finish 'luaD_precall' */
  luaD_poscall(L, L->top - n);
}