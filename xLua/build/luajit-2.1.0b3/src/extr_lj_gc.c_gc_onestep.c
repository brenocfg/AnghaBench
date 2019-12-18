#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_11__ {int state; int sweepstr; size_t total; size_t estimate; int nocdatafin; int /*<<< orphan*/  debt; int /*<<< orphan*/  mmudata; int /*<<< orphan*/  sweep; int /*<<< orphan*/  gray; } ;
struct TYPE_12__ {int strmask; int strnum; TYPE_1__ gc; int /*<<< orphan*/  jit_base; int /*<<< orphan*/ * strhash; } ;
typedef  TYPE_2__ global_State ;
struct TYPE_13__ {int /*<<< orphan*/  finalizer; } ;
typedef  size_t GCSize ;

/* Variables and functions */
 TYPE_2__* G (int /*<<< orphan*/ *) ; 
 size_t GCFINALIZECOST ; 
 int /*<<< orphan*/  GCRef ; 
 size_t GCSWEEPCOST ; 
 size_t GCSWEEPMAX ; 
#define  GCSatomic 133 
#define  GCSfinalize 132 
#define  GCSpause 131 
#define  GCSpropagate 130 
#define  GCSsweep 129 
#define  GCSsweepstring 128 
 size_t LJ_MAX_MEM ; 
 int LJ_MIN_STRTAB ; 
 int /*<<< orphan*/  atomic (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_7__* ctype_ctsG (TYPE_2__*) ; 
 int /*<<< orphan*/  gc_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gc_fullsweep (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gc_mark_start (TYPE_2__*) ; 
 int /*<<< orphan*/  gc_sweep (TYPE_2__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * gcref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_str_resize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lj_tab_rehash (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/ * mref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t propagatemark (TYPE_2__*) ; 
 int /*<<< orphan*/  setmref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t gc_onestep(lua_State *L)
{
  global_State *g = G(L);
  switch (g->gc.state) {
  case GCSpause:
    gc_mark_start(g);  /* Start a new GC cycle by marking all GC roots. */
    return 0;
  case GCSpropagate:
    if (gcref(g->gc.gray) != NULL)
      return propagatemark(g);  /* Propagate one gray object. */
    g->gc.state = GCSatomic;  /* End of mark phase. */
    return 0;
  case GCSatomic:
    if (tvref(g->jit_base))  /* Don't run atomic phase on trace. */
      return LJ_MAX_MEM;
    atomic(g, L);
    g->gc.state = GCSsweepstring;  /* Start of sweep phase. */
    g->gc.sweepstr = 0;
    return 0;
  case GCSsweepstring: {
    GCSize old = g->gc.total;
    gc_fullsweep(g, &g->strhash[g->gc.sweepstr++]);  /* Sweep one chain. */
    if (g->gc.sweepstr > g->strmask)
      g->gc.state = GCSsweep;  /* All string hash chains sweeped. */
    lua_assert(old >= g->gc.total);
    g->gc.estimate -= old - g->gc.total;
    return GCSWEEPCOST;
    }
  case GCSsweep: {
    GCSize old = g->gc.total;
    setmref(g->gc.sweep, gc_sweep(g, mref(g->gc.sweep, GCRef), GCSWEEPMAX));
    lua_assert(old >= g->gc.total);
    g->gc.estimate -= old - g->gc.total;
    if (gcref(*mref(g->gc.sweep, GCRef)) == NULL) {
      if (g->strnum <= (g->strmask >> 2) && g->strmask > LJ_MIN_STRTAB*2-1)
	lj_str_resize(L, g->strmask >> 1);  /* Shrink string table. */
      if (gcref(g->gc.mmudata)) {  /* Need any finalizations? */
	g->gc.state = GCSfinalize;
#if LJ_HASFFI
	g->gc.nocdatafin = 1;
#endif
      } else {  /* Otherwise skip this phase to help the JIT. */
	g->gc.state = GCSpause;  /* End of GC cycle. */
	g->gc.debt = 0;
      }
    }
    return GCSWEEPMAX*GCSWEEPCOST;
    }
  case GCSfinalize:
    if (gcref(g->gc.mmudata) != NULL) {
      if (tvref(g->jit_base))  /* Don't call finalizers on trace. */
	return LJ_MAX_MEM;
      gc_finalize(L);  /* Finalize one userdata object. */
      if (g->gc.estimate > GCFINALIZECOST)
	g->gc.estimate -= GCFINALIZECOST;
      return GCFINALIZECOST;
    }
#if LJ_HASFFI
    if (!g->gc.nocdatafin) lj_tab_rehash(L, ctype_ctsG(g)->finalizer);
#endif
    g->gc.state = GCSpause;  /* End of GC cycle. */
    g->gc.debt = 0;
    return 0;
  default:
    lua_assert(0);
    return 0;
  }
}