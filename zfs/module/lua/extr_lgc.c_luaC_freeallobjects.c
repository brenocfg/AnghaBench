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
struct TYPE_4__ {int size; scalar_t__ nuse; int /*<<< orphan*/ ** hash; } ;
struct TYPE_5__ {TYPE_1__ strt; int /*<<< orphan*/ * allgc; int /*<<< orphan*/ * finobj; int /*<<< orphan*/  gckind; int /*<<< orphan*/  currentwhite; } ;
typedef  TYPE_2__ global_State ;

/* Variables and functions */
 TYPE_2__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KGC_NORMAL ; 
 int /*<<< orphan*/  WHITEBITS ; 
 int /*<<< orphan*/  callallpendingfinalizers (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  separatetobefnz (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sweepwholelist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

void luaC_freeallobjects (lua_State *L) {
  global_State *g = G(L);
  int i;
  separatetobefnz(L, 1);  /* separate all objects with finalizers */
  lua_assert(g->finobj == NULL);
  callallpendingfinalizers(L, 0);
  g->currentwhite = WHITEBITS; /* this "white" makes all objects look dead */
  g->gckind = KGC_NORMAL;
  sweepwholelist(L, &g->finobj);  /* finalizers can create objs. in 'finobj' */
  sweepwholelist(L, &g->allgc);
  for (i = 0; i < g->strt.size; i++)  /* free all string lists */
    sweepwholelist(L, &g->strt.hash[i]);
  lua_assert(g->strt.nuse == 0);
}