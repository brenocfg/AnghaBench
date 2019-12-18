#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {scalar_t__ gcrunning; } ;
typedef  TYPE_1__ global_State ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GCSTEPSIZE ; 
 int /*<<< orphan*/  luaC_forcestep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaE_setdebt (TYPE_1__*,int /*<<< orphan*/ ) ; 

void luaC_step (lua_State *L) {
  global_State *g = G(L);
  if (g->gcrunning) luaC_forcestep(L);
  else luaE_setdebt(g, -GCSTEPSIZE);  /* avoid being called too often */
}