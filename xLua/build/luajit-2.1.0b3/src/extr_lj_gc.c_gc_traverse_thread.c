#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int stacksize; int /*<<< orphan*/  env; int /*<<< orphan*/  stack; int /*<<< orphan*/ * top; } ;
typedef  TYPE_2__ lua_State ;
struct TYPE_11__ {scalar_t__ state; } ;
struct TYPE_13__ {TYPE_1__ gc; } ;
typedef  TYPE_3__ global_State ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 scalar_t__ GCSatomic ; 
 int LJ_FR2 ; 
 int /*<<< orphan*/  gc_markobj (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_marktv (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gc_traverse_frames (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  lj_state_shrinkstack (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setnilV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tabref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tvref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gc_traverse_thread(global_State *g, lua_State *th)
{
  TValue *o, *top = th->top;
  for (o = tvref(th->stack)+1+LJ_FR2; o < top; o++)
    gc_marktv(g, o);
  if (g->gc.state == GCSatomic) {
    top = tvref(th->stack) + th->stacksize;
    for (; o < top; o++)  /* Clear unmarked slots. */
      setnilV(o);
  }
  gc_markobj(g, tabref(th->env));
  lj_state_shrinkstack(th, gc_traverse_frames(g, th));
}