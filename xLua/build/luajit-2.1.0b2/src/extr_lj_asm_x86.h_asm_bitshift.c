#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x86Shift ;
struct TYPE_6__ {int i; scalar_t__ r; int /*<<< orphan*/  op1; int /*<<< orphan*/  t; int /*<<< orphan*/  op2; } ;
typedef  scalar_t__ Reg ;
typedef  int /*<<< orphan*/  IRRef ;
typedef  TYPE_1__ IRIns ;
typedef  int /*<<< orphan*/  ASMState ;

/* Variables and functions */
 TYPE_1__* IR (int /*<<< orphan*/ ) ; 
 scalar_t__ REX_64IR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RID2RSET (scalar_t__) ; 
 scalar_t__ RID_ECX ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int /*<<< orphan*/  XO_MOV ; 
 int /*<<< orphan*/  XO_SHIFT1 ; 
 int /*<<< orphan*/  XO_SHIFTcl ; 
 int /*<<< orphan*/  emit_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  emit_shifti (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int) ; 
 scalar_t__ irref_isk (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_is64 (int /*<<< orphan*/ ) ; 
 scalar_t__ ra_allocref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_dest (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_left (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_noreg (scalar_t__) ; 
 int /*<<< orphan*/  ra_noweak (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ra_scratch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_exclude (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void asm_bitshift(ASMState *as, IRIns *ir, x86Shift xs)
{
  IRRef rref = ir->op2;
  IRIns *irr = IR(rref);
  Reg dest;
  if (irref_isk(rref)) {  /* Constant shifts. */
    int shift;
    dest = ra_dest(as, ir, RSET_GPR);
    shift = irr->i & (irt_is64(ir->t) ? 63 : 31);
    switch (shift) {
    case 0: break;
    case 1: emit_rr(as, XO_SHIFT1, REX_64IR(ir, xs), dest); break;
    default: emit_shifti(as, REX_64IR(ir, xs), dest, shift); break;
    }
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