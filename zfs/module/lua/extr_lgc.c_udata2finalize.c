#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * allgc; int /*<<< orphan*/ * tobefnz; } ;
typedef  TYPE_1__ global_State ;
struct TYPE_7__ {int /*<<< orphan*/  marked; int /*<<< orphan*/ * next; } ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 int /*<<< orphan*/  SEPARATED ; 
 TYPE_5__* gch (int /*<<< orphan*/ *) ; 
 int isfinalized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keepinvariantout (TYPE_1__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  makewhite (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resetbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static GCObject *udata2finalize (global_State *g) {
  GCObject *o = g->tobefnz;  /* get first element */
  lua_assert(isfinalized(o));
  g->tobefnz = gch(o)->next;  /* remove it from 'tobefnz' list */
  gch(o)->next = g->allgc;  /* return it to 'allgc' list */
  g->allgc = o;
  resetbit(gch(o)->marked, SEPARATED);  /* mark that it is not in 'tobefnz' */
  lua_assert(!isold(o));  /* see MOVE OLD rule */
  if (!keepinvariantout(g))  /* not keeping invariant? */
    makewhite(g, o);  /* "sweep" object */
  return o;
}