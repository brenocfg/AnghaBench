#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  postproc; } ;
typedef  TYPE_1__ jit_State ;
struct TYPE_10__ {int /*<<< orphan*/  info; } ;
typedef  scalar_t__ TRef ;
typedef  scalar_t__ MMS ;
typedef  scalar_t__ IRType ;
typedef  int /*<<< orphan*/  IROp ;
typedef  int /*<<< orphan*/  CTypeID ;
typedef  TYPE_2__ CType ;
typedef  int /*<<< orphan*/  CTState ;
typedef  int CTSize ;

/* Variables and functions */
 int CTALIGN_PTR ; 
 int /*<<< orphan*/  CTINFO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CTSIZE_PTR ; 
 int /*<<< orphan*/  CT_PTR ; 
 int /*<<< orphan*/  IRCONV_ANY ; 
 int /*<<< orphan*/  IRCONV_SEXT ; 
 int /*<<< orphan*/  IRT (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  IRTG (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ IRT_CDATA ; 
 scalar_t__ IRT_FLOAT ; 
 scalar_t__ IRT_I64 ; 
 scalar_t__ IRT_I8 ; 
 scalar_t__ IRT_INT ; 
 scalar_t__ IRT_INTP ; 
 scalar_t__ IRT_NUM ; 
 scalar_t__ IRT_PTR ; 
 int /*<<< orphan*/  IRT_U32 ; 
 scalar_t__ IRT_U64 ; 
 scalar_t__ IR_ADD ; 
 scalar_t__ IR_BSAR ; 
 int /*<<< orphan*/  IR_CNEWI ; 
 int /*<<< orphan*/  IR_EQ ; 
 scalar_t__ IR_MUL ; 
 scalar_t__ IR_SUB ; 
 int /*<<< orphan*/  IR_ULE ; 
 int /*<<< orphan*/  IR_ULT ; 
 int /*<<< orphan*/  J2G (TYPE_1__*) ; 
 int /*<<< orphan*/  LJ_POST_FIXGUARD ; 
 scalar_t__ MM_add ; 
 scalar_t__ MM_eq ; 
 scalar_t__ MM_le ; 
 scalar_t__ MM_lt ; 
 scalar_t__ MM_sub ; 
 scalar_t__ TREF_TRUE ; 
 int ctype_cid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ctype_ctsG (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isnum (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isptr (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isrefarray (int /*<<< orphan*/ ) ; 
 scalar_t__ emitconv (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ emitir (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lj_ctype_intern (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lj_ctype_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lj_fls (int) ; 
 scalar_t__ lj_ir_kint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lj_ir_kintp (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lj_ir_set (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ tref_type (scalar_t__) ; 
 int /*<<< orphan*/  tref_typerange (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TRef crec_arith_ptr(jit_State *J, TRef *sp, CType **s, MMS mm)
{
  CTState *cts = ctype_ctsG(J2G(J));
  CType *ctp = s[0];
  if (!(sp[0] && sp[1])) return 0;
  if (ctype_isptr(ctp->info) || ctype_isrefarray(ctp->info)) {
    if ((mm == MM_sub || mm == MM_eq || mm == MM_lt || mm == MM_le) &&
	(ctype_isptr(s[1]->info) || ctype_isrefarray(s[1]->info))) {
      if (mm == MM_sub) {  /* Pointer difference. */
	TRef tr;
	CTSize sz = lj_ctype_size(cts, ctype_cid(ctp->info));
	if (sz == 0 || (sz & (sz-1)) != 0)
	  return 0;  /* NYI: integer division. */
	tr = emitir(IRT(IR_SUB, IRT_INTP), sp[0], sp[1]);
	tr = emitir(IRT(IR_BSAR, IRT_INTP), tr, lj_ir_kint(J, lj_fls(sz)));
#if LJ_64
	tr = emitconv(tr, IRT_NUM, IRT_INTP, 0);
#endif
	return tr;
      } else {  /* Pointer comparison (unsigned). */
	/* Assume true comparison. Fixup and emit pending guard later. */
	IROp op = mm == MM_eq ? IR_EQ : mm == MM_lt ? IR_ULT : IR_ULE;
	lj_ir_set(J, IRTG(op, IRT_PTR), sp[0], sp[1]);
	J->postproc = LJ_POST_FIXGUARD;
	return TREF_TRUE;
      }
    }
    if (!((mm == MM_add || mm == MM_sub) && ctype_isnum(s[1]->info)))
      return 0;
  } else if (mm == MM_add && ctype_isnum(ctp->info) &&
	     (ctype_isptr(s[1]->info) || ctype_isrefarray(s[1]->info))) {
    TRef tr = sp[0]; sp[0] = sp[1]; sp[1] = tr;  /* Swap pointer and index. */
    ctp = s[1];
  } else {
    return 0;
  }
  {
    TRef tr = sp[1];
    IRType t = tref_type(tr);
    CTSize sz = lj_ctype_size(cts, ctype_cid(ctp->info));
    CTypeID id;
#if LJ_64
    if (t == IRT_NUM || t == IRT_FLOAT)
      tr = emitconv(tr, IRT_INTP, t, IRCONV_ANY);
    else if (!(t == IRT_I64 || t == IRT_U64))
      tr = emitconv(tr, IRT_INTP, IRT_INT,
		    ((t - IRT_I8) & 1) ? 0 : IRCONV_SEXT);
#else
    if (!tref_typerange(sp[1], IRT_I8, IRT_U32)) {
      tr = emitconv(tr, IRT_INTP, t,
		    (t == IRT_NUM || t == IRT_FLOAT) ? IRCONV_ANY : 0);
    }
#endif
    tr = emitir(IRT(IR_MUL, IRT_INTP), tr, lj_ir_kintp(J, sz));
    tr = emitir(IRT(mm+(int)IR_ADD-(int)MM_add, IRT_PTR), sp[0], tr);
    id = lj_ctype_intern(cts, CTINFO(CT_PTR, CTALIGN_PTR|ctype_cid(ctp->info)),
			 CTSIZE_PTR);
    return emitir(IRTG(IR_CNEWI, IRT_CDATA), lj_ir_kint(J, id), tr);
  }
}