#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ state; } ;
struct TYPE_18__ {TYPE_2__ gc; } ;
typedef  TYPE_3__ global_State ;
struct TYPE_16__ {int /*<<< orphan*/  gct; } ;
struct TYPE_19__ {TYPE_1__ gch; } ;
typedef  TYPE_4__ GCobj ;

/* Variables and functions */
 scalar_t__ GCSatomic ; 
 scalar_t__ GCSfinalize ; 
 scalar_t__ GCSpause ; 
 scalar_t__ GCSpropagate ; 
 int /*<<< orphan*/  LJ_TTAB ; 
 int /*<<< orphan*/  gc_mark (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ isblack (TYPE_4__*) ; 
 int /*<<< orphan*/  isdead (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ iswhite (TYPE_4__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  makewhite (TYPE_3__*,TYPE_4__*) ; 

void lj_gc_barrierf(global_State *g, GCobj *o, GCobj *v)
{
  lua_assert(isblack(o) && iswhite(v) && !isdead(g, v) && !isdead(g, o));
  lua_assert(g->gc.state != GCSfinalize && g->gc.state != GCSpause);
  lua_assert(o->gch.gct != ~LJ_TTAB);
  /* Preserve invariant during propagation. Otherwise it doesn't matter. */
  if (g->gc.state == GCSpropagate || g->gc.state == GCSatomic)
    gc_mark(g, v);  /* Move frontier forward. */
  else
    makewhite(g, o);  /* Make it white to avoid the following barrier. */
}