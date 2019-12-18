#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  postproc; } ;
typedef  TYPE_1__ jit_State ;
struct TYPE_11__ {scalar_t__ i; } ;
struct TYPE_10__ {int info; int size; } ;
typedef  scalar_t__ TRef ;
typedef  int MSize ;
typedef  scalar_t__ MMS ;
typedef  scalar_t__ IRType ;
typedef  scalar_t__ IROp ;
typedef  int /*<<< orphan*/  CTypeID ;
typedef  TYPE_2__ CType ;

/* Variables and functions */
 int CTF_FP ; 
 int CTF_UNSIGNED ; 
 int /*<<< orphan*/  CTID_INT64 ; 
 int /*<<< orphan*/  CTID_UINT64 ; 
 TYPE_8__* IR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRCONV_ANY ; 
 int /*<<< orphan*/  IRCONV_SEXT ; 
 int /*<<< orphan*/  IRT (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  IRTG (scalar_t__,scalar_t__) ; 
 scalar_t__ IRT_CDATA ; 
 scalar_t__ IRT_FLOAT ; 
 scalar_t__ IRT_I64 ; 
 scalar_t__ IRT_INT ; 
 scalar_t__ IRT_NUM ; 
 scalar_t__ IRT_U32 ; 
 scalar_t__ IRT_U64 ; 
 scalar_t__ IR_ADD ; 
 scalar_t__ IR_CNEWI ; 
 scalar_t__ IR_EQ ; 
 scalar_t__ IR_LE ; 
 scalar_t__ IR_LT ; 
 scalar_t__ IR_ULT ; 
 int /*<<< orphan*/  LJ_POST_FIXGUARD ; 
 scalar_t__ MM_add ; 
 scalar_t__ MM_eq ; 
 scalar_t__ MM_lt ; 
 scalar_t__ TREF_TRUE ; 
 scalar_t__ ctype_isnum (int) ; 
 scalar_t__ emitconv (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ emitir (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ lj_ir_kint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_set (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lj_needsplit (TYPE_1__*) ; 
 scalar_t__ tref_isk (scalar_t__) ; 
 int /*<<< orphan*/  tref_ref (scalar_t__) ; 
 scalar_t__ tref_type (scalar_t__) ; 

__attribute__((used)) static TRef crec_arith_int64(jit_State *J, TRef *sp, CType **s, MMS mm)
{
  if (sp[0] && sp[1] && ctype_isnum(s[0]->info) && ctype_isnum(s[1]->info)) {
    IRType dt;
    CTypeID id;
    TRef tr;
    MSize i;
    IROp op;
    lj_needsplit(J);
    if (((s[0]->info & CTF_UNSIGNED) && s[0]->size == 8) ||
	((s[1]->info & CTF_UNSIGNED) && s[1]->size == 8)) {
      dt = IRT_U64; id = CTID_UINT64;
    } else {
      dt = IRT_I64; id = CTID_INT64;
      if (mm < MM_add &&
	  !((s[0]->info | s[1]->info) & CTF_FP) &&
	  s[0]->size == 4 && s[1]->size == 4) {  /* Try to narrow comparison. */
	if (!((s[0]->info ^ s[1]->info) & CTF_UNSIGNED) ||
	    (tref_isk(sp[1]) && IR(tref_ref(sp[1]))->i >= 0)) {
	  dt = (s[0]->info & CTF_UNSIGNED) ? IRT_U32 : IRT_INT;
	  goto comp;
	} else if (tref_isk(sp[0]) && IR(tref_ref(sp[0]))->i >= 0) {
	  dt = (s[1]->info & CTF_UNSIGNED) ? IRT_U32 : IRT_INT;
	  goto comp;
	}
      }
    }
    for (i = 0; i < 2; i++) {
      IRType st = tref_type(sp[i]);
      if (st == IRT_NUM || st == IRT_FLOAT)
	sp[i] = emitconv(sp[i], dt, st, IRCONV_ANY);
      else if (!(st == IRT_I64 || st == IRT_U64))
	sp[i] = emitconv(sp[i], dt, IRT_INT,
			 (s[i]->info & CTF_UNSIGNED) ? 0 : IRCONV_SEXT);
    }
    if (mm < MM_add) {
    comp:
      /* Assume true comparison. Fixup and emit pending guard later. */
      if (mm == MM_eq) {
	op = IR_EQ;
      } else {
	op = mm == MM_lt ? IR_LT : IR_LE;
	if (dt == IRT_U32 || dt == IRT_U64)
	  op += (IR_ULT-IR_LT);
      }
      lj_ir_set(J, IRTG(op, dt), sp[0], sp[1]);
      J->postproc = LJ_POST_FIXGUARD;
      return TREF_TRUE;
    } else {
      tr = emitir(IRT(mm+(int)IR_ADD-(int)MM_add, dt), sp[0], sp[1]);
    }
    return emitir(IRTG(IR_CNEWI, IRT_CDATA), lj_ir_kint(J, id), tr);
  }
  return 0;
}