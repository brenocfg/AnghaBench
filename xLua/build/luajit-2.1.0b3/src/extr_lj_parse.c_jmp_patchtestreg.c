#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ins; } ;
struct TYPE_4__ {TYPE_2__* bcbase; } ;
typedef  TYPE_1__ FuncState ;
typedef  scalar_t__ BCReg ;
typedef  int BCPos ;
typedef  scalar_t__ BCOp ;
typedef  TYPE_2__ BCInsLine ;

/* Variables and functions */
 int /*<<< orphan*/  BCINS_AJ (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ BC_ISFC ; 
 scalar_t__ BC_IST ; 
 scalar_t__ BC_ISTC ; 
 int /*<<< orphan*/  BC_JMP ; 
 scalar_t__ NO_REG ; 
 scalar_t__ bc_a (int /*<<< orphan*/ ) ; 
 scalar_t__ bc_d (int /*<<< orphan*/ ) ; 
 scalar_t__ bc_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setbc_a (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  setbc_op (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int jmp_patchtestreg(FuncState *fs, BCPos pc, BCReg reg)
{
  BCInsLine *ilp = &fs->bcbase[pc >= 1 ? pc-1 : pc];
  BCOp op = bc_op(ilp->ins);
  if (op == BC_ISTC || op == BC_ISFC) {
    if (reg != NO_REG && reg != bc_d(ilp->ins)) {
      setbc_a(&ilp->ins, reg);
    } else {  /* Nothing to store or already in the right register. */
      setbc_op(&ilp->ins, op+(BC_IST-BC_ISTC));
      setbc_a(&ilp->ins, 0);
    }
  } else if (bc_a(ilp->ins) == NO_REG) {
    if (reg == NO_REG) {
      ilp->ins = BCINS_AJ(BC_JMP, bc_a(fs->bcbase[pc].ins), 0);
    } else {
      setbc_a(&ilp->ins, reg);
      if (reg >= bc_a(ilp[1].ins))
	setbc_a(&ilp[1].ins, reg+1);
    }
  } else {
    return 0;  /* Cannot patch other instructions. */
  }
  return 1;
}