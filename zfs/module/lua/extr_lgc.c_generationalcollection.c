#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int lu_mem ;
struct TYPE_5__ {scalar_t__ gcstate; scalar_t__ GCestimate; int gcmajorinc; } ;
typedef  TYPE_1__ global_State ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GCSpause ; 
 scalar_t__ GCSpropagate ; 
 int /*<<< orphan*/  bitmask (int /*<<< orphan*/ ) ; 
 int gettotalbytes (TYPE_1__*) ; 
 int /*<<< orphan*/  luaC_fullgc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaC_runtilstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  setpause (TYPE_1__*,int) ; 

__attribute__((used)) static void generationalcollection (lua_State *L) {
  global_State *g = G(L);
  lua_assert(g->gcstate == GCSpropagate);
  if (g->GCestimate == 0) {  /* signal for another major collection? */
    luaC_fullgc(L, 0);  /* perform a full regular collection */
    g->GCestimate = gettotalbytes(g);  /* update control */
  }
  else {
    lu_mem estimate = g->GCestimate;
    luaC_runtilstate(L, bitmask(GCSpause));  /* run complete (minor) cycle */
    g->gcstate = GCSpropagate;  /* skip restart */
    if (gettotalbytes(g) > (estimate / 100) * g->gcmajorinc)
      g->GCestimate = 0;  /* signal for a major collection */
    else
      g->GCestimate = estimate;  /* keep estimate from last major coll. */

  }
  setpause(g, gettotalbytes(g));
  lua_assert(g->gcstate == GCSpropagate);
}