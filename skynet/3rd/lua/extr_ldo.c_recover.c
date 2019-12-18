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
struct TYPE_14__ {int /*<<< orphan*/  errfunc; scalar_t__ nny; int /*<<< orphan*/  allowhook; TYPE_4__* ci; } ;
typedef  TYPE_3__ lua_State ;
struct TYPE_12__ {int /*<<< orphan*/  old_errfunc; } ;
struct TYPE_13__ {TYPE_1__ c; } ;
struct TYPE_15__ {TYPE_2__ u; int /*<<< orphan*/  callstatus; int /*<<< orphan*/  extra; } ;
typedef  int /*<<< orphan*/  StkId ;
typedef  TYPE_4__ CallInfo ;

/* Variables and functions */
 TYPE_4__* findpcall (TYPE_3__*) ; 
 int /*<<< orphan*/  getoah (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaD_shrinkstack (TYPE_3__*) ; 
 int /*<<< orphan*/  luaF_close (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restorestack (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seterrorobj (TYPE_3__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int recover (lua_State *L, int status) {
  StkId oldtop;
  CallInfo *ci = findpcall(L);
  if (ci == NULL) return 0;  /* no recovery point */
  /* "finish" luaD_pcall */
  oldtop = restorestack(L, ci->extra);
  luaF_close(L, oldtop);
  seterrorobj(L, status, oldtop);
  L->ci = ci;
  L->allowhook = getoah(ci->callstatus);  /* restore original 'allowhook' */
  L->nny = 0;  /* should be zero to be yieldable */
  luaD_shrinkstack(L);
  L->errfunc = ci->u.c.old_errfunc;
  return 1;  /* continue running the coroutine */
}