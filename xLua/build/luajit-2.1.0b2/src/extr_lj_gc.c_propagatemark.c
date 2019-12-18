#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_49__   TYPE_9__ ;
typedef  struct TYPE_48__   TYPE_8__ ;
typedef  struct TYPE_47__   TYPE_7__ ;
typedef  struct TYPE_46__   TYPE_6__ ;
typedef  struct TYPE_45__   TYPE_5__ ;
typedef  struct TYPE_44__   TYPE_4__ ;
typedef  struct TYPE_43__   TYPE_3__ ;
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_1__ ;
typedef  struct TYPE_40__   TYPE_11__ ;
typedef  struct TYPE_39__   TYPE_10__ ;

/* Type definitions */
struct TYPE_45__ {int stacksize; int /*<<< orphan*/  gclist; } ;
typedef  TYPE_5__ lua_State ;
struct TYPE_44__ {int /*<<< orphan*/  grayagain; int /*<<< orphan*/  gray; } ;
struct TYPE_46__ {TYPE_4__ gc; } ;
typedef  TYPE_6__ global_State ;
struct TYPE_49__ {size_t sizept; } ;
struct TYPE_48__ {int asize; int hmask; } ;
struct TYPE_47__ {int nins; int nk; int nsnap; int nsnapmap; } ;
struct TYPE_43__ {scalar_t__ nupvalues; } ;
struct TYPE_42__ {scalar_t__ nupvalues; } ;
struct TYPE_41__ {int gct; int /*<<< orphan*/  gclist; } ;
struct TYPE_40__ {TYPE_3__ c; TYPE_2__ l; } ;
struct TYPE_39__ {TYPE_1__ gch; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  SnapShot ;
typedef  int /*<<< orphan*/  SnapEntry ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  MSize ;
typedef  int /*<<< orphan*/  IRIns ;
typedef  TYPE_7__ GCtrace ;
typedef  TYPE_8__ GCtab ;
typedef  TYPE_9__ GCproto ;
typedef  TYPE_10__ GCobj ;
typedef  TYPE_11__ GCfunc ;

/* Variables and functions */
 scalar_t__ LJ_LIKELY (int) ; 
 int LJ_TFUNC ; 
 int LJ_TPROTO ; 
 int LJ_TTAB ; 
 int LJ_TTHREAD ; 
 int /*<<< orphan*/  black2gray (TYPE_10__*) ; 
 int /*<<< orphan*/  gc_traverse_func (TYPE_6__*,TYPE_11__*) ; 
 int /*<<< orphan*/  gc_traverse_proto (TYPE_6__*,TYPE_9__*) ; 
 scalar_t__ gc_traverse_tab (TYPE_6__*,TYPE_8__*) ; 
 int /*<<< orphan*/  gc_traverse_thread (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  gc_traverse_trace (TYPE_6__*,TYPE_7__*) ; 
 TYPE_11__* gco2func (TYPE_10__*) ; 
 TYPE_9__* gco2pt (TYPE_10__*) ; 
 TYPE_8__* gco2tab (TYPE_10__*) ; 
 TYPE_5__* gco2th (TYPE_10__*) ; 
 TYPE_7__* gco2trace (TYPE_10__*) ; 
 TYPE_10__* gcref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gray2black (TYPE_10__*) ; 
 int /*<<< orphan*/  isgray (TYPE_10__*) ; 
 scalar_t__ isluafunc (TYPE_11__*) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,TYPE_10__*) ; 
 int /*<<< orphan*/  setgcrefr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t sizeCfunc (int /*<<< orphan*/ ) ; 
 size_t sizeLfunc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t propagatemark(global_State *g)
{
  GCobj *o = gcref(g->gc.gray);
  int gct = o->gch.gct;
  lua_assert(isgray(o));
  gray2black(o);
  setgcrefr(g->gc.gray, o->gch.gclist);  /* Remove from gray list. */
  if (LJ_LIKELY(gct == ~LJ_TTAB)) {
    GCtab *t = gco2tab(o);
    if (gc_traverse_tab(g, t) > 0)
      black2gray(o);  /* Keep weak tables gray. */
    return sizeof(GCtab) + sizeof(TValue) * t->asize +
			   sizeof(Node) * (t->hmask + 1);
  } else if (LJ_LIKELY(gct == ~LJ_TFUNC)) {
    GCfunc *fn = gco2func(o);
    gc_traverse_func(g, fn);
    return isluafunc(fn) ? sizeLfunc((MSize)fn->l.nupvalues) :
			   sizeCfunc((MSize)fn->c.nupvalues);
  } else if (LJ_LIKELY(gct == ~LJ_TPROTO)) {
    GCproto *pt = gco2pt(o);
    gc_traverse_proto(g, pt);
    return pt->sizept;
  } else if (LJ_LIKELY(gct == ~LJ_TTHREAD)) {
    lua_State *th = gco2th(o);
    setgcrefr(th->gclist, g->gc.grayagain);
    setgcref(g->gc.grayagain, o);
    black2gray(o);  /* Threads are never black. */
    gc_traverse_thread(g, th);
    return sizeof(lua_State) + sizeof(TValue) * th->stacksize;
  } else {
#if LJ_HASJIT
    GCtrace *T = gco2trace(o);
    gc_traverse_trace(g, T);
    return ((sizeof(GCtrace)+7)&~7) + (T->nins-T->nk)*sizeof(IRIns) +
	   T->nsnap*sizeof(SnapShot) + T->nsnapmap*sizeof(SnapEntry);
#else
    lua_assert(0);
    return 0;
#endif
  }
}