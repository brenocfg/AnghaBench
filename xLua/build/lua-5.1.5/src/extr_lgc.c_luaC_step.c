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
typedef  int l_mem ;
struct TYPE_4__ {int gcstepmul; int gcdept; scalar_t__ gcstate; scalar_t__ totalbytes; scalar_t__ GCthreshold; } ;
typedef  TYPE_1__ global_State ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 int GCSTEPSIZE ; 
 scalar_t__ GCSpause ; 
 int MAX_LUMEM ; 
 int /*<<< orphan*/  setthreshold (TYPE_1__*) ; 
 scalar_t__ singlestep (int /*<<< orphan*/ *) ; 

void luaC_step (lua_State *L) {
  global_State *g = G(L);
  l_mem lim = (GCSTEPSIZE/100) * g->gcstepmul;
  if (lim == 0)
    lim = (MAX_LUMEM-1)/2;  /* no limit */
  g->gcdept += g->totalbytes - g->GCthreshold;
  do {
    lim -= singlestep(L);
    if (g->gcstate == GCSpause)
      break;
  } while (lim > 0);
  if (g->gcstate != GCSpause) {
    if (g->gcdept < GCSTEPSIZE)
      g->GCthreshold = g->totalbytes + GCSTEPSIZE;  /* - lim/g->gcstepmul;*/
    else {
      g->gcdept -= GCSTEPSIZE;
      g->GCthreshold = g->totalbytes;
    }
  }
  else {
    setthreshold(g);
  }
}