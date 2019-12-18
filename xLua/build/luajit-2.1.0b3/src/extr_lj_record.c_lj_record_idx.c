#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_22__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {scalar_t__* base; int flags; int needsnap; void* guardemit; TYPE_4__* L; } ;
typedef  TYPE_1__ jit_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_30__ {int /*<<< orphan*/ * base; } ;
struct TYPE_29__ {int /*<<< orphan*/  metatable; } ;
struct TYPE_28__ {scalar_t__ tab; scalar_t__ idxchain; scalar_t__ val; scalar_t__ mobj; scalar_t__ key; int /*<<< orphan*/  tabv; int /*<<< orphan*/ * oldv; int /*<<< orphan*/  keyv; int /*<<< orphan*/  mobjv; int /*<<< orphan*/  valv; } ;
struct TYPE_27__ {scalar_t__ o; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  scalar_t__ TRef ;
typedef  TYPE_2__ RecordIndex ;
typedef  void* IRType1 ;
typedef  scalar_t__ IRType ;
typedef  scalar_t__ IRRef ;
typedef  scalar_t__ IROp ;
typedef  int /*<<< orphan*/  GCtab ;
typedef  int BCReg ;

/* Variables and functions */
 TYPE_22__* IR (scalar_t__) ; 
 scalar_t__ IRCONV_NUM_INT ; 
 scalar_t__ IRDELTA_L2S ; 
 scalar_t__ IRFL_TAB_META ; 
 scalar_t__ IRFL_TAB_NOMM ; 
 int /*<<< orphan*/  IRT (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  IRTG (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  IRTN (int /*<<< orphan*/ ) ; 
 scalar_t__ IRT_NIL ; 
 scalar_t__ IRT_PGC ; 
 scalar_t__ IRT_TAB ; 
 scalar_t__ IRT_U8 ; 
 scalar_t__ IR_ALOAD ; 
 scalar_t__ IR_AREF ; 
 int /*<<< orphan*/  IR_CONV ; 
 scalar_t__ IR_EQ ; 
 scalar_t__ IR_FLOAD ; 
 scalar_t__ IR_FREF ; 
 scalar_t__ IR_FSTORE ; 
 scalar_t__ IR_HLOAD ; 
 scalar_t__ IR_HREF ; 
 scalar_t__ IR_KKPTR ; 
 scalar_t__ IR_NE ; 
 scalar_t__ IR_NEWREF ; 
 scalar_t__ IR_TBAR ; 
 int /*<<< orphan*/  J2G (TYPE_1__*) ; 
 int JIT_F_OPT_SINK ; 
 int /*<<< orphan*/  LJ_DUALNUM ; 
 int LJ_FR2 ; 
 int /*<<< orphan*/  LJ_TRERR_IDXLOOP ; 
 int /*<<< orphan*/  LJ_TRERR_NOMM ; 
 int /*<<< orphan*/  LJ_TRERR_STORENN ; 
 int /*<<< orphan*/  MM_index ; 
 int /*<<< orphan*/  MM_newindex ; 
 scalar_t__ TREF_NIL ; 
 scalar_t__ TREF_PRI (scalar_t__) ; 
 int /*<<< orphan*/  copyTV (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* emitir (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  funcV (int /*<<< orphan*/ *) ; 
 scalar_t__ ir_kptr (TYPE_22__*) ; 
 scalar_t__ irtype_ispri (scalar_t__) ; 
 scalar_t__ itype2irt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_cont_nop ; 
 int /*<<< orphan*/  lj_cont_ra ; 
 scalar_t__ lj_ir_kint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lj_ir_kkptr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ lj_ir_knull (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  lj_ir_rollback (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  lj_opt_fwd_wasnonnil (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lj_record_call (TYPE_1__*,int,int) ; 
 scalar_t__ lj_record_mm_lookup (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_tab_getstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  mmname_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * niltvg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nommstr (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  rec_idx_bump (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ rec_idx_key (TYPE_1__*,TYPE_2__*,scalar_t__*,void**) ; 
 int rec_mm_prep (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setfuncV (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* tabV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tabref (int /*<<< orphan*/ ) ; 
 scalar_t__ tref_isfunc (scalar_t__) ; 
 scalar_t__ tref_isgcv (scalar_t__) ; 
 scalar_t__ tref_isinteger (scalar_t__) ; 
 scalar_t__ tref_isk (scalar_t__) ; 
 int /*<<< orphan*/  tref_isnil (scalar_t__) ; 
 int /*<<< orphan*/  tref_istab (scalar_t__) ; 
 scalar_t__ tref_ref (scalar_t__) ; 
 scalar_t__ tref_type (scalar_t__) ; 
 scalar_t__ tvisnan (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnil (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnum (int /*<<< orphan*/ *) ; 

TRef lj_record_idx(jit_State *J, RecordIndex *ix)
{
  TRef xref;
  IROp xrefop, loadop;
  IRRef rbref;
  IRType1 rbguard;
  cTValue *oldv;

  while (!tref_istab(ix->tab)) { /* Handle non-table lookup. */
    /* Never call raw lj_record_idx() on non-table. */
    lua_assert(ix->idxchain != 0);
    if (!lj_record_mm_lookup(J, ix, ix->val ? MM_newindex : MM_index))
      lj_trace_err(J, LJ_TRERR_NOMM);
  handlemm:
    if (tref_isfunc(ix->mobj)) {  /* Handle metamethod call. */
      BCReg func = rec_mm_prep(J, ix->val ? lj_cont_nop : lj_cont_ra);
      TRef *base = J->base + func + LJ_FR2;
      TValue *tv = J->L->base + func + LJ_FR2;
      base[-LJ_FR2] = ix->mobj; base[1] = ix->tab; base[2] = ix->key;
      setfuncV(J->L, tv-LJ_FR2, funcV(&ix->mobjv));
      copyTV(J->L, tv+1, &ix->tabv);
      copyTV(J->L, tv+2, &ix->keyv);
      if (ix->val) {
	base[3] = ix->val;
	copyTV(J->L, tv+3, &ix->valv);
	lj_record_call(J, func, 3);  /* mobj(tab, key, val) */
	return 0;
      } else {
	lj_record_call(J, func, 2);  /* res = mobj(tab, key) */
	return 0;  /* No result yet. */
      }
    }
    /* Otherwise retry lookup with metaobject. */
    ix->tab = ix->mobj;
    copyTV(J->L, &ix->tabv, &ix->mobjv);
    if (--ix->idxchain == 0)
      lj_trace_err(J, LJ_TRERR_IDXLOOP);
  }

  /* First catch nil and NaN keys for tables. */
  if (tvisnil(&ix->keyv) || (tvisnum(&ix->keyv) && tvisnan(&ix->keyv))) {
    if (ix->val)  /* Better fail early. */
      lj_trace_err(J, LJ_TRERR_STORENN);
    if (tref_isk(ix->key)) {
      if (ix->idxchain && lj_record_mm_lookup(J, ix, MM_index))
	goto handlemm;
      return TREF_NIL;
    }
  }

  /* Record the key lookup. */
  xref = rec_idx_key(J, ix, &rbref, &rbguard);
  xrefop = IR(tref_ref(xref))->o;
  loadop = xrefop == IR_AREF ? IR_ALOAD : IR_HLOAD;
  /* The lj_meta_tset() inconsistency is gone, but better play safe. */
  oldv = xrefop == IR_KKPTR ? (cTValue *)ir_kptr(IR(tref_ref(xref))) : ix->oldv;

  if (ix->val == 0) {  /* Indexed load */
    IRType t = itype2irt(oldv);
    TRef res;
    if (oldv == niltvg(J2G(J))) {
      emitir(IRTG(IR_EQ, IRT_PGC), xref, lj_ir_kkptr(J, niltvg(J2G(J))));
      res = TREF_NIL;
    } else {
      res = emitir(IRTG(loadop, t), xref, 0);
    }
    if (tref_ref(res) < rbref) {  /* HREFK + load forwarded? */
      lj_ir_rollback(J, rbref);  /* Rollback to eliminate hmask guard. */
      J->guardemit = rbguard;
    }
    if (t == IRT_NIL && ix->idxchain && lj_record_mm_lookup(J, ix, MM_index))
      goto handlemm;
    if (irtype_ispri(t)) res = TREF_PRI(t);  /* Canonicalize primitives. */
    return res;
  } else {  /* Indexed store. */
    GCtab *mt = tabref(tabV(&ix->tabv)->metatable);
    int keybarrier = tref_isgcv(ix->key) && !tref_isnil(ix->val);
    if (tref_ref(xref) < rbref) {  /* HREFK forwarded? */
      lj_ir_rollback(J, rbref);  /* Rollback to eliminate hmask guard. */
      J->guardemit = rbguard;
    }
    if (tvisnil(oldv)) {  /* Previous value was nil? */
      /* Need to duplicate the hasmm check for the early guards. */
      int hasmm = 0;
      if (ix->idxchain && mt) {
	cTValue *mo = lj_tab_getstr(mt, mmname_str(J2G(J), MM_newindex));
	hasmm = mo && !tvisnil(mo);
      }
      if (hasmm)
	emitir(IRTG(loadop, IRT_NIL), xref, 0);  /* Guard for nil value. */
      else if (xrefop == IR_HREF)
	emitir(IRTG(oldv == niltvg(J2G(J)) ? IR_EQ : IR_NE, IRT_PGC),
	       xref, lj_ir_kkptr(J, niltvg(J2G(J))));
      if (ix->idxchain && lj_record_mm_lookup(J, ix, MM_newindex)) {
	lua_assert(hasmm);
	goto handlemm;
      }
      lua_assert(!hasmm);
      if (oldv == niltvg(J2G(J))) {  /* Need to insert a new key. */
	TRef key = ix->key;
	if (tref_isinteger(key))  /* NEWREF needs a TValue as a key. */
	  key = emitir(IRTN(IR_CONV), key, IRCONV_NUM_INT);
	xref = emitir(IRT(IR_NEWREF, IRT_PGC), ix->tab, key);
	keybarrier = 0;  /* NEWREF already takes care of the key barrier. */
#ifdef LUAJIT_ENABLE_TABLE_BUMP
	if ((J->flags & JIT_F_OPT_SINK))  /* Avoid a separate flag. */
	  rec_idx_bump(J, ix);
#endif
      }
    } else if (!lj_opt_fwd_wasnonnil(J, loadop, tref_ref(xref))) {
      /* Cannot derive that the previous value was non-nil, must do checks. */
      if (xrefop == IR_HREF)  /* Guard against store to niltv. */
	emitir(IRTG(IR_NE, IRT_PGC), xref, lj_ir_kkptr(J, niltvg(J2G(J))));
      if (ix->idxchain) {  /* Metamethod lookup required? */
	/* A check for NULL metatable is cheaper (hoistable) than a load. */
	if (!mt) {
	  TRef mtref = emitir(IRT(IR_FLOAD, IRT_TAB), ix->tab, IRFL_TAB_META);
	  emitir(IRTG(IR_EQ, IRT_TAB), mtref, lj_ir_knull(J, IRT_TAB));
	} else {
	  IRType t = itype2irt(oldv);
	  emitir(IRTG(loadop, t), xref, 0);  /* Guard for non-nil value. */
	}
      }
    } else {
      keybarrier = 0;  /* Previous non-nil value kept the key alive. */
    }
    /* Convert int to number before storing. */
    if (!LJ_DUALNUM && tref_isinteger(ix->val))
      ix->val = emitir(IRTN(IR_CONV), ix->val, IRCONV_NUM_INT);
    emitir(IRT(loadop+IRDELTA_L2S, tref_type(ix->val)), xref, ix->val);
    if (keybarrier || tref_isgcv(ix->val))
      emitir(IRT(IR_TBAR, IRT_NIL), ix->tab, 0);
    /* Invalidate neg. metamethod cache for stores with certain string keys. */
    if (!nommstr(J, ix->key)) {
      TRef fref = emitir(IRT(IR_FREF, IRT_PGC), ix->tab, IRFL_TAB_NOMM);
      emitir(IRT(IR_FSTORE, IRT_U8), fref, lj_ir_kint(J, 0));
    }
    J->needsnap = 1;
    return 0;
  }
}