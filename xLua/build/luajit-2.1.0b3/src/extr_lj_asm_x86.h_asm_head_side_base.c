#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  freeset; int /*<<< orphan*/  modset; } ;
struct TYPE_9__ {int r; int /*<<< orphan*/  t; } ;
typedef  int /*<<< orphan*/  RegSet ;
typedef  int Reg ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 TYPE_1__* IR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REF_BASE ; 
 int REX_GC64 ; 
 int RID_INIT ; 
 int /*<<< orphan*/  XO_MOV ; 
 int /*<<< orphan*/  emit_getgl (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_rr (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ irt_ismarked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jit_base ; 
 int /*<<< orphan*/  ra_free (TYPE_2__*,int) ; 
 scalar_t__ ra_hasreg (int) ; 
 int /*<<< orphan*/  rset_clear (int /*<<< orphan*/ ,int) ; 
 scalar_t__ rset_test (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static RegSet asm_head_side_base(ASMState *as, IRIns *irp, RegSet allow)
{
  IRIns *ir = IR(REF_BASE);
  Reg r = ir->r;
  if (ra_hasreg(r)) {
    ra_free(as, r);
    if (rset_test(as->modset, r) || irt_ismarked(ir->t))
      ir->r = RID_INIT;  /* No inheritance for modified BASE register. */
    if (irp->r == r) {
      rset_clear(allow, r);  /* Mark same BASE register as coalesced. */
    } else if (ra_hasreg(irp->r) && rset_test(as->freeset, irp->r)) {
      /* Move from coalesced parent reg. */
      rset_clear(allow, irp->r);
      emit_rr(as, XO_MOV, r|REX_GC64, irp->r);
    } else {
      emit_getgl(as, r, jit_base);  /* Otherwise reload BASE. */
    }
  }
  return allow;
}