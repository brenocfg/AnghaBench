#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ lua_Number ;
struct TYPE_5__ {int /*<<< orphan*/  pt; } ;
typedef  TYPE_1__ jit_State ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  cTValue ;
typedef  int /*<<< orphan*/  TRef ;
typedef  scalar_t__ IRType ;
typedef  scalar_t__ BCReg ;
typedef  scalar_t__ BCOp ;
typedef  int /*<<< orphan*/  const BCIns ;

/* Variables and functions */
 scalar_t__ BCMbase ; 
 scalar_t__ BCMdst ; 
 scalar_t__ BC_JMP ; 
 scalar_t__ BC_KNUM ; 
 scalar_t__ BC_KSHORT ; 
 scalar_t__ IRT_INT ; 
 scalar_t__ bc_a (int /*<<< orphan*/  const) ; 
 scalar_t__ bc_d (int /*<<< orphan*/  const) ; 
 int bc_j (int /*<<< orphan*/  const) ; 
 scalar_t__ bc_op (int /*<<< orphan*/  const) ; 
 scalar_t__ bcmode_a (scalar_t__) ; 
 int /*<<< orphan*/  lj_ir_kint (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  lj_ir_knum (TYPE_1__*,scalar_t__) ; 
 scalar_t__ numV (int /*<<< orphan*/ *) ; 
 scalar_t__ numberVint (int /*<<< orphan*/ *) ; 
 scalar_t__ numberVnum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* proto_bc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * proto_knumtv (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ tvisint (int /*<<< orphan*/ *) ; 

__attribute__((used)) static TRef find_kinit(jit_State *J, const BCIns *endpc, BCReg slot, IRType t)
{
  /* This algorithm is rather simplistic and assumes quite a bit about
  ** how the bytecode is generated. It works fine for FORI initializers,
  ** but it won't necessarily work in other cases (e.g. iterator arguments).
  ** It doesn't do anything fancy, either (like backpropagating MOVs).
  */
  const BCIns *pc, *startpc = proto_bc(J->pt);
  for (pc = endpc-1; pc > startpc; pc--) {
    BCIns ins = *pc;
    BCOp op = bc_op(ins);
    /* First try to find the last instruction that stores to this slot. */
    if (bcmode_a(op) == BCMbase && bc_a(ins) <= slot) {
      return 0;  /* Multiple results, e.g. from a CALL or KNIL. */
    } else if (bcmode_a(op) == BCMdst && bc_a(ins) == slot) {
      if (op == BC_KSHORT || op == BC_KNUM) {  /* Found const. initializer. */
	/* Now try to verify there's no forward jump across it. */
	const BCIns *kpc = pc;
	for (; pc > startpc; pc--)
	  if (bc_op(*pc) == BC_JMP) {
	    const BCIns *target = pc+bc_j(*pc)+1;
	    if (target > kpc && target <= endpc)
	      return 0;  /* Conditional assignment. */
	  }
	if (op == BC_KSHORT) {
	  int32_t k = (int32_t)(int16_t)bc_d(ins);
	  return t == IRT_INT ? lj_ir_kint(J, k) : lj_ir_knum(J, (lua_Number)k);
	} else {
	  cTValue *tv = proto_knumtv(J->pt, bc_d(ins));
	  if (t == IRT_INT) {
	    int32_t k = numberVint(tv);
	    if (tvisint(tv) || numV(tv) == (lua_Number)k)  /* -0 is ok here. */
	      return lj_ir_kint(J, k);
	    return 0;  /* Type mismatch. */
	  } else {
	    return lj_ir_knum(J, numberVnum(tv));
	  }
	}
      }
      return 0;  /* Non-constant initializer. */
    }
  }
  return 0;  /* No assignment to this slot found? */
}