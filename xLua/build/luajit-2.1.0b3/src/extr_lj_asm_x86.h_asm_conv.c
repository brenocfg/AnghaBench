#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_21__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x86Op ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_25__ {TYPE_1__* J; } ;
struct TYPE_24__ {int op2; int /*<<< orphan*/  t; int /*<<< orphan*/  op1; } ;
struct TYPE_23__ {int /*<<< orphan*/  r; } ;
struct TYPE_22__ {int /*<<< orphan*/ * k32; int /*<<< orphan*/ * k64; } ;
typedef  int /*<<< orphan*/  RegSet ;
typedef  int Reg ;
typedef  int /*<<< orphan*/  MCLabel ;
typedef  scalar_t__ IRType ;
typedef  int /*<<< orphan*/  IRRef ;
typedef  TYPE_2__ IRIns ;
typedef  TYPE_3__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  CC_NS ; 
 int FORCE_REX ; 
 TYPE_21__* IR (int /*<<< orphan*/ ) ; 
 int IRCONV_SEXT ; 
 int IRCONV_SRCMASK ; 
 scalar_t__ IRT_FLOAT ; 
 scalar_t__ IRT_I16 ; 
 scalar_t__ IRT_I64 ; 
 scalar_t__ IRT_I8 ; 
 scalar_t__ IRT_NUM ; 
 scalar_t__ IRT_P64 ; 
 scalar_t__ IRT_U16 ; 
 scalar_t__ IRT_U32 ; 
 scalar_t__ IRT_U64 ; 
 scalar_t__ IRT_U8 ; 
 scalar_t__ LJ_32 ; 
 scalar_t__ LJ_64 ; 
 size_t LJ_K32_M2P64_31 ; 
 size_t LJ_K64_2P64 ; 
 size_t LJ_K64_M2P64_31 ; 
 size_t LJ_K64_TOBIT ; 
 int REX_64 ; 
 int RID_MRM ; 
 int /*<<< orphan*/  RSET_FPR ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int /*<<< orphan*/  RSET_GPR8 ; 
 int /*<<< orphan*/  XG_ARITHi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XO_ADDSD ; 
 int /*<<< orphan*/  XO_ADDSS ; 
 int /*<<< orphan*/  XO_CVTSD2SS ; 
 int /*<<< orphan*/  XO_CVTSI2SD ; 
 int /*<<< orphan*/  XO_CVTSI2SS ; 
 int /*<<< orphan*/  XO_CVTSS2SD ; 
 int /*<<< orphan*/  XO_CVTTSD2SI ; 
 int /*<<< orphan*/  XO_CVTTSS2SI ; 
 int /*<<< orphan*/  XO_MOV ; 
 int /*<<< orphan*/  XO_MOVD ; 
 int /*<<< orphan*/  XO_MOVSD ; 
 int /*<<< orphan*/  XO_MOVSXb ; 
 int /*<<< orphan*/  XO_MOVSXd ; 
 int /*<<< orphan*/  XO_MOVSXw ; 
 int /*<<< orphan*/  XO_MOVZXb ; 
 int /*<<< orphan*/  XO_MOVZXw ; 
 int /*<<< orphan*/  XO_SUBSD ; 
 int /*<<< orphan*/  XO_TEST ; 
 int /*<<< orphan*/  XO_XORPS ; 
 int /*<<< orphan*/  XOg_ADD ; 
 int asm_fuseload (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int asm_fuseloadm (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  asm_tointg (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  emit_gri (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label (TYPE_3__*) ; 
 int /*<<< orphan*/  emit_mrm (TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  emit_rma (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_rr (TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  emit_sjcc (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ irt_is64 (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isfloat (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isfp (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isguard (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isint (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isint64 (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isnum (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isu32 (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isu64 (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int ra_alloc1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ra_dest (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_left (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_noreg (int /*<<< orphan*/ ) ; 
 int ra_scratch (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_exclude (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rset_test (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void asm_conv(ASMState *as, IRIns *ir)
{
  IRType st = (IRType)(ir->op2 & IRCONV_SRCMASK);
  int st64 = (st == IRT_I64 || st == IRT_U64 || (LJ_64 && st == IRT_P64));
  int stfp = (st == IRT_NUM || st == IRT_FLOAT);
  IRRef lref = ir->op1;
  lua_assert(irt_type(ir->t) != st);
  lua_assert(!(LJ_32 && (irt_isint64(ir->t) || st64)));  /* Handled by SPLIT. */
  if (irt_isfp(ir->t)) {
    Reg dest = ra_dest(as, ir, RSET_FPR);
    if (stfp) {  /* FP to FP conversion. */
      Reg left = asm_fuseload(as, lref, RSET_FPR);
      emit_mrm(as, st == IRT_NUM ? XO_CVTSD2SS : XO_CVTSS2SD, dest, left);
      if (left == dest) return;  /* Avoid the XO_XORPS. */
    } else if (LJ_32 && st == IRT_U32) {  /* U32 to FP conversion on x86. */
      /* number = (2^52+2^51 .. u32) - (2^52+2^51) */
      cTValue *k = &as->J->k64[LJ_K64_TOBIT];
      Reg bias = ra_scratch(as, rset_exclude(RSET_FPR, dest));
      if (irt_isfloat(ir->t))
	emit_rr(as, XO_CVTSD2SS, dest, dest);
      emit_rr(as, XO_SUBSD, dest, bias);  /* Subtract 2^52+2^51 bias. */
      emit_rr(as, XO_XORPS, dest, bias);  /* Merge bias and integer. */
      emit_rma(as, XO_MOVSD, bias, k);
      emit_mrm(as, XO_MOVD, dest, asm_fuseload(as, lref, RSET_GPR));
      return;
    } else {  /* Integer to FP conversion. */
      Reg left = (LJ_64 && (st == IRT_U32 || st == IRT_U64)) ?
		 ra_alloc1(as, lref, RSET_GPR) :
		 asm_fuseloadm(as, lref, RSET_GPR, st64);
      if (LJ_64 && st == IRT_U64) {
	MCLabel l_end = emit_label(as);
	cTValue *k = &as->J->k64[LJ_K64_2P64];
	emit_rma(as, XO_ADDSD, dest, k);  /* Add 2^64 to compensate. */
	emit_sjcc(as, CC_NS, l_end);
	emit_rr(as, XO_TEST, left|REX_64, left);  /* Check if u64 >= 2^63. */
      }
      emit_mrm(as, irt_isnum(ir->t) ? XO_CVTSI2SD : XO_CVTSI2SS,
	       dest|((LJ_64 && (st64 || st == IRT_U32)) ? REX_64 : 0), left);
    }
    emit_rr(as, XO_XORPS, dest, dest);  /* Avoid partial register stall. */
  } else if (stfp) {  /* FP to integer conversion. */
    if (irt_isguard(ir->t)) {
      /* Checked conversions are only supported from number to int. */
      lua_assert(irt_isint(ir->t) && st == IRT_NUM);
      asm_tointg(as, ir, ra_alloc1(as, lref, RSET_FPR));
    } else {
      Reg dest = ra_dest(as, ir, RSET_GPR);
      x86Op op = st == IRT_NUM ? XO_CVTTSD2SI : XO_CVTTSS2SI;
      if (LJ_64 ? irt_isu64(ir->t) : irt_isu32(ir->t)) {
	/* LJ_64: For inputs >= 2^63 add -2^64, convert again. */
	/* LJ_32: For inputs >= 2^31 add -2^31, convert again and add 2^31. */
	Reg tmp = ra_noreg(IR(lref)->r) ? ra_alloc1(as, lref, RSET_FPR) :
					  ra_scratch(as, RSET_FPR);
	MCLabel l_end = emit_label(as);
	if (LJ_32)
	  emit_gri(as, XG_ARITHi(XOg_ADD), dest, (int32_t)0x80000000);
	emit_rr(as, op, dest|REX_64, tmp);
	if (st == IRT_NUM)
	  emit_rma(as, XO_ADDSD, tmp, &as->J->k64[LJ_K64_M2P64_31]);
	else
	  emit_rma(as, XO_ADDSS, tmp, &as->J->k32[LJ_K32_M2P64_31]);
	emit_sjcc(as, CC_NS, l_end);
	emit_rr(as, XO_TEST, dest|REX_64, dest);  /* Check if dest negative. */
	emit_rr(as, op, dest|REX_64, tmp);
	ra_left(as, tmp, lref);
      } else {
	if (LJ_64 && irt_isu32(ir->t))
	  emit_rr(as, XO_MOV, dest, dest);  /* Zero hiword. */
	emit_mrm(as, op,
		 dest|((LJ_64 &&
			(irt_is64(ir->t) || irt_isu32(ir->t))) ? REX_64 : 0),
		 asm_fuseload(as, lref, RSET_FPR));
      }
    }
  } else if (st >= IRT_I8 && st <= IRT_U16) {  /* Extend to 32 bit integer. */
    Reg left, dest = ra_dest(as, ir, RSET_GPR);
    RegSet allow = RSET_GPR;
    x86Op op;
    lua_assert(irt_isint(ir->t) || irt_isu32(ir->t));
    if (st == IRT_I8) {
      op = XO_MOVSXb; allow = RSET_GPR8; dest |= FORCE_REX;
    } else if (st == IRT_U8) {
      op = XO_MOVZXb; allow = RSET_GPR8; dest |= FORCE_REX;
    } else if (st == IRT_I16) {
      op = XO_MOVSXw;
    } else {
      op = XO_MOVZXw;
    }
    left = asm_fuseload(as, lref, allow);
    /* Add extra MOV if source is already in wrong register. */
    if (!LJ_64 && left != RID_MRM && !rset_test(allow, left)) {
      Reg tmp = ra_scratch(as, allow);
      emit_rr(as, op, dest, tmp);
      emit_rr(as, XO_MOV, tmp, left);
    } else {
      emit_mrm(as, op, dest, left);
    }
  } else {  /* 32/64 bit integer conversions. */
    if (LJ_32) {  /* Only need to handle 32/32 bit no-op (cast) on x86. */
      Reg dest = ra_dest(as, ir, RSET_GPR);
      ra_left(as, dest, lref);  /* Do nothing, but may need to move regs. */
    } else if (irt_is64(ir->t)) {
      Reg dest = ra_dest(as, ir, RSET_GPR);
      if (st64 || !(ir->op2 & IRCONV_SEXT)) {
	/* 64/64 bit no-op (cast) or 32 to 64 bit zero extension. */
	ra_left(as, dest, lref);  /* Do nothing, but may need to move regs. */
      } else {  /* 32 to 64 bit sign extension. */
	Reg left = asm_fuseload(as, lref, RSET_GPR);
	emit_mrm(as, XO_MOVSXd, dest|REX_64, left);
      }
    } else {
      Reg dest = ra_dest(as, ir, RSET_GPR);
      if (st64) {
	Reg left = asm_fuseload(as, lref, RSET_GPR);
	/* This is either a 32 bit reg/reg mov which zeroes the hiword
	** or a load of the loword from a 64 bit address.
	*/
	emit_mrm(as, XO_MOV, dest, left);
      } else {  /* 32/32 bit no-op (cast). */
	ra_left(as, dest, lref);  /* Do nothing, but may need to move regs. */
      }
    }
  }
}