#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_14__ {scalar_t__ gcstate; } ;
typedef  TYPE_1__ global_State ;
struct TYPE_15__ {int /*<<< orphan*/  gch; } ;
typedef  TYPE_2__ GCObject ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 scalar_t__ GCSfinalize ; 
 scalar_t__ GCSpause ; 
 scalar_t__ GCSpropagate ; 
 scalar_t__ LUA_TTABLE ; 
 scalar_t__ isblack (TYPE_2__*) ; 
 int /*<<< orphan*/  isdead (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ iswhite (TYPE_2__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  makewhite (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  reallymarkobject (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ ttype (int /*<<< orphan*/ *) ; 

void luaC_barrierf (lua_State *L, GCObject *o, GCObject *v) {
  global_State *g = G(L);
  lua_assert(isblack(o) && iswhite(v) && !isdead(g, v) && !isdead(g, o));
  lua_assert(g->gcstate != GCSfinalize && g->gcstate != GCSpause);
  lua_assert(ttype(&o->gch) != LUA_TTABLE);
  /* must keep invariant? */
  if (g->gcstate == GCSpropagate)
    reallymarkobject(g, v);  /* restore invariant */
  else  /* don't mind */
    makewhite(g, o);  /* mark as white just to avoid other barriers */
}