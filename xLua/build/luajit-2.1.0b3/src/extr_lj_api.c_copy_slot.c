#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  env; } ;
typedef  TYPE_2__ lua_State ;
struct TYPE_14__ {int /*<<< orphan*/  env; int /*<<< orphan*/  gct; } ;
struct TYPE_16__ {TYPE_1__ c; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_3__ GCfunc ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_ERR_NOENV ; 
 int /*<<< orphan*/  LJ_TFUNC ; 
 int LUA_ENVIRONINDEX ; 
 int LUA_GLOBALSINDEX ; 
 int /*<<< orphan*/  api_check (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  api_checkvalidindex (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copyTV (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* curr_func (TYPE_2__*) ; 
 int /*<<< orphan*/ * index2adr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  lj_err_msg (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_gc_barrier (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obj2gco (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tabV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvistab (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void copy_slot(lua_State *L, TValue *f, int idx)
{
  if (idx == LUA_GLOBALSINDEX) {
    api_check(L, tvistab(f));
    /* NOBARRIER: A thread (i.e. L) is never black. */
    setgcref(L->env, obj2gco(tabV(f)));
  } else if (idx == LUA_ENVIRONINDEX) {
    GCfunc *fn = curr_func(L);
    if (fn->c.gct != ~LJ_TFUNC)
      lj_err_msg(L, LJ_ERR_NOENV);
    api_check(L, tvistab(f));
    setgcref(fn->c.env, obj2gco(tabV(f)));
    lj_gc_barrier(L, fn, f);
  } else {
    TValue *o = index2adr(L, idx);
    api_checkvalidindex(L, o);
    copyTV(L, o, f);
    if (idx < LUA_GLOBALSINDEX)  /* Need a barrier for upvalues. */
      lj_gc_barrier(L, curr_func(L), f);
  }
}