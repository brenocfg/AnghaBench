#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int allowhook; int /*<<< orphan*/ * errorJmp; scalar_t__ errfunc; int /*<<< orphan*/  baseCcalls; int /*<<< orphan*/  nCcalls; int /*<<< orphan*/  base; TYPE_1__* ci; TYPE_1__* base_ci; } ;
typedef  TYPE_2__ lua_State ;
struct TYPE_7__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  luaD_seterrorobj (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaF_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_stack_limit (TYPE_2__*) ; 

__attribute__((used)) static void resetstack (lua_State *L, int status) {
  L->ci = L->base_ci;
  L->base = L->ci->base;
  luaF_close(L, L->base);  /* close eventual pending closures */
  luaD_seterrorobj(L, status, L->base);
  L->nCcalls = L->baseCcalls;
  L->allowhook = 1;
  restore_stack_limit(L);
  L->errfunc = 0;
  L->errorJmp = NULL;
}