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
typedef  scalar_t__ uint8_t ;
struct TYPE_10__ {int freeset; scalar_t__ loopref; int modset; int /*<<< orphan*/ * cost; } ;
struct TYPE_9__ {int /*<<< orphan*/  t; scalar_t__ r; } ;
typedef  int RegSet ;
typedef  size_t Reg ;
typedef  scalar_t__ IRRef ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 TYPE_1__* IR (scalar_t__) ; 
 int /*<<< orphan*/  RA_DBGX (TYPE_2__*) ; 
 int /*<<< orphan*/  REGCOST_REF_T (scalar_t__,int /*<<< orphan*/ ) ; 
 int RID_NUM_GPR ; 
 int RSET_SCRATCH ; 
 scalar_t__ emit_canremat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_isphi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 size_t ra_evict (TYPE_2__*,int) ; 
 size_t ra_gethint (scalar_t__) ; 
 scalar_t__ ra_hashint (scalar_t__) ; 
 int /*<<< orphan*/  ra_noreg (scalar_t__) ; 
 int /*<<< orphan*/  ra_noweak (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  ra_rematk (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcost_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_clear (int,size_t) ; 
 size_t rset_pickbot (int) ; 
 size_t rset_picktop (int) ; 
 scalar_t__ rset_test (int,size_t) ; 

__attribute__((used)) static Reg ra_allocref(ASMState *as, IRRef ref, RegSet allow)
{
  IRIns *ir = IR(ref);
  RegSet pick = as->freeset & allow;
  Reg r;
  lua_assert(ra_noreg(ir->r));
  if (pick) {
    /* First check register hint from propagation or PHI. */
    if (ra_hashint(ir->r)) {
      r = ra_gethint(ir->r);
      if (rset_test(pick, r))  /* Use hint register if possible. */
	goto found;
      /* Rematerialization is cheaper than missing a hint. */
      if (rset_test(allow, r) && emit_canremat(regcost_ref(as->cost[r]))) {
	ra_rematk(as, regcost_ref(as->cost[r]));
	goto found;
      }
      RA_DBGX((as, "hintmiss  $f $r", ref, r));
    }
    /* Invariants should preferably get unmodified registers. */
    if (ref < as->loopref && !irt_isphi(ir->t)) {
      if ((pick & ~as->modset))
	pick &= ~as->modset;
      r = rset_pickbot(pick);  /* Reduce conflicts with inverse allocation. */
    } else {
      /* We've got plenty of regs, so get callee-save regs if possible. */
      if (RID_NUM_GPR > 8 && (pick & ~RSET_SCRATCH))
	pick &= ~RSET_SCRATCH;
      r = rset_picktop(pick);
    }
  } else {
    r = ra_evict(as, allow);
  }
found:
  RA_DBGX((as, "alloc     $f $r", ref, r));
  ir->r = (uint8_t)r;
  rset_clear(as->freeset, r);
  ra_noweak(as, r);
  as->cost[r] = REGCOST_REF_T(ref, irt_t(ir->t));
  return r;
}