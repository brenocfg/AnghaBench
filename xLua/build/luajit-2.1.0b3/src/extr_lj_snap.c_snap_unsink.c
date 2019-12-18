#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_31__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_36__ {int /*<<< orphan*/  L; } ;
typedef  TYPE_3__ jit_State ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_40__ {int /*<<< orphan*/  metatable; } ;
struct TYPE_39__ {int nins; TYPE_5__* ir; TYPE_2__* snap; } ;
struct TYPE_38__ {scalar_t__ o; size_t op1; size_t op2; scalar_t__ r; int /*<<< orphan*/  i; int /*<<< orphan*/  t; } ;
struct TYPE_33__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct TYPE_37__ {TYPE_1__ u32; } ;
struct TYPE_35__ {scalar_t__ u64; } ;
struct TYPE_34__ {size_t ref; } ;
typedef  TYPE_4__ TValue ;
typedef  size_t SnapNo ;
typedef  TYPE_5__ IRIns ;
typedef  TYPE_6__ GCtrace ;
typedef  TYPE_7__ GCtab ;
typedef  int /*<<< orphan*/  GCcdata ;
typedef  int /*<<< orphan*/  ExitState ;
typedef  int /*<<< orphan*/  CTypeID ;
typedef  int /*<<< orphan*/  CTState ;
typedef  int CTSize ;
typedef  int /*<<< orphan*/  CTInfo ;
typedef  int /*<<< orphan*/  BloomFilter ;

/* Variables and functions */
 size_t IRFL_TAB_META ; 
 scalar_t__ IR_ADD ; 
 scalar_t__ IR_ASTORE ; 
 scalar_t__ IR_CNEW ; 
 scalar_t__ IR_CNEWI ; 
 scalar_t__ IR_FREF ; 
 scalar_t__ IR_FSTORE ; 
 scalar_t__ IR_HIOP ; 
 scalar_t__ IR_HSTORE ; 
 scalar_t__ IR_KINT ; 
 scalar_t__ IR_KINT64 ; 
 scalar_t__ IR_KSLOT ; 
 scalar_t__ IR_TDUP ; 
 scalar_t__ IR_TNEW ; 
 scalar_t__ IR_XSTORE ; 
 scalar_t__ LJ_32 ; 
 scalar_t__ LJ_64 ; 
 scalar_t__ LJ_BE ; 
 scalar_t__ LJ_LE ; 
 scalar_t__ LJ_SOFTFP ; 
 scalar_t__ RID_SINK ; 
 scalar_t__ cdataptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ctype_cts (int /*<<< orphan*/ ) ; 
 TYPE_31__* ir_k64 (TYPE_5__*) ; 
 int /*<<< orphan*/  ir_ktab (TYPE_5__*) ; 
 scalar_t__ irt_is64 (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isi16 (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isi8 (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isu16 (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isu8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_cdata_newx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ctype_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lj_ir_kvalue (int /*<<< orphan*/ ,TYPE_4__*,TYPE_5__*) ; 
 TYPE_7__* lj_tab_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* lj_tab_new (int /*<<< orphan*/ ,size_t,size_t) ; 
 TYPE_4__* lj_tab_set (int /*<<< orphan*/ ,TYPE_7__*,TYPE_4__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  obj2gco (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setcdataV (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  settabV (int /*<<< orphan*/ ,TYPE_4__*,TYPE_7__*) ; 
 int /*<<< orphan*/  snap_restoredata (TYPE_6__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snap_restoreval (TYPE_3__*,TYPE_6__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,size_t,TYPE_4__*) ; 
 scalar_t__ snap_sunk_store (TYPE_6__*,TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  tabV (TYPE_4__*) ; 

__attribute__((used)) static void snap_unsink(jit_State *J, GCtrace *T, ExitState *ex,
			SnapNo snapno, BloomFilter rfilt,
			IRIns *ir, TValue *o)
{
  lua_assert(ir->o == IR_TNEW || ir->o == IR_TDUP ||
	     ir->o == IR_CNEW || ir->o == IR_CNEWI);
#if LJ_HASFFI
  if (ir->o == IR_CNEW || ir->o == IR_CNEWI) {
    CTState *cts = ctype_cts(J->L);
    CTypeID id = (CTypeID)T->ir[ir->op1].i;
    CTSize sz;
    CTInfo info = lj_ctype_info(cts, id, &sz);
    GCcdata *cd = lj_cdata_newx(cts, id, sz, info);
    setcdataV(J->L, o, cd);
    if (ir->o == IR_CNEWI) {
      uint8_t *p = (uint8_t *)cdataptr(cd);
      lua_assert(sz == 4 || sz == 8);
      if (LJ_32 && sz == 8 && ir+1 < T->ir + T->nins && (ir+1)->o == IR_HIOP) {
	snap_restoredata(T, ex, snapno, rfilt, (ir+1)->op2, LJ_LE?p+4:p, 4);
	if (LJ_BE) p += 4;
	sz = 4;
      }
      snap_restoredata(T, ex, snapno, rfilt, ir->op2, p, sz);
    } else {
      IRIns *irs, *irlast = &T->ir[T->snap[snapno].ref];
      for (irs = ir+1; irs < irlast; irs++)
	if (irs->r == RID_SINK && snap_sunk_store(T, ir, irs)) {
	  IRIns *iro = &T->ir[T->ir[irs->op1].op2];
	  uint8_t *p = (uint8_t *)cd;
	  CTSize szs;
	  lua_assert(irs->o == IR_XSTORE && T->ir[irs->op1].o == IR_ADD);
	  lua_assert(iro->o == IR_KINT || iro->o == IR_KINT64);
	  if (irt_is64(irs->t)) szs = 8;
	  else if (irt_isi8(irs->t) || irt_isu8(irs->t)) szs = 1;
	  else if (irt_isi16(irs->t) || irt_isu16(irs->t)) szs = 2;
	  else szs = 4;
	  if (LJ_64 && iro->o == IR_KINT64)
	    p += (int64_t)ir_k64(iro)->u64;
	  else
	    p += iro->i;
	  lua_assert(p >= (uint8_t *)cdataptr(cd) &&
		     p + szs <= (uint8_t *)cdataptr(cd) + sz);
	  if (LJ_32 && irs+1 < T->ir + T->nins && (irs+1)->o == IR_HIOP) {
	    lua_assert(szs == 4);
	    snap_restoredata(T, ex, snapno, rfilt, (irs+1)->op2, LJ_LE?p+4:p,4);
	    if (LJ_BE) p += 4;
	  }
	  snap_restoredata(T, ex, snapno, rfilt, irs->op2, p, szs);
	}
    }
  } else
#endif
  {
    IRIns *irs, *irlast;
    GCtab *t = ir->o == IR_TNEW ? lj_tab_new(J->L, ir->op1, ir->op2) :
				  lj_tab_dup(J->L, ir_ktab(&T->ir[ir->op1]));
    settabV(J->L, o, t);
    irlast = &T->ir[T->snap[snapno].ref];
    for (irs = ir+1; irs < irlast; irs++)
      if (irs->r == RID_SINK && snap_sunk_store(T, ir, irs)) {
	IRIns *irk = &T->ir[irs->op1];
	TValue tmp, *val;
	lua_assert(irs->o == IR_ASTORE || irs->o == IR_HSTORE ||
		   irs->o == IR_FSTORE);
	if (irk->o == IR_FREF) {
	  lua_assert(irk->op2 == IRFL_TAB_META);
	  snap_restoreval(J, T, ex, snapno, rfilt, irs->op2, &tmp);
	  /* NOBARRIER: The table is new (marked white). */
	  setgcref(t->metatable, obj2gco(tabV(&tmp)));
	} else {
	  irk = &T->ir[irk->op2];
	  if (irk->o == IR_KSLOT) irk = &T->ir[irk->op1];
	  lj_ir_kvalue(J->L, &tmp, irk);
	  val = lj_tab_set(J->L, t, &tmp);
	  /* NOBARRIER: The table is new (marked white). */
	  snap_restoreval(J, T, ex, snapno, rfilt, irs->op2, val);
	  if (LJ_SOFTFP && irs+1 < T->ir + T->nins && (irs+1)->o == IR_HIOP) {
	    snap_restoreval(J, T, ex, snapno, rfilt, (irs+1)->op2, &tmp);
	    val->u32.hi = tmp.u32.lo;
	  }
	}
      }
  }
}