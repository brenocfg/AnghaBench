#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int op2; scalar_t__ o; int /*<<< orphan*/  op1; int /*<<< orphan*/  r; } ;
typedef  int /*<<< orphan*/  Reg ;
typedef  TYPE_1__ IRIns ;
typedef  int /*<<< orphan*/  ASMState ;

/* Variables and functions */
 TYPE_1__* IR (int /*<<< orphan*/ ) ; 
 int IRBUFHDR_APPEND ; 
 scalar_t__ IR_BUFHDR ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int /*<<< orphan*/  SBuf ; 
 int /*<<< orphan*/  b ; 
 int /*<<< orphan*/  emit_loadofs (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_storeofs (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ irref_isk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p ; 
 int /*<<< orphan*/  ra_allocref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_dest (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_hasreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_left (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_leftov (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_scratch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_used (TYPE_1__*) ; 
 int /*<<< orphan*/  ra_weak (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_exclude (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asm_bufhdr(ASMState *as, IRIns *ir)
{
  Reg sb = ra_dest(as, ir, RSET_GPR);
  if ((ir->op2 & IRBUFHDR_APPEND)) {
    /* Rematerialize const buffer pointer instead of likely spill. */
    IRIns *irp = IR(ir->op1);
    if (!(ra_hasreg(irp->r) || irp == ir-1 ||
	  (irp == ir-2 && !ra_used(ir-1)))) {
      while (!(irp->o == IR_BUFHDR && !(irp->op2 & IRBUFHDR_APPEND)))
	irp = IR(irp->op1);
      if (irref_isk(irp->op1)) {
	ra_weak(as, ra_allocref(as, ir->op1, RSET_GPR));
	ir = irp;
      }
    }
  } else {
    Reg tmp = ra_scratch(as, rset_exclude(RSET_GPR, sb));
    /* Passing ir isn't strictly correct, but it's an IRT_P32, too. */
    emit_storeofs(as, ir, tmp, sb, offsetof(SBuf, p));
    emit_loadofs(as, ir, tmp, sb, offsetof(SBuf, b));
  }
#if LJ_TARGET_X86ORX64
  ra_left(as, sb, ir->op1);
#else
  ra_leftov(as, sb, ir->op1);
#endif
}