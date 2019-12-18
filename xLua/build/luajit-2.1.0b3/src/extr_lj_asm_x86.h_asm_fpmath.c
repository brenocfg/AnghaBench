#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int flags; int* mcp; } ;
struct TYPE_19__ {int /*<<< orphan*/  op1; int /*<<< orphan*/  r; int /*<<< orphan*/  op2; } ;
typedef  int RegSet ;
typedef  int /*<<< orphan*/  Reg ;
typedef  int MCode ;
typedef  TYPE_1__ IRIns ;
typedef  scalar_t__ IRFPMathOp ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 scalar_t__ IRCALL_lj_vm_floor ; 
 scalar_t__ IRFPM_CEIL ; 
 scalar_t__ IRFPM_EXP2 ; 
 scalar_t__ IRFPM_FLOOR ; 
 scalar_t__ IRFPM_SQRT ; 
 scalar_t__ IRFPM_TRUNC ; 
 int JIT_F_SSE4_1 ; 
 scalar_t__ LJ_64 ; 
 int RID2RSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RID_EAX ; 
 int /*<<< orphan*/  RID_XMM0 ; 
 scalar_t__ RID_XMM3 ; 
 int /*<<< orphan*/  RSET_FPR ; 
 int RSET_RANGE (int /*<<< orphan*/ ,scalar_t__) ; 
 int XO_ROUNDSD ; 
 int XO_SQRTSD ; 
 int /*<<< orphan*/  asm_callid (TYPE_2__*,TYPE_1__*,scalar_t__) ; 
 scalar_t__ asm_fpjoin_pow (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_fuseload (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_call (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_i8 (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  emit_mrm (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_vm_ceil_sse ; 
 int /*<<< orphan*/  lj_vm_floor_sse ; 
 int /*<<< orphan*/  lj_vm_trunc_sse ; 
 int /*<<< orphan*/  ra_dest (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_destreg (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_evictset (TYPE_2__*,int) ; 
 scalar_t__ ra_hasreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_left (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_clear (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asm_fpmath(ASMState *as, IRIns *ir)
{
  IRFPMathOp fpm = (IRFPMathOp)ir->op2;
  if (fpm == IRFPM_SQRT) {
    Reg dest = ra_dest(as, ir, RSET_FPR);
    Reg left = asm_fuseload(as, ir->op1, RSET_FPR);
    emit_mrm(as, XO_SQRTSD, dest, left);
  } else if (fpm <= IRFPM_TRUNC) {
    if (as->flags & JIT_F_SSE4_1) {  /* SSE4.1 has a rounding instruction. */
      Reg dest = ra_dest(as, ir, RSET_FPR);
      Reg left = asm_fuseload(as, ir->op1, RSET_FPR);
      /* ROUNDSD has a 4-byte opcode which doesn't fit in x86Op.
      ** Let's pretend it's a 3-byte opcode, and compensate afterwards.
      ** This is atrocious, but the alternatives are much worse.
      */
      /* Round down/up/trunc == 1001/1010/1011. */
      emit_i8(as, 0x09 + fpm);
      emit_mrm(as, XO_ROUNDSD, dest, left);
      if (LJ_64 && as->mcp[1] != (MCode)(XO_ROUNDSD >> 16)) {
	as->mcp[0] = as->mcp[1]; as->mcp[1] = 0x0f;  /* Swap 0F and REX. */
      }
      *--as->mcp = 0x66;  /* 1st byte of ROUNDSD opcode. */
    } else {  /* Call helper functions for SSE2 variant. */
      /* The modified regs must match with the *.dasc implementation. */
      RegSet drop = RSET_RANGE(RID_XMM0, RID_XMM3+1)|RID2RSET(RID_EAX);
      if (ra_hasreg(ir->r))
	rset_clear(drop, ir->r);  /* Dest reg handled below. */
      ra_evictset(as, drop);
      ra_destreg(as, ir, RID_XMM0);
      emit_call(as, fpm == IRFPM_FLOOR ? lj_vm_floor_sse :
		    fpm == IRFPM_CEIL ? lj_vm_ceil_sse : lj_vm_trunc_sse);
      ra_left(as, RID_XMM0, ir->op1);
    }
  } else if (fpm == IRFPM_EXP2 && asm_fpjoin_pow(as, ir)) {
    /* Rejoined to pow(). */
  } else {
    asm_callid(as, ir, IRCALL_lj_vm_floor + fpm);
  }
}