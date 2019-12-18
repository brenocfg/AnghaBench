#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ state; int /*<<< orphan*/  root; } ;
struct TYPE_21__ {TYPE_2__ gc; } ;
typedef  TYPE_3__ global_State ;
struct TYPE_19__ {int /*<<< orphan*/  nextgc; } ;
struct TYPE_23__ {TYPE_1__ gch; } ;
struct TYPE_22__ {int closed; int /*<<< orphan*/  tv; int /*<<< orphan*/  v; } ;
typedef  TYPE_4__ GCupval ;
typedef  TYPE_5__ GCobj ;

/* Variables and functions */
 scalar_t__ GCSatomic ; 
 scalar_t__ GCSfinalize ; 
 scalar_t__ GCSpause ; 
 scalar_t__ GCSpropagate ; 
 int /*<<< orphan*/  copyTV (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gray2black (TYPE_5__*) ; 
 scalar_t__ isgray (TYPE_5__*) ; 
 int /*<<< orphan*/  lj_gc_barrierf (TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  mainthread (TYPE_3__*) ; 
 int /*<<< orphan*/  makewhite (TYPE_3__*,TYPE_5__*) ; 
 TYPE_5__* obj2gco (TYPE_4__*) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  setgcrefr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setmref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ tviswhite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvval (TYPE_4__*) ; 

void lj_gc_closeuv(global_State *g, GCupval *uv)
{
  GCobj *o = obj2gco(uv);
  /* Copy stack slot to upvalue itself and point to the copy. */
  copyTV(mainthread(g), &uv->tv, uvval(uv));
  setmref(uv->v, &uv->tv);
  uv->closed = 1;
  setgcrefr(o->gch.nextgc, g->gc.root);
  setgcref(g->gc.root, o);
  if (isgray(o)) {  /* A closed upvalue is never gray, so fix this. */
    if (g->gc.state == GCSpropagate || g->gc.state == GCSatomic) {
      gray2black(o);  /* Make it black and preserve invariant. */
      if (tviswhite(&uv->tv))
	lj_gc_barrierf(g, o, gcV(&uv->tv));
    } else {
      makewhite(g, o);  /* Make it white, i.e. sweep the upvalue. */
      lua_assert(g->gc.state != GCSfinalize && g->gc.state != GCSpause);
    }
  }
}