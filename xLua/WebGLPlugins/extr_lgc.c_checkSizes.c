#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  scalar_t__ l_mem ;
struct TYPE_4__ {int nuse; int size; } ;
struct TYPE_5__ {scalar_t__ gckind; scalar_t__ GCdebt; int /*<<< orphan*/  GCestimate; TYPE_1__ strt; } ;
typedef  TYPE_2__ global_State ;

/* Variables and functions */
 scalar_t__ KGC_EMERGENCY ; 
 int /*<<< orphan*/  luaS_resize (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void checkSizes (lua_State *L, global_State *g) {
  if (g->gckind != KGC_EMERGENCY) {
    l_mem olddebt = g->GCdebt;
    if (g->strt.nuse < g->strt.size / 4)  /* string table too big? */
      luaS_resize(L, g->strt.size / 2);  /* shrink it a little */
    g->GCestimate += g->GCdebt - olddebt;  /* update estimate */
  }
}