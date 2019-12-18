#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ lua_Number ;
struct TYPE_24__ {scalar_t__ irt; } ;
struct TYPE_21__ {scalar_t__ nins; } ;
struct TYPE_22__ {TYPE_4__ guardemit; TYPE_1__ cur; int /*<<< orphan*/  L; } ;
typedef  TYPE_2__ jit_State ;
typedef  scalar_t__ int32_t ;
struct TYPE_25__ {scalar_t__ asize; scalar_t__ hmask; int /*<<< orphan*/  node; } ;
struct TYPE_23__ {int /*<<< orphan*/  tab; scalar_t__ oldv; int /*<<< orphan*/  keyv; int /*<<< orphan*/  key; int /*<<< orphan*/  tabv; } ;
struct TYPE_20__ {int /*<<< orphan*/  val; } ;
typedef  int /*<<< orphan*/  TRef ;
typedef  TYPE_3__ RecordIndex ;
typedef  int /*<<< orphan*/  Node ;
typedef  scalar_t__ MSize ;
typedef  TYPE_4__ IRType1 ;
typedef  scalar_t__ IRRef ;
typedef  TYPE_5__ GCtab ;

/* Variables and functions */
 int /*<<< orphan*/  IRCONV_NUM_INT ; 
 int /*<<< orphan*/  IRFL_TAB_ARRAY ; 
 int /*<<< orphan*/  IRFL_TAB_ASIZE ; 
 int /*<<< orphan*/  IRFL_TAB_HMASK ; 
 int /*<<< orphan*/  IRFL_TAB_NODE ; 
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTGI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRT_P32 ; 
 int /*<<< orphan*/  IR_AREF ; 
 int /*<<< orphan*/  IR_CONV ; 
 int /*<<< orphan*/  IR_EQ ; 
 int /*<<< orphan*/  IR_FLOAD ; 
 int /*<<< orphan*/  IR_HREF ; 
 int /*<<< orphan*/  IR_HREFK ; 
 int /*<<< orphan*/  IR_ULE ; 
 int /*<<< orphan*/  J2G (TYPE_2__*) ; 
 scalar_t__ LJ_MAX_ASIZE ; 
 int /*<<< orphan*/  LJ_TRERR_NYITMIX ; 
 int /*<<< orphan*/  emitir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kint (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  lj_ir_kkptr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_knum_zero (TYPE_2__*) ; 
 int /*<<< orphan*/  lj_ir_kslot (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lj_opt_narrow_index (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lj_tab_get (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  niltvg (int /*<<< orphan*/ ) ; 
 TYPE_11__* noderef (int /*<<< orphan*/ ) ; 
 scalar_t__ numV (int /*<<< orphan*/ *) ; 
 scalar_t__ numberVint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rec_idx_abc (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_5__* tabV (int /*<<< orphan*/ *) ; 
 scalar_t__ tref_isinteger (int /*<<< orphan*/ ) ; 
 scalar_t__ tref_isk (int /*<<< orphan*/ ) ; 
 scalar_t__ tref_isnumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvisint (int /*<<< orphan*/ *) ; 

__attribute__((used)) static TRef rec_idx_key(jit_State *J, RecordIndex *ix, IRRef *rbref,
			IRType1 *rbguard)
{
  TRef key;
  GCtab *t = tabV(&ix->tabv);
  ix->oldv = lj_tab_get(J->L, t, &ix->keyv);  /* Lookup previous value. */
  *rbref = 0;
  rbguard->irt = 0;

  /* Integer keys are looked up in the array part first. */
  key = ix->key;
  if (tref_isnumber(key)) {
    int32_t k = numberVint(&ix->keyv);
    if (!tvisint(&ix->keyv) && numV(&ix->keyv) != (lua_Number)k)
      k = LJ_MAX_ASIZE;
    if ((MSize)k < LJ_MAX_ASIZE) {  /* Potential array key? */
      TRef ikey = lj_opt_narrow_index(J, key);
      TRef asizeref = emitir(IRTI(IR_FLOAD), ix->tab, IRFL_TAB_ASIZE);
      if ((MSize)k < t->asize) {  /* Currently an array key? */
	TRef arrayref;
	rec_idx_abc(J, asizeref, ikey, t->asize);
	arrayref = emitir(IRT(IR_FLOAD, IRT_P32), ix->tab, IRFL_TAB_ARRAY);
	return emitir(IRT(IR_AREF, IRT_P32), arrayref, ikey);
      } else {  /* Currently not in array (may be an array extension)? */
	emitir(IRTGI(IR_ULE), asizeref, ikey);  /* Inv. bounds check. */
	if (k == 0 && tref_isk(key))
	  key = lj_ir_knum_zero(J);  /* Canonicalize 0 or +-0.0 to +0.0. */
	/* And continue with the hash lookup. */
      }
    } else if (!tref_isk(key)) {
      /* We can rule out const numbers which failed the integerness test
      ** above. But all other numbers are potential array keys.
      */
      if (t->asize == 0) {  /* True sparse tables have an empty array part. */
	/* Guard that the array part stays empty. */
	TRef tmp = emitir(IRTI(IR_FLOAD), ix->tab, IRFL_TAB_ASIZE);
	emitir(IRTGI(IR_EQ), tmp, lj_ir_kint(J, 0));
      } else {
	lj_trace_err(J, LJ_TRERR_NYITMIX);
      }
    }
  }

  /* Otherwise the key is located in the hash part. */
  if (t->hmask == 0) {  /* Shortcut for empty hash part. */
    /* Guard that the hash part stays empty. */
    TRef tmp = emitir(IRTI(IR_FLOAD), ix->tab, IRFL_TAB_HMASK);
    emitir(IRTGI(IR_EQ), tmp, lj_ir_kint(J, 0));
    return lj_ir_kkptr(J, niltvg(J2G(J)));
  }
  if (tref_isinteger(key))  /* Hash keys are based on numbers, not ints. */
    key = emitir(IRTN(IR_CONV), key, IRCONV_NUM_INT);
  if (tref_isk(key)) {
    /* Optimize lookup of constant hash keys. */
    MSize hslot = (MSize)((char *)ix->oldv - (char *)&noderef(t->node)[0].val);
    if (t->hmask > 0 && hslot <= t->hmask*(MSize)sizeof(Node) &&
	hslot <= 65535*(MSize)sizeof(Node)) {
      TRef node, kslot, hm;
      *rbref = J->cur.nins;  /* Mark possible rollback point. */
      *rbguard = J->guardemit;
      hm = emitir(IRTI(IR_FLOAD), ix->tab, IRFL_TAB_HMASK);
      emitir(IRTGI(IR_EQ), hm, lj_ir_kint(J, (int32_t)t->hmask));
      node = emitir(IRT(IR_FLOAD, IRT_P32), ix->tab, IRFL_TAB_NODE);
      kslot = lj_ir_kslot(J, key, hslot / sizeof(Node));
      return emitir(IRTG(IR_HREFK, IRT_P32), node, kslot);
    }
  }
  /* Fall back to a regular hash lookup. */
  return emitir(IRT(IR_HREF, IRT_P32), ix->tab, key);
}