#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ nny; scalar_t__ top; int /*<<< orphan*/  errfunc; TYPE_4__* ci; } ;
typedef  TYPE_3__ lua_State ;
struct TYPE_13__ {int (* k ) (TYPE_3__*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ctx; int /*<<< orphan*/  old_errfunc; } ;
struct TYPE_14__ {TYPE_1__ c; } ;
struct TYPE_16__ {int callstatus; TYPE_2__ u; int /*<<< orphan*/  nresults; } ;
typedef  TYPE_4__ CallInfo ;

/* Variables and functions */
 int CIST_YPCALL ; 
 int LUA_YIELD ; 
 int /*<<< orphan*/  adjustresults (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  api_checknelems (TYPE_3__*,int) ; 
 int /*<<< orphan*/  luaD_poscall (TYPE_3__*,TYPE_4__*,scalar_t__,int) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  lua_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  lua_unlock (TYPE_3__*) ; 
 int stub1 (TYPE_3__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void finishCcall (lua_State *L, int status) {
  CallInfo *ci = L->ci;
  int n;
  /* must have a continuation and must be able to call it */
  lua_assert(ci->u.c.k != NULL && L->nny == 0);
  /* error status can only happen in a protected call */
  lua_assert((ci->callstatus & CIST_YPCALL) || status == LUA_YIELD);
  if (ci->callstatus & CIST_YPCALL) {  /* was inside a pcall? */
    ci->callstatus &= ~CIST_YPCALL;  /* continuation is also inside it */
    L->errfunc = ci->u.c.old_errfunc;  /* with the same error function */
  }
  /* finish 'lua_callk'/'lua_pcall'; CIST_YPCALL and 'errfunc' already
     handled */
  adjustresults(L, ci->nresults);
  lua_unlock(L);
  n = (*ci->u.c.k)(L, status, ci->u.c.ctx);  /* call continuation function */
  lua_lock(L);
  api_checknelems(L, n);
  luaD_poscall(L, ci, L->top - n, n);  /* finish 'luaD_precall' */
}