#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int lu_mem ;
typedef  scalar_t__ l_mem ;
struct TYPE_3__ {int gcstate; int /*<<< orphan*/ ** sweepgc; scalar_t__ GCdebt; int /*<<< orphan*/  GCestimate; } ;
typedef  TYPE_1__ global_State ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 int GCSWEEPCOST ; 
 int GCSWEEPMAX ; 
 int /*<<< orphan*/ ** sweeplist (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static lu_mem sweepstep (lua_State *L, global_State *g,
                         int nextstate, GCObject **nextlist) {
  if (g->sweepgc) {
    l_mem olddebt = g->GCdebt;
    g->sweepgc = sweeplist(L, g->sweepgc, GCSWEEPMAX);
    g->GCestimate += g->GCdebt - olddebt;  /* update estimate */
    if (g->sweepgc)  /* is there still something to sweep? */
      return (GCSWEEPMAX * GCSWEEPCOST);
  }
  /* else enter next state */
  g->gcstate = nextstate;
  g->sweepgc = nextlist;
  return 0;
}