#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int ptrdiff_t ;
struct TYPE_16__ {int /*<<< orphan*/  L; int /*<<< orphan*/  postproc; } ;
typedef  TYPE_1__ jit_State ;
struct TYPE_18__ {int /*<<< orphan*/  L; } ;
struct TYPE_17__ {int info; int size; } ;
typedef  int /*<<< orphan*/  TRef ;
typedef  scalar_t__ IRType ;
typedef  int /*<<< orphan*/  GCcdata ;
typedef  int /*<<< orphan*/  CTypeID ;
typedef  TYPE_2__ CType ;
typedef  TYPE_3__ CTState ;
typedef  int CTInfo ;

/* Variables and functions */
 int CTF_BOOL ; 
 int /*<<< orphan*/  CTINFO_REF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTSIZE_PTR ; 
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IRTG (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IRTGI (int /*<<< orphan*/ ) ; 
 scalar_t__ IRT_CDATA ; 
 scalar_t__ IRT_FLOAT ; 
 scalar_t__ IRT_I64 ; 
 int /*<<< orphan*/  IRT_NUM ; 
 scalar_t__ IRT_PTR ; 
 scalar_t__ IRT_U32 ; 
 scalar_t__ IRT_U64 ; 
 int /*<<< orphan*/  IR_ADD ; 
 int /*<<< orphan*/  IR_CNEW ; 
 int /*<<< orphan*/  IR_CNEWI ; 
 int /*<<< orphan*/  IR_NE ; 
 int /*<<< orphan*/  IR_XLOAD ; 
 int /*<<< orphan*/  IR_XSTORE ; 
 int /*<<< orphan*/  J2G (TYPE_1__*) ; 
 int /*<<< orphan*/  LJ_POST_FIXGUARD ; 
 int /*<<< orphan*/  LJ_TRERR_NYICONV ; 
 int /*<<< orphan*/  TREF_NIL ; 
 int /*<<< orphan*/  TREF_TRUE ; 
 scalar_t__ crec_ct2irt (TYPE_3__*,TYPE_2__*) ; 
 TYPE_3__* ctype_ctsG (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_iscomplex (int) ; 
 scalar_t__ ctype_isenum (int) ; 
 scalar_t__ ctype_isnum (int) ; 
 scalar_t__ ctype_isptr (int) ; 
 scalar_t__ ctype_isrefarray (int) ; 
 scalar_t__ ctype_isstruct (int) ; 
 int /*<<< orphan*/  emitconv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ctype_intern (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kintp (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lj_ir_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_needsplit (TYPE_1__*) ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TRef crec_tv_ct(jit_State *J, CType *s, CTypeID sid, TRef sp)
{
  CTState *cts = ctype_ctsG(J2G(J));
  IRType t = crec_ct2irt(cts, s);
  CTInfo sinfo = s->info;
  if (ctype_isnum(sinfo)) {
    TRef tr;
    if (t == IRT_CDATA)
      goto err_nyi;  /* NYI: copyval of >64 bit integers. */
    tr = emitir(IRT(IR_XLOAD, t), sp, 0);
    if (t == IRT_FLOAT || t == IRT_U32) {  /* Keep uint32_t/float as numbers. */
      return emitconv(tr, IRT_NUM, t, 0);
    } else if (t == IRT_I64 || t == IRT_U64) {  /* Box 64 bit integer. */
      sp = tr;
      lj_needsplit(J);
    } else if ((sinfo & CTF_BOOL)) {
      /* Assume not equal to zero. Fixup and emit pending guard later. */
      lj_ir_set(J, IRTGI(IR_NE), tr, lj_ir_kint(J, 0));
      J->postproc = LJ_POST_FIXGUARD;
      return TREF_TRUE;
    } else {
      return tr;
    }
  } else if (ctype_isptr(sinfo) || ctype_isenum(sinfo)) {
    sp = emitir(IRT(IR_XLOAD, t), sp, 0);  /* Box pointers and enums. */
  } else if (ctype_isrefarray(sinfo) || ctype_isstruct(sinfo)) {
    cts->L = J->L;
    sid = lj_ctype_intern(cts, CTINFO_REF(sid), CTSIZE_PTR);  /* Create ref. */
  } else if (ctype_iscomplex(sinfo)) {  /* Unbox/box complex. */
    ptrdiff_t esz = (ptrdiff_t)(s->size >> 1);
    TRef ptr, tr1, tr2, dp;
    dp = emitir(IRTG(IR_CNEW, IRT_CDATA), lj_ir_kint(J, sid), TREF_NIL);
    tr1 = emitir(IRT(IR_XLOAD, t), sp, 0);
    ptr = emitir(IRT(IR_ADD, IRT_PTR), sp, lj_ir_kintp(J, esz));
    tr2 = emitir(IRT(IR_XLOAD, t), ptr, 0);
    ptr = emitir(IRT(IR_ADD, IRT_PTR), dp, lj_ir_kintp(J, sizeof(GCcdata)));
    emitir(IRT(IR_XSTORE, t), ptr, tr1);
    ptr = emitir(IRT(IR_ADD, IRT_PTR), dp, lj_ir_kintp(J, sizeof(GCcdata)+esz));
    emitir(IRT(IR_XSTORE, t), ptr, tr2);
    return dp;
  } else {
    /* NYI: copyval of vectors. */
  err_nyi:
    lj_trace_err(J, LJ_TRERR_NYICONV);
  }
  /* Box pointer, ref, enum or 64 bit integer. */
  return emitir(IRTG(IR_CNEWI, IRT_CDATA), lj_ir_kint(J, sid), sp);
}