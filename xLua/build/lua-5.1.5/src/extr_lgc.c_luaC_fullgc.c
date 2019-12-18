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
struct TYPE_4__ {scalar_t__ gcstate; int /*<<< orphan*/ * weak; int /*<<< orphan*/ * grayagain; int /*<<< orphan*/ * gray; int /*<<< orphan*/  rootgc; int /*<<< orphan*/ * sweepgc; scalar_t__ sweepstrgc; } ;
typedef  TYPE_1__ global_State ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 scalar_t__ GCSfinalize ; 
 scalar_t__ GCSpause ; 
 scalar_t__ GCSpropagate ; 
 scalar_t__ GCSsweep ; 
 scalar_t__ GCSsweepstring ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  markroot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setthreshold (TYPE_1__*) ; 
 int /*<<< orphan*/  singlestep (int /*<<< orphan*/ *) ; 

void luaC_fullgc (lua_State *L) {
  global_State *g = G(L);
  if (g->gcstate <= GCSpropagate) {
    /* reset sweep marks to sweep all elements (returning them to white) */
    g->sweepstrgc = 0;
    g->sweepgc = &g->rootgc;
    /* reset other collector lists */
    g->gray = NULL;
    g->grayagain = NULL;
    g->weak = NULL;
    g->gcstate = GCSsweepstring;
  }
  lua_assert(g->gcstate != GCSpause && g->gcstate != GCSpropagate);
  /* finish any pending sweep phase */
  while (g->gcstate != GCSfinalize) {
    lua_assert(g->gcstate == GCSsweepstring || g->gcstate == GCSsweep);
    singlestep(L);
  }
  markroot(L);
  while (g->gcstate != GCSpause) {
    singlestep(L);
  }
  setthreshold(g);
}