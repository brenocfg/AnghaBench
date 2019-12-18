#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
struct TYPE_12__ {int ofs; void* base; void* idx; void* scale; } ;
struct TYPE_14__ {TYPE_1__ mrm; } ;
struct TYPE_13__ {scalar_t__ o; int i; scalar_t__ op2; scalar_t__ op1; int /*<<< orphan*/  r; } ;
typedef  int /*<<< orphan*/  RegSet ;
typedef  scalar_t__ Reg ;
typedef  scalar_t__ IRRef ;
typedef  TYPE_2__ IRIns ;
typedef  TYPE_3__ ASMState ;

/* Variables and functions */
 TYPE_2__* IR (scalar_t__) ; 
 scalar_t__ IR_ADD ; 
 scalar_t__ IR_BSHL ; 
 scalar_t__ IR_KKPTR ; 
 scalar_t__ IR_KPTR ; 
 scalar_t__ IR_STRREF ; 
 void* RID_NONE ; 
 void* XM_SCALE1 ; 
 void* XM_SCALE2 ; 
 int /*<<< orphan*/  asm_fusestrref (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ asm_isk32 (TYPE_3__*,scalar_t__,int*) ; 
 scalar_t__ canfuse (TYPE_3__*,TYPE_2__*) ; 
 scalar_t__ irref_isk (scalar_t__) ; 
 scalar_t__ ra_alloc1 (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_noreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_clear (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void asm_fusexref(ASMState *as, IRRef ref, RegSet allow)
{
  IRIns *ir = IR(ref);
  as->mrm.idx = RID_NONE;
  if (ir->o == IR_KPTR || ir->o == IR_KKPTR) {
    as->mrm.ofs = ir->i;
    as->mrm.base = RID_NONE;
  } else if (ir->o == IR_STRREF) {
    asm_fusestrref(as, ir, allow);
  } else {
    as->mrm.ofs = 0;
    if (canfuse(as, ir) && ir->o == IR_ADD && ra_noreg(ir->r)) {
      /* Gather (base+idx*sz)+ofs as emitted by cdata ptr/array indexing. */
      IRIns *irx;
      IRRef idx;
      Reg r;
      if (asm_isk32(as, ir->op2, &as->mrm.ofs)) {  /* Recognize x+ofs. */
	ref = ir->op1;
	ir = IR(ref);
	if (!(ir->o == IR_ADD && canfuse(as, ir) && ra_noreg(ir->r)))
	  goto noadd;
      }
      as->mrm.scale = XM_SCALE1;
      idx = ir->op1;
      ref = ir->op2;
      irx = IR(idx);
      if (!(irx->o == IR_BSHL || irx->o == IR_ADD)) {  /* Try other operand. */
	idx = ir->op2;
	ref = ir->op1;
	irx = IR(idx);
      }
      if (canfuse(as, irx) && ra_noreg(irx->r)) {
	if (irx->o == IR_BSHL && irref_isk(irx->op2) && IR(irx->op2)->i <= 3) {
	  /* Recognize idx<<b with b = 0-3, corresponding to sz = (1),2,4,8. */
	  idx = irx->op1;
	  as->mrm.scale = (uint8_t)(IR(irx->op2)->i << 6);
	} else if (irx->o == IR_ADD && irx->op1 == irx->op2) {
	  /* FOLD does idx*2 ==> idx<<1 ==> idx+idx. */
	  idx = irx->op1;
	  as->mrm.scale = XM_SCALE2;
	}
      }
      r = ra_alloc1(as, idx, allow);
      rset_clear(allow, r);
      as->mrm.idx = (uint8_t)r;
    }
  noadd:
    as->mrm.base = (uint8_t)ra_alloc1(as, ref, allow);
  }
}