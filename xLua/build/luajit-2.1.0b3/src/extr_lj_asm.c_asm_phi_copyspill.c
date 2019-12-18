#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int freeset; int /*<<< orphan*/ * cost; scalar_t__ orignins; } ;
struct TYPE_10__ {scalar_t__ o; int /*<<< orphan*/  s; int /*<<< orphan*/  t; scalar_t__ op1; } ;
typedef  size_t Reg ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 TYPE_1__* IR (scalar_t__) ; 
 scalar_t__ IR_PHI ; 
 size_t RID_FPRET ; 
 size_t RID_RET ; 
 size_t RID_TMP ; 
 size_t RID_XMM0 ; 
 int RSET_FPR ; 
 int RSET_GPR ; 
 int /*<<< orphan*/  SPOFS_TMP ; 
 int /*<<< orphan*/  checkmclim (TYPE_2__*) ; 
 int /*<<< orphan*/  emit_spload (TYPE_2__*,TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_spstore (TYPE_2__*,TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isfp (int /*<<< orphan*/ ) ; 
 scalar_t__ ra_hasspill (int /*<<< orphan*/ ) ; 
 scalar_t__ regcost_ref (int /*<<< orphan*/ ) ; 
 size_t rset_pickbot (int) ; 
 int /*<<< orphan*/  rset_test (int,size_t) ; 
 int /*<<< orphan*/  sps_scale (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asm_phi_copyspill(ASMState *as)
{
  int need = 0;
  IRIns *ir;
  for (ir = IR(as->orignins-1); ir->o == IR_PHI; ir--)
    if (ra_hasspill(ir->s) && ra_hasspill(IR(ir->op1)->s))
      need |= irt_isfp(ir->t) ? 2 : 1;  /* Unsynced spill slot? */
  if ((need & 1)) {  /* Copy integer spill slots. */
#if !LJ_TARGET_X86ORX64
    Reg r = RID_TMP;
#else
    Reg r = RID_RET;
    if ((as->freeset & RSET_GPR))
      r = rset_pickbot((as->freeset & RSET_GPR));
    else
      emit_spload(as, IR(regcost_ref(as->cost[r])), r, SPOFS_TMP);
#endif
    for (ir = IR(as->orignins-1); ir->o == IR_PHI; ir--) {
      if (ra_hasspill(ir->s)) {
	IRIns *irl = IR(ir->op1);
	if (ra_hasspill(irl->s) && !irt_isfp(ir->t)) {
	  emit_spstore(as, irl, r, sps_scale(irl->s));
	  emit_spload(as, ir, r, sps_scale(ir->s));
	  checkmclim(as);
	}
      }
    }
#if LJ_TARGET_X86ORX64
    if (!rset_test(as->freeset, r))
      emit_spstore(as, IR(regcost_ref(as->cost[r])), r, SPOFS_TMP);
#endif
  }
#if !LJ_SOFTFP
  if ((need & 2)) {  /* Copy FP spill slots. */
#if LJ_TARGET_X86
    Reg r = RID_XMM0;
#else
    Reg r = RID_FPRET;
#endif
    if ((as->freeset & RSET_FPR))
      r = rset_pickbot((as->freeset & RSET_FPR));
    if (!rset_test(as->freeset, r))
      emit_spload(as, IR(regcost_ref(as->cost[r])), r, SPOFS_TMP);
    for (ir = IR(as->orignins-1); ir->o == IR_PHI; ir--) {
      if (ra_hasspill(ir->s)) {
	IRIns *irl = IR(ir->op1);
	if (ra_hasspill(irl->s) && irt_isfp(ir->t)) {
	  emit_spstore(as, irl, r, sps_scale(irl->s));
	  emit_spload(as, ir, r, sps_scale(ir->s));
	  checkmclim(as);
	}
      }
    }
    if (!rset_test(as->freeset, r))
      emit_spstore(as, IR(regcost_ref(as->cost[r])), r, SPOFS_TMP);
  }
#endif
}