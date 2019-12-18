#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_12__ {TYPE_2__* finobj; TYPE_2__* allgc; TYPE_2__** sweepgc; } ;
typedef  TYPE_1__ global_State ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_13__ {int /*<<< orphan*/  marked; struct TYPE_13__* next; } ;
typedef  TYPE_2__ GCObject ;

/* Variables and functions */
 int /*<<< orphan*/  FINALIZEDBIT ; 
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TM_GC ; 
 int /*<<< orphan*/ * gfasttm (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ issweepphase (TYPE_1__*) ; 
 int /*<<< orphan*/  l_setbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makewhite (TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__** sweeptolive (int /*<<< orphan*/ *,TYPE_2__**) ; 
 scalar_t__ tofinalize (TYPE_2__*) ; 

void luaC_checkfinalizer (lua_State *L, GCObject *o, Table *mt) {
  global_State *g = G(L);
  if (tofinalize(o) ||                 /* obj. is already marked... */
      gfasttm(g, mt, TM_GC) == NULL)   /* or has no finalizer? */
    return;  /* nothing to be done */
  else {  /* move 'o' to 'finobj' list */
    GCObject **p;
    if (issweepphase(g)) {
      makewhite(g, o);  /* "sweep" object 'o' */
      if (g->sweepgc == &o->next)  /* should not remove 'sweepgc' object */
        g->sweepgc = sweeptolive(L, g->sweepgc);  /* change 'sweepgc' */
    }
    /* search for pointer pointing to 'o' */
    for (p = &g->allgc; *p != o; p = &(*p)->next) { /* empty */ }
    *p = o->next;  /* remove 'o' from 'allgc' list */
    o->next = g->finobj;  /* link it in 'finobj' list */
    g->finobj = o;
    l_setbit(o->marked, FINALIZEDBIT);  /* mark it as such */
  }
}