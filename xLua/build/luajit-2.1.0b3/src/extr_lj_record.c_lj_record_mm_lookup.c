#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_18__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ jit_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_24__ {int /*<<< orphan*/  metatable; } ;
struct TYPE_23__ {int udtype; int /*<<< orphan*/  metatable; } ;
struct TYPE_22__ {void* tab; void* mt; int /*<<< orphan*/  mobj; scalar_t__ idxchain; scalar_t__ val; int /*<<< orphan*/  key; int /*<<< orphan*/  keyv; int /*<<< orphan*/  tabv; int /*<<< orphan*/ * mtv; int /*<<< orphan*/  mobjv; } ;
struct TYPE_20__ {int /*<<< orphan*/ * gcroot; } ;
typedef  void* TRef ;
typedef  TYPE_2__ RecordIndex ;
typedef  int /*<<< orphan*/  MMS ;
typedef  int /*<<< orphan*/  GCtab ;
typedef  int /*<<< orphan*/  GCstr ;

/* Variables and functions */
 size_t GCROOT_BASEMT ; 
 int /*<<< orphan*/  GG_OFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRFL_TAB_META ; 
 int /*<<< orphan*/  IRFL_UDATA_META ; 
 int /*<<< orphan*/  IRFL_UDATA_UDTYPE ; 
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTGI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRT_FUNC ; 
 int /*<<< orphan*/  IRT_PGC ; 
 int /*<<< orphan*/  IRT_TAB ; 
 int /*<<< orphan*/  IRT_U8 ; 
 int /*<<< orphan*/  IR_EQ ; 
 int /*<<< orphan*/  IR_FLOAD ; 
 int /*<<< orphan*/  IR_NE ; 
 int /*<<< orphan*/  J2G (TYPE_1__*) ; 
 scalar_t__ LJ_HASFFI ; 
 int /*<<< orphan*/  LJ_TRERR_BADTYPE ; 
 void* TREF_NIL ; 
 int UDTYPE_FFI_CLIB ; 
 int UDTYPE_USERDATA ; 
 int /*<<< orphan*/  basemt_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copyTV (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* emitir (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 TYPE_18__ g ; 
 int /*<<< orphan*/  gcV (int /*<<< orphan*/ *) ; 
 size_t itypemap (int /*<<< orphan*/ *) ; 
 void* lj_ir_ggfload (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kgc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kint (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lj_ir_knull (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kptr (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  lj_ir_kstr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 void* lj_ir_ktab (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_record_idx (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/ * lj_tab_getstr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mmname_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setstrV (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  settabV (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* tabV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tabref (int /*<<< orphan*/ ) ; 
 scalar_t__ tref_iscdata (void*) ; 
 int /*<<< orphan*/  tref_isnil (int /*<<< orphan*/ ) ; 
 scalar_t__ tref_istab (void*) ; 
 scalar_t__ tref_isudata (void*) ; 
 scalar_t__ tvisfunc (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnil (int /*<<< orphan*/ *) ; 
 scalar_t__ tvistab (int /*<<< orphan*/ *) ; 
 TYPE_3__* udataV (int /*<<< orphan*/ *) ; 

int lj_record_mm_lookup(jit_State *J, RecordIndex *ix, MMS mm)
{
  RecordIndex mix;
  GCtab *mt;
  if (tref_istab(ix->tab)) {
    mt = tabref(tabV(&ix->tabv)->metatable);
    mix.tab = emitir(IRT(IR_FLOAD, IRT_TAB), ix->tab, IRFL_TAB_META);
  } else if (tref_isudata(ix->tab)) {
    int udtype = udataV(&ix->tabv)->udtype;
    mt = tabref(udataV(&ix->tabv)->metatable);
    /* The metatables of special userdata objects are treated as immutable. */
    if (udtype != UDTYPE_USERDATA) {
      cTValue *mo;
      if (LJ_HASFFI && udtype == UDTYPE_FFI_CLIB) {
	/* Specialize to the C library namespace object. */
	emitir(IRTG(IR_EQ, IRT_PGC), ix->tab, lj_ir_kptr(J, udataV(&ix->tabv)));
      } else {
	/* Specialize to the type of userdata. */
	TRef tr = emitir(IRT(IR_FLOAD, IRT_U8), ix->tab, IRFL_UDATA_UDTYPE);
	emitir(IRTGI(IR_EQ), tr, lj_ir_kint(J, udtype));
      }
  immutable_mt:
      mo = lj_tab_getstr(mt, mmname_str(J2G(J), mm));
      if (!mo || tvisnil(mo))
	return 0;  /* No metamethod. */
      /* Treat metamethod or index table as immutable, too. */
      if (!(tvisfunc(mo) || tvistab(mo)))
	lj_trace_err(J, LJ_TRERR_BADTYPE);
      copyTV(J->L, &ix->mobjv, mo);
      ix->mobj = lj_ir_kgc(J, gcV(mo), tvisfunc(mo) ? IRT_FUNC : IRT_TAB);
      ix->mtv = mt;
      ix->mt = TREF_NIL;  /* Dummy value for comparison semantics. */
      return 1;  /* Got metamethod or index table. */
    }
    mix.tab = emitir(IRT(IR_FLOAD, IRT_TAB), ix->tab, IRFL_UDATA_META);
  } else {
    /* Specialize to base metatable. Must flush mcode in lua_setmetatable(). */
    mt = tabref(basemt_obj(J2G(J), &ix->tabv));
    if (mt == NULL) {
      ix->mt = TREF_NIL;
      return 0;  /* No metamethod. */
    }
    /* The cdata metatable is treated as immutable. */
    if (LJ_HASFFI && tref_iscdata(ix->tab)) goto immutable_mt;
#if LJ_GC64
    /* TODO: fix ARM32 asm_fload(), so we can use this for all archs. */
    ix->mt = mix.tab = lj_ir_ggfload(J, IRT_TAB,
      GG_OFS(g.gcroot[GCROOT_BASEMT+itypemap(&ix->tabv)]));
#else
    ix->mt = mix.tab = lj_ir_ktab(J, mt);
#endif
    goto nocheck;
  }
  ix->mt = mt ? mix.tab : TREF_NIL;
  emitir(IRTG(mt ? IR_NE : IR_EQ, IRT_TAB), mix.tab, lj_ir_knull(J, IRT_TAB));
nocheck:
  if (mt) {
    GCstr *mmstr = mmname_str(J2G(J), mm);
    cTValue *mo = lj_tab_getstr(mt, mmstr);
    if (mo && !tvisnil(mo))
      copyTV(J->L, &ix->mobjv, mo);
    ix->mtv = mt;
    settabV(J->L, &mix.tabv, mt);
    setstrV(J->L, &mix.keyv, mmstr);
    mix.key = lj_ir_kstr(J, mmstr);
    mix.val = 0;
    mix.idxchain = 0;
    ix->mobj = lj_record_idx(J, &mix);
    return !tref_isnil(ix->mobj);  /* 1 if metamethod found, 0 if not. */
  }
  return 0;  /* No metamethod. */
}