#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_19__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x86Op ;
typedef  scalar_t__ x86Arith ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_22__ {int* flagmcp; int* mcp; } ;
struct TYPE_21__ {scalar_t__ op1; scalar_t__ op2; int /*<<< orphan*/  t; } ;
struct TYPE_20__ {int /*<<< orphan*/  r; } ;
typedef  int /*<<< orphan*/  RegSet ;
typedef  int /*<<< orphan*/  Reg ;
typedef  int MCode ;
typedef  scalar_t__ IRRef ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  CC_O ; 
 TYPE_19__* IR (scalar_t__) ; 
 scalar_t__ LJ_64 ; 
 int /*<<< orphan*/  REX_64IR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int /*<<< orphan*/  XG_ARITHi (scalar_t__) ; 
 scalar_t__ XI_TESTb ; 
 int /*<<< orphan*/  XO_ARITH (scalar_t__) ; 
 int /*<<< orphan*/  XO_IMUL ; 
 int /*<<< orphan*/  XO_IMULi ; 
 int /*<<< orphan*/  XO_IMULi8 ; 
 scalar_t__ XOg_X_IMUL ; 
 int /*<<< orphan*/  asm_fuseloadm (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_guardcc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_isk32 (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ asm_swapops (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ checki8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_gri (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_i32 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_i8 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_mrm (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_is64 (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isguard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_dest (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_hasreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_left (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ra_noreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_noweak (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asm_intarith(ASMState *as, IRIns *ir, x86Arith xa)
{
  IRRef lref = ir->op1;
  IRRef rref = ir->op2;
  RegSet allow = RSET_GPR;
  Reg dest, right;
  int32_t k = 0;
  if (as->flagmcp == as->mcp) {  /* Drop test r,r instruction. */
    MCode *p = as->mcp + ((LJ_64 && *as->mcp < XI_TESTb) ? 3 : 2);
    if ((p[1] & 15) < 14) {
      if ((p[1] & 15) >= 12) p[1] -= 4;  /* L <->S, NL <-> NS */
      as->flagmcp = NULL;
      as->mcp = p;
    }  /* else: cannot transform LE/NLE to cc without use of OF. */
  }
  right = IR(rref)->r;
  if (ra_hasreg(right)) {
    rset_clear(allow, right);
    ra_noweak(as, right);
  }
  dest = ra_dest(as, ir, allow);
  if (lref == rref) {
    right = dest;
  } else if (ra_noreg(right) && !asm_isk32(as, rref, &k)) {
    if (asm_swapops(as, ir)) {
      IRRef tmp = lref; lref = rref; rref = tmp;
    }
    right = asm_fuseloadm(as, rref, rset_clear(allow, dest), irt_is64(ir->t));
  }
  if (irt_isguard(ir->t))  /* For IR_ADDOV etc. */
    asm_guardcc(as, CC_O);
  if (xa != XOg_X_IMUL) {
    if (ra_hasreg(right))
      emit_mrm(as, XO_ARITH(xa), REX_64IR(ir, dest), right);
    else
      emit_gri(as, XG_ARITHi(xa), REX_64IR(ir, dest), k);
  } else if (ra_hasreg(right)) {  /* IMUL r, mrm. */
    emit_mrm(as, XO_IMUL, REX_64IR(ir, dest), right);
  } else {  /* IMUL r, r, k. */
    /* NYI: use lea/shl/add/sub (FOLD only does 2^k) depending on CPU. */
    Reg left = asm_fuseloadm(as, lref, RSET_GPR, irt_is64(ir->t));
    x86Op xo;
    if (checki8(k)) { emit_i8(as, k); xo = XO_IMULi8;
    } else { emit_i32(as, k); xo = XO_IMULi; }
    emit_mrm(as, xo, REX_64IR(ir, dest), left);
    return;
  }
  ra_left(as, dest, lref);
}