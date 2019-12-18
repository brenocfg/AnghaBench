#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {scalar_t__ nuse; } ;
struct TYPE_6__ {TYPE_1__ strt; int /*<<< orphan*/ * fixedgc; int /*<<< orphan*/ * allgc; int /*<<< orphan*/ * finobj; int /*<<< orphan*/  gckind; int /*<<< orphan*/  currentwhite; int /*<<< orphan*/ * tobefnz; } ;
typedef  TYPE_2__ global_State ;

/* Variables and functions */
 TYPE_2__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KGC_NORMAL ; 
 int /*<<< orphan*/  WHITEBITS ; 
 int /*<<< orphan*/  callallpendingfinalizers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  separatetobefnz (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sweepwholelist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

void luaC_freeallobjects (lua_State *L) {
  global_State *g = G(L);
  separatetobefnz(g, 1);  /* separate all objects with finalizers */
  lua_assert(g->finobj == NULL);
  callallpendingfinalizers(L);
  lua_assert(g->tobefnz == NULL);
  g->currentwhite = WHITEBITS; /* this "white" makes all objects look dead */
  g->gckind = KGC_NORMAL;
  sweepwholelist(L, &g->finobj);
  sweepwholelist(L, &g->allgc);
  sweepwholelist(L, &g->fixedgc);  /* collect fixed objects */
  lua_assert(g->strt.nuse == 0);
}