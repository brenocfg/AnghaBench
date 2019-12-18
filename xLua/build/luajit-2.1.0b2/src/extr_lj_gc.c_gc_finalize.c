#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_19__ ;
typedef  struct TYPE_22__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_24__ {scalar_t__ nocdatafin; int /*<<< orphan*/  root; int /*<<< orphan*/  mmudata; } ;
struct TYPE_26__ {TYPE_1__ gc; int /*<<< orphan*/  jit_base; } ;
typedef  TYPE_3__ global_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_28__ {int /*<<< orphan*/  nextgc; } ;
struct TYPE_25__ {int /*<<< orphan*/  nextgc; int /*<<< orphan*/  marked; int /*<<< orphan*/  gct; } ;
struct TYPE_27__ {TYPE_2__ gch; } ;
struct TYPE_23__ {int /*<<< orphan*/  finalizer; } ;
struct TYPE_22__ {int /*<<< orphan*/  metatable; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_4__ GCobj ;

/* Variables and functions */
 TYPE_3__* G (int /*<<< orphan*/ *) ; 
 scalar_t__ LJ_GC_CDATA_FIN ; 
 int /*<<< orphan*/  LJ_TCDATA ; 
 int /*<<< orphan*/  MM_gc ; 
 int /*<<< orphan*/  copyTV (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_19__* ctype_ctsG (TYPE_3__*) ; 
 int /*<<< orphan*/  gc_call_finalizer (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_4__* gcnext (TYPE_4__*) ; 
 int /*<<< orphan*/  gco2cd (TYPE_4__*) ; 
 TYPE_12__* gco2ud (TYPE_4__*) ; 
 TYPE_4__* gcref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_meta_fastg (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_tab_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 TYPE_8__* mainthread (TYPE_3__*) ; 
 int /*<<< orphan*/  makewhite (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  setcdataV (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  setgcrefnull (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setgcrefr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setnilV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tabref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvisnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tvref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gc_finalize(lua_State *L)
{
  global_State *g = G(L);
  GCobj *o = gcnext(gcref(g->gc.mmudata));
  cTValue *mo;
  lua_assert(tvref(g->jit_base) == NULL);  /* Must not be called on trace. */
  /* Unchain from list of userdata to be finalized. */
  if (o == gcref(g->gc.mmudata))
    setgcrefnull(g->gc.mmudata);
  else
    setgcrefr(gcref(g->gc.mmudata)->gch.nextgc, o->gch.nextgc);
#if LJ_HASFFI
  if (o->gch.gct == ~LJ_TCDATA) {
    TValue tmp, *tv;
    /* Add cdata back to the GC list and make it white. */
    setgcrefr(o->gch.nextgc, g->gc.root);
    setgcref(g->gc.root, o);
    makewhite(g, o);
    o->gch.marked &= (uint8_t)~LJ_GC_CDATA_FIN;
    /* Resolve finalizer. */
    setcdataV(L, &tmp, gco2cd(o));
    tv = lj_tab_set(L, ctype_ctsG(g)->finalizer, &tmp);
    if (!tvisnil(tv)) {
      g->gc.nocdatafin = 0;
      copyTV(L, &tmp, tv);
      setnilV(tv);  /* Clear entry in finalizer table. */
      gc_call_finalizer(g, L, &tmp, o);
    }
    return;
  }
#endif
  /* Add userdata back to the main userdata list and make it white. */
  setgcrefr(o->gch.nextgc, mainthread(g)->nextgc);
  setgcref(mainthread(g)->nextgc, o);
  makewhite(g, o);
  /* Resolve the __gc metamethod. */
  mo = lj_meta_fastg(g, tabref(gco2ud(o)->metatable), MM_gc);
  if (mo)
    gc_call_finalizer(g, L, mo, o);
}