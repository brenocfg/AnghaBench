#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ x86Shift ;
typedef  scalar_t__ x86Op ;
struct TYPE_21__ {int flags; } ;
struct TYPE_20__ {int i; scalar_t__ r; int /*<<< orphan*/  op1; int /*<<< orphan*/  t; int /*<<< orphan*/  op2; } ;
typedef  scalar_t__ Reg ;
typedef  int /*<<< orphan*/  IRRef ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 TYPE_1__* IR (int /*<<< orphan*/ ) ; 
 int JIT_F_BMI2 ; 
 scalar_t__ REX_64IR (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  RID2RSET (scalar_t__) ; 
 scalar_t__ RID_ECX ; 
 int /*<<< orphan*/  RSET_GPR ; 
 scalar_t__ VEX_64IR (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  XO_MOV ; 
 int /*<<< orphan*/  XO_SHIFT1 ; 
 int /*<<< orphan*/  XO_SHIFTcl ; 
 scalar_t__ XOg_ROL ; 
 scalar_t__ XV_RORX ; 
 scalar_t__ asm_fuseloadm (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  emit_i8 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  emit_mrm (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  emit_rr (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  emit_shifti (TYPE_2__*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ irref_isk (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_is64 (int /*<<< orphan*/ ) ; 
 scalar_t__ ra_alloc1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_allocref (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_dest (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_left (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_noreg (scalar_t__) ; 
 int /*<<< orphan*/  ra_noweak (TYPE_2__*,scalar_t__) ; 
 scalar_t__ ra_scratch (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_exclude (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void asm_bitshift(ASMState *as, IRIns *ir, x86Shift xs, x86Op xv)
{
  IRRef rref = ir->op2;
  IRIns *irr = IR(rref);
  Reg dest;
  if (irref_isk(rref)) {  /* Constant shifts. */
    int shift;
    dest = ra_dest(as, ir, RSET_GPR);
    shift = irr->i & (irt_is64(ir->t) ? 63 : 31);
    if (!xv && shift && (as->flags & JIT_F_BMI2)) {
      Reg left = asm_fuseloadm(as, ir->op1, RSET_GPR, irt_is64(ir->t));
      if (left != dest) {  /* BMI2 rotate right by constant. */
	emit_i8(as, xs == XOg_ROL ? -shift : shift);
	emit_mrm(as, VEX_64IR(ir, XV_RORX), dest, left);
	return;
      }
    }
    switch (shift) {
    case 0: break;
    case 1: emit_rr(as, XO_SHIFT1, REX_64IR(ir, xs), dest); break;
    default: emit_shifti(as, REX_64IR(ir, xs), dest, shift); break;
    }
  } else if ((as->flags & JIT_F_BMI2) && xv) {	/* BMI2 variable shifts. */
    Reg left, right;
    dest = ra_dest(as, ir, RSET_GPR);
    right = ra_alloc1(as, rref, RSET_GPR);
    left = asm_fuseloadm(as, ir->op1, rset_exclude(RSET_GPR, right),
			 irt_is64(ir->t));
    emit_mrm(as, VEX_64IR(ir, xv) ^ (right << 19), dest, left);
    return;
  } else {  /* Variable shifts implicitly use register cl (i.e. ecx). */
    Reg right;
    dest = ra_dest(as, ir, rset_exclude(RSET_GPR, RID_ECX));
    if (dest == RID_ECX) {
      dest = ra_scratch(as, rset_exclude(RSET_GPR, RID_ECX));
      emit_rr(as, XO_MOV, RID_ECX, dest);
    }
    right = irr->r;
    if (ra_noreg(right))
      right = ra_allocref(as, rref, RID2RSET(RID_ECX));
    else if (right != RID_ECX)
      ra_scratch(as, RID2RSET(RID_ECX));
    emit_rr(as, XO_SHIFTcl, REX_64IR(ir, xs), dest);
    ra_noweak(as, right);
    if (right != RID_ECX)
      emit_rr(as, XO_MOV, RID_ECX, right);
  }
  ra_left(as, dest, ir->op1);
  /*
  ** Note: avoid using the flags resulting from a shift or rotate!
  ** All of them cause a partial flag stall, except for r,1 shifts
  ** (but not rotates). And a shift count of 0 leaves the flags unmodified.
  */
}