#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ curins; scalar_t__ loopref; } ;
struct TYPE_6__ {scalar_t__ op1; scalar_t__ op2; size_t o; int /*<<< orphan*/  t; int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 TYPE_1__* IR (scalar_t__) ; 
 int /*<<< orphan*/  irm_iscomm (int /*<<< orphan*/ ) ; 
 scalar_t__ irref_isk (scalar_t__) ; 
 int /*<<< orphan*/  irt_isphi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_ir_mode ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ opisfusableload (size_t) ; 
 scalar_t__ ra_hasreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_noreg (int /*<<< orphan*/ ) ; 
 scalar_t__ ra_samehint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asm_swapops(ASMState *as, IRIns *ir)
{
  IRIns *irl = IR(ir->op1);
  IRIns *irr = IR(ir->op2);
  lua_assert(ra_noreg(irr->r));
  if (!irm_iscomm(lj_ir_mode[ir->o]))
    return 0;  /* Can't swap non-commutative operations. */
  if (irref_isk(ir->op2))
    return 0;  /* Don't swap constants to the left. */
  if (ra_hasreg(irl->r))
    return 1;  /* Swap if left already has a register. */
  if (ra_samehint(ir->r, irr->r))
    return 1;  /* Swap if dest and right have matching hints. */
  if (as->curins > as->loopref) {  /* In variant part? */
    if (ir->op2 < as->loopref && !irt_isphi(irr->t))
      return 0;  /* Keep invariants on the right. */
    if (ir->op1 < as->loopref && !irt_isphi(irl->t))
      return 1;  /* Swap invariants to the right. */
  }
  if (opisfusableload(irl->o))
    return 1;  /* Swap fusable loads to the right. */
  return 0;  /* Otherwise don't swap. */
}