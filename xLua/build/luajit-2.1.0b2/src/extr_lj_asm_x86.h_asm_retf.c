#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_14__ {int /*<<< orphan*/  t; } ;
struct TYPE_13__ {scalar_t__ topslot; } ;
struct TYPE_12__ {int /*<<< orphan*/  op2; } ;
typedef  int /*<<< orphan*/  Reg ;
typedef  TYPE_1__ IRIns ;
typedef  scalar_t__ BCReg ;
typedef  int /*<<< orphan*/  BCIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  CC_NE ; 
 TYPE_4__* IR (int /*<<< orphan*/ ) ; 
 scalar_t__ LJ_FR2 ; 
 int /*<<< orphan*/  REF_BASE ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int /*<<< orphan*/  XG_ARITHi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOg_CMP ; 
 int /*<<< orphan*/  asm_guardcc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bc_a (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  emit_addptr (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_gmroi (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_setgl (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ir_kptr (TYPE_4__*) ; 
 int /*<<< orphan*/  irt_setmark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jit_base ; 
 int /*<<< orphan*/  ptr2addr (void*) ; 
 int /*<<< orphan*/  ra_alloc1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asm_retf(ASMState *as, IRIns *ir)
{
  Reg base = ra_alloc1(as, REF_BASE, RSET_GPR);
  void *pc = ir_kptr(IR(ir->op2));
  int32_t delta = 1+LJ_FR2+bc_a(*((const BCIns *)pc - 1));
  as->topslot -= (BCReg)delta;
  if ((int32_t)as->topslot < 0) as->topslot = 0;
  irt_setmark(IR(REF_BASE)->t);  /* Children must not coalesce with BASE reg. */
  emit_setgl(as, base, jit_base);
  emit_addptr(as, base, -8*delta);
  asm_guardcc(as, CC_NE);
  emit_gmroi(as, XG_ARITHi(XOg_CMP), base, -4, ptr2addr(pc));
}