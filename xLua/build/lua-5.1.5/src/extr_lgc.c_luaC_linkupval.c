#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_15__ {scalar_t__ gcstate; TYPE_4__* rootgc; } ;
typedef  TYPE_2__ global_State ;
struct TYPE_16__ {int /*<<< orphan*/  v; } ;
typedef  TYPE_3__ UpVal ;
struct TYPE_14__ {TYPE_4__* next; } ;
struct TYPE_17__ {TYPE_1__ gch; } ;
typedef  TYPE_4__ GCObject ;

/* Variables and functions */
 TYPE_2__* G (int /*<<< orphan*/ *) ; 
 scalar_t__ GCSfinalize ; 
 scalar_t__ GCSpause ; 
 scalar_t__ GCSpropagate ; 
 int /*<<< orphan*/  gray2black (TYPE_4__*) ; 
 scalar_t__ isgray (TYPE_4__*) ; 
 int /*<<< orphan*/  luaC_barrier (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  makewhite (TYPE_2__*,TYPE_4__*) ; 
 TYPE_4__* obj2gco (TYPE_3__*) ; 

void luaC_linkupval (lua_State *L, UpVal *uv) {
  global_State *g = G(L);
  GCObject *o = obj2gco(uv);
  o->gch.next = g->rootgc;  /* link upvalue into `rootgc' list */
  g->rootgc = o;
  if (isgray(o)) { 
    if (g->gcstate == GCSpropagate) {
      gray2black(o);  /* closed upvalues need barrier */
      luaC_barrier(L, uv, uv->v);
    }
    else {  /* sweep phase: sweep it (turning it into white) */
      makewhite(g, o);
      lua_assert(g->gcstate != GCSfinalize && g->gcstate != GCSpause);
    }
  }
}