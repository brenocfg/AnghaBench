#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {scalar_t__ gcstate; int /*<<< orphan*/ * grayagain; } ;
typedef  TYPE_1__ global_State ;
struct TYPE_8__ {int /*<<< orphan*/ * gclist; } ;
typedef  TYPE_2__ Table ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 scalar_t__ GCSfinalize ; 
 scalar_t__ GCSpause ; 
 int /*<<< orphan*/  black2gray (int /*<<< orphan*/ *) ; 
 scalar_t__ isblack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isdead (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/ * obj2gco (TYPE_2__*) ; 

void luaC_barrierback (lua_State *L, Table *t) {
  global_State *g = G(L);
  GCObject *o = obj2gco(t);
  lua_assert(isblack(o) && !isdead(g, o));
  lua_assert(g->gcstate != GCSfinalize && g->gcstate != GCSpause);
  black2gray(o);  /* make table gray (again) */
  t->gclist = g->grayagain;
  g->grayagain = o;
}