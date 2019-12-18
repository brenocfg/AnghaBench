#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_17__ {int /*<<< orphan*/  t; } ;
struct TYPE_16__ {scalar_t__ topslot; } ;
struct TYPE_15__ {int /*<<< orphan*/  op2; } ;
typedef  int Reg ;
typedef  TYPE_1__ IRIns ;
typedef  scalar_t__ BCReg ;
typedef  int /*<<< orphan*/  BCIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  CC_NE ; 
 TYPE_5__* IR (int /*<<< orphan*/ ) ; 
 scalar_t__ LJ_FR2 ; 
 int /*<<< orphan*/  REF_BASE ; 
 int REX_GC64 ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int /*<<< orphan*/  XG_ARITHi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XO_CMP ; 
 int /*<<< orphan*/  XOg_CMP ; 
 int /*<<< orphan*/  asm_guardcc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bc_a (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  emit_addptr (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  emit_gmroi (TYPE_2__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_loadu64 (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_rmro (TYPE_2__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  emit_setgl (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 void* ir_kptr (TYPE_5__*) ; 
 int /*<<< orphan*/  irt_setmark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jit_base ; 
 int /*<<< orphan*/  ptr2addr (void*) ; 
 int ra_alloc1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ra_scratch (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_exclude (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  u64ptr (void*) ; 

__attribute__((used)) static void asm_retf(ASMState *as, IRIns *ir)
{
  Reg base = ra_alloc1(as, REF_BASE, RSET_GPR);
#if LJ_FR2
  Reg rpc = ra_scratch(as, rset_exclude(RSET_GPR, base));
#endif
  void *pc = ir_kptr(IR(ir->op2));
  int32_t delta = 1+LJ_FR2+bc_a(*((const BCIns *)pc - 1));
  as->topslot -= (BCReg)delta;
  if ((int32_t)as->topslot < 0) as->topslot = 0;
  irt_setmark(IR(REF_BASE)->t);  /* Children must not coalesce with BASE reg. */
  emit_setgl(as, base, jit_base);
  emit_addptr(as, base, -8*delta);
  asm_guardcc(as, CC_NE);
#if LJ_FR2
  emit_rmro(as, XO_CMP, rpc|REX_GC64, base, -8);
  emit_loadu64(as, rpc, u64ptr(pc));
#else
  emit_gmroi(as, XG_ARITHi(XOg_CMP), base, -4, ptr2addr(pc));
#endif
}