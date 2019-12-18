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
struct TYPE_13__ {int phiset; int freeset; int modset; int /*<<< orphan*/ * phireg; int /*<<< orphan*/ * cost; } ;
struct TYPE_12__ {size_t r; int /*<<< orphan*/  t; int /*<<< orphan*/  s; } ;
typedef  int RegSet ;
typedef  size_t Reg ;
typedef  int /*<<< orphan*/  IRRef ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 TYPE_1__* IR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LJ_SOFTFP ; 
 int /*<<< orphan*/  RID2RSET (size_t) ; 
 size_t RID_NONE ; 
 int RSET_EMPTY ; 
 int RSET_FPR ; 
 int RSET_GPR ; 
 int /*<<< orphan*/  asm_phi_break (TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  checkmclim (TYPE_2__*) ; 
 int /*<<< orphan*/  irt_clearmark (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_ismarked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_alloc1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_hasreg (size_t) ; 
 scalar_t__ ra_hasspill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_iskref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_rename (TYPE_2__*,size_t,size_t) ; 
 int /*<<< orphan*/  ra_restore (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_save (TYPE_2__*,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  regcost_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_clear (int,size_t) ; 
 size_t rset_pickbot (int) ; 
 size_t rset_picktop (int) ; 
 int /*<<< orphan*/  rset_set (int,size_t) ; 
 int /*<<< orphan*/  rset_test (int,size_t) ; 

__attribute__((used)) static void asm_phi_shuffle(ASMState *as)
{
  RegSet work;

  /* Find and resolve PHI register mismatches. */
  for (;;) {
    RegSet blocked = RSET_EMPTY;
    RegSet blockedby = RSET_EMPTY;
    RegSet phiset = as->phiset;
    while (phiset) {  /* Check all left PHI operand registers. */
      Reg r = rset_pickbot(phiset);
      IRIns *irl = IR(as->phireg[r]);
      Reg left = irl->r;
      if (r != left) {  /* Mismatch? */
	if (!rset_test(as->freeset, r)) {  /* PHI register blocked? */
	  IRRef ref = regcost_ref(as->cost[r]);
	  /* Blocked by other PHI (w/reg)? */
	  if (!ra_iskref(ref) && irt_ismarked(IR(ref)->t)) {
	    rset_set(blocked, r);
	    if (ra_hasreg(left))
	      rset_set(blockedby, left);
	    left = RID_NONE;
	  } else {  /* Otherwise grab register from invariant. */
	    ra_restore(as, ref);
	    checkmclim(as);
	  }
	}
	if (ra_hasreg(left)) {
	  ra_rename(as, left, r);
	  checkmclim(as);
	}
      }
      rset_clear(phiset, r);
    }
    if (!blocked) break;  /* Finished. */
    if (!(as->freeset & blocked)) {  /* Break cycles if none are free. */
      asm_phi_break(as, blocked, blockedby, RSET_GPR);
      if (!LJ_SOFTFP) asm_phi_break(as, blocked, blockedby, RSET_FPR);
      checkmclim(as);
    }  /* Else retry some more renames. */
  }

  /* Restore/remat invariants whose registers are modified inside the loop. */
#if !LJ_SOFTFP
  work = as->modset & ~(as->freeset | as->phiset) & RSET_FPR;
  while (work) {
    Reg r = rset_pickbot(work);
    ra_restore(as, regcost_ref(as->cost[r]));
    rset_clear(work, r);
    checkmclim(as);
  }
#endif
  work = as->modset & ~(as->freeset | as->phiset);
  while (work) {
    Reg r = rset_pickbot(work);
    ra_restore(as, regcost_ref(as->cost[r]));
    rset_clear(work, r);
    checkmclim(as);
  }

  /* Allocate and save all unsaved PHI regs and clear marks. */
  work = as->phiset;
  while (work) {
    Reg r = rset_picktop(work);
    IRRef lref = as->phireg[r];
    IRIns *ir = IR(lref);
    if (ra_hasspill(ir->s)) {  /* Left PHI gained a spill slot? */
      irt_clearmark(ir->t);  /* Handled here, so clear marker now. */
      ra_alloc1(as, lref, RID2RSET(r));
      ra_save(as, ir, r);  /* Save to spill slot inside the loop. */
      checkmclim(as);
    }
    rset_clear(work, r);
  }
}