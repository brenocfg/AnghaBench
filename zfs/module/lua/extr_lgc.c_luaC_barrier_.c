#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_9__ {scalar_t__ gcstate; } ;
typedef  TYPE_1__ global_State ;
struct TYPE_10__ {scalar_t__ tt; } ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 scalar_t__ GCSpause ; 
 scalar_t__ LUA_TTABLE ; 
 TYPE_7__* gch (int /*<<< orphan*/ *) ; 
 scalar_t__ isblack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isdead (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int issweepphase (TYPE_1__*) ; 
 scalar_t__ iswhite (int /*<<< orphan*/ *) ; 
 scalar_t__ keepinvariantout (TYPE_1__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  makewhite (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reallymarkobject (TYPE_1__*,int /*<<< orphan*/ *) ; 

void luaC_barrier_ (lua_State *L, GCObject *o, GCObject *v) {
  global_State *g = G(L);
  lua_assert(isblack(o) && iswhite(v) && !isdead(g, v) && !isdead(g, o));
  lua_assert(g->gcstate != GCSpause);
  lua_assert(gch(o)->tt != LUA_TTABLE);
  if (keepinvariantout(g))  /* must keep invariant? */
    reallymarkobject(g, v);  /* restore invariant */
  else {  /* sweep phase */
    lua_assert(issweepphase(g));
    makewhite(g, o);  /* mark main obj. as white to avoid other barriers */
  }
}