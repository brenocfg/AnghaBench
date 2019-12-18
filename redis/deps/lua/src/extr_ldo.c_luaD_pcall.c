#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* ptrdiff_t ;
struct TYPE_12__ {unsigned short nCcalls; void* errfunc; int /*<<< orphan*/  allowhook; TYPE_3__* ci; int /*<<< orphan*/  savedpc; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  lu_byte ;
struct TYPE_13__ {int /*<<< orphan*/  savedpc; int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  StkId ;
typedef  int /*<<< orphan*/  Pfunc ;

/* Variables and functions */
 int luaD_rawrunprotected (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  luaD_seterrorobj (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaF_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_stack_limit (TYPE_1__*) ; 
 TYPE_3__* restoreci (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  restorestack (TYPE_1__*,void*) ; 
 void* saveci (TYPE_1__*,TYPE_3__*) ; 

int luaD_pcall (lua_State *L, Pfunc func, void *u,
                ptrdiff_t old_top, ptrdiff_t ef) {
  int status;
  unsigned short oldnCcalls = L->nCcalls;
  ptrdiff_t old_ci = saveci(L, L->ci);
  lu_byte old_allowhooks = L->allowhook;
  ptrdiff_t old_errfunc = L->errfunc;
  L->errfunc = ef;
  status = luaD_rawrunprotected(L, func, u);
  if (status != 0) {  /* an error occurred? */
    StkId oldtop = restorestack(L, old_top);
    luaF_close(L, oldtop);  /* close eventual pending closures */
    luaD_seterrorobj(L, status, oldtop);
    L->nCcalls = oldnCcalls;
    L->ci = restoreci(L, old_ci);
    L->base = L->ci->base;
    L->savedpc = L->ci->savedpc;
    L->allowhook = old_allowhooks;
    restore_stack_limit(L);
  }
  L->errfunc = old_errfunc;
  return status;
}