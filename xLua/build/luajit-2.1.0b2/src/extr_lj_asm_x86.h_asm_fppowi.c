#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  op2; int /*<<< orphan*/  op1; int /*<<< orphan*/  r; } ;
typedef  int RegSet ;
typedef  TYPE_1__ IRIns ;
typedef  int /*<<< orphan*/  ASMState ;

/* Variables and functions */
 int RID2RSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RID_EAX ; 
 int /*<<< orphan*/  RID_XMM0 ; 
 scalar_t__ RID_XMM1 ; 
 int RSET_RANGE (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  emit_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_vm_powi_sse ; 
 int /*<<< orphan*/  ra_destreg (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_evictset (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ra_hasreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_left (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_clear (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asm_fppowi(ASMState *as, IRIns *ir)
{
  /* The modified regs must match with the *.dasc implementation. */
  RegSet drop = RSET_RANGE(RID_XMM0, RID_XMM1+1)|RID2RSET(RID_EAX);
  if (ra_hasreg(ir->r))
    rset_clear(drop, ir->r);  /* Dest reg handled below. */
  ra_evictset(as, drop);
  ra_destreg(as, ir, RID_XMM0);
  emit_call(as, lj_vm_powi_sse);
  ra_left(as, RID_XMM0, ir->op1);
  ra_left(as, RID_EAX, ir->op2);
}