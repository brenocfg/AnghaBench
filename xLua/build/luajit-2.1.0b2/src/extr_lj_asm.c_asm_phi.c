#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_13__ {int phiset; int freeset; int /*<<< orphan*/  J; scalar_t__* phireg; } ;
struct TYPE_12__ {scalar_t__ r; int /*<<< orphan*/  s; int /*<<< orphan*/  t; scalar_t__ op1; scalar_t__ op2; } ;
typedef  int RegSet ;
typedef  size_t Reg ;
typedef  scalar_t__ IRRef1 ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 TYPE_1__* IR (scalar_t__) ; 
 int /*<<< orphan*/  LJ_SOFTFP ; 
 int /*<<< orphan*/  LJ_TRERR_NYIPHI ; 
 scalar_t__ RID_SINK ; 
 int RSET_FPR ; 
 int RSET_GPR ; 
 int /*<<< orphan*/  emit_movrr (TYPE_2__*,TYPE_1__*,size_t,scalar_t__) ; 
 scalar_t__ irt_isfp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_setmark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_trace_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ra_allocref (TYPE_2__*,scalar_t__,int) ; 
 scalar_t__ ra_hasreg (scalar_t__) ; 
 scalar_t__ ra_hasspill (int /*<<< orphan*/ ) ; 
 scalar_t__ ra_noreg (scalar_t__) ; 
 size_t ra_scratch (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ra_sethint (scalar_t__,size_t) ; 
 int /*<<< orphan*/  ra_spill (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  rset_set (int,size_t) ; 

__attribute__((used)) static void asm_phi(ASMState *as, IRIns *ir)
{
  RegSet allow = ((!LJ_SOFTFP && irt_isfp(ir->t)) ? RSET_FPR : RSET_GPR) &
		 ~as->phiset;
  RegSet afree = (as->freeset & allow);
  IRIns *irl = IR(ir->op1);
  IRIns *irr = IR(ir->op2);
  if (ir->r == RID_SINK)  /* Sink PHI. */
    return;
  /* Spill slot shuffling is not implemented yet (but rarely needed). */
  if (ra_hasspill(irl->s) || ra_hasspill(irr->s))
    lj_trace_err(as->J, LJ_TRERR_NYIPHI);
  /* Leave at least one register free for non-PHIs (and PHI cycle breaking). */
  if ((afree & (afree-1))) {  /* Two or more free registers? */
    Reg r;
    if (ra_noreg(irr->r)) {  /* Get a register for the right PHI. */
      r = ra_allocref(as, ir->op2, allow);
    } else {  /* Duplicate right PHI, need a copy (rare). */
      r = ra_scratch(as, allow);
      emit_movrr(as, irr, r, irr->r);
    }
    ir->r = (uint8_t)r;
    rset_set(as->phiset, r);
    as->phireg[r] = (IRRef1)ir->op1;
    irt_setmark(irl->t);  /* Marks left PHIs _with_ register. */
    if (ra_noreg(irl->r))
      ra_sethint(irl->r, r); /* Set register hint for left PHI. */
  } else {  /* Otherwise allocate a spill slot. */
    /* This is overly restrictive, but it triggers only on synthetic code. */
    if (ra_hasreg(irl->r) || ra_hasreg(irr->r))
      lj_trace_err(as->J, LJ_TRERR_NYIPHI);
    ra_spill(as, ir);
    irr->s = ir->s;  /* Set right PHI spill slot. Sync left slot later. */
  }
}