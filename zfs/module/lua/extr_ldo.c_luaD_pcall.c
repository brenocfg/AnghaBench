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
typedef  void* ptrdiff_t ;
struct TYPE_8__ {unsigned short nny; void* errfunc; int /*<<< orphan*/  allowhook; int /*<<< orphan*/ * ci; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  lu_byte ;
typedef  int /*<<< orphan*/  StkId ;
typedef  int /*<<< orphan*/  Pfunc ;
typedef  int /*<<< orphan*/  CallInfo ;

/* Variables and functions */
 int LUA_OK ; 
 int luaD_rawrunprotected (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  luaD_shrinkstack (TYPE_1__*) ; 
 int /*<<< orphan*/  luaF_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restorestack (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  seterrorobj (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

int luaD_pcall (lua_State *L, Pfunc func, void *u,
                ptrdiff_t old_top, ptrdiff_t ef) {
  int status;
  CallInfo *old_ci = L->ci;
  lu_byte old_allowhooks = L->allowhook;
  unsigned short old_nny = L->nny;
  ptrdiff_t old_errfunc = L->errfunc;
  L->errfunc = ef;
  status = luaD_rawrunprotected(L, func, u);
  if (status != LUA_OK) {  /* an error occurred? */
    StkId oldtop = restorestack(L, old_top);
    luaF_close(L, oldtop);  /* close possible pending closures */
    seterrorobj(L, status, oldtop);
    L->ci = old_ci;
    L->allowhook = old_allowhooks;
    L->nny = old_nny;
    luaD_shrinkstack(L);
  }
  L->errfunc = old_errfunc;
  return status;
}