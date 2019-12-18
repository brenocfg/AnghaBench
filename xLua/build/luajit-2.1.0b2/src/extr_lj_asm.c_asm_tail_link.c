#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_16__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_21__ {int /*<<< orphan*/  const startins; } ;
struct TYPE_20__ {int freeset; int /*<<< orphan*/  topslot; int /*<<< orphan*/  parent; int /*<<< orphan*/  J; TYPE_1__* T; } ;
struct TYPE_19__ {size_t mapofs; size_t nent; scalar_t__ nslots; int /*<<< orphan*/  topslot; } ;
struct TYPE_18__ {size_t nsnap; scalar_t__ link; int /*<<< orphan*/ * snapmap; TYPE_2__* snap; } ;
struct TYPE_17__ {int /*<<< orphan*/  const* dispatch; } ;
typedef  TYPE_2__ SnapShot ;
typedef  size_t SnapNo ;
typedef  scalar_t__ BCReg ;
typedef  int /*<<< orphan*/  const BCIns ;
typedef  TYPE_3__ ASMState ;

/* Variables and functions */
#define  BC_CALLM 131 
#define  BC_CALLMT 130 
 int BC_FUNCF ; 
 int BC_JLOOP ; 
#define  BC_RETM 129 
#define  BC_TSETM 128 
 TYPE_16__* J2GG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LJ_FR2 ; 
 int /*<<< orphan*/  REF_BASE ; 
 int /*<<< orphan*/  RID2RSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RID_BASE ; 
 int /*<<< orphan*/  RID_DISPATCH ; 
 int /*<<< orphan*/  RID_LPC ; 
 int /*<<< orphan*/  RID_RET ; 
 int RSET_GPR ; 
 scalar_t__ asm_baseslot (TYPE_3__*,TYPE_2__*,int*) ; 
 int /*<<< orphan*/  asm_stack_check (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  asm_stack_restore (TYPE_3__*,TYPE_2__*) ; 
 scalar_t__ bc_a (int /*<<< orphan*/  const) ; 
 scalar_t__ bc_c (int /*<<< orphan*/  const) ; 
 scalar_t__ bc_d (int /*<<< orphan*/  const) ; 
 scalar_t__ bc_isret (int) ; 
 int bc_op (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  checkmclim (TYPE_3__*) ; 
 int /*<<< orphan*/  emit_addptr (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_setgl (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i32ptr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  jit_base ; 
 int /*<<< orphan*/  ra_allockreg (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_allocref (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* snap_pc (int /*<<< orphan*/ ) ; 
 TYPE_4__* traceref (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void asm_tail_link(ASMState *as)
{
  SnapNo snapno = as->T->nsnap-1;  /* Last snapshot. */
  SnapShot *snap = &as->T->snap[snapno];
  int gotframe = 0;
  BCReg baseslot = asm_baseslot(as, snap, &gotframe);

  as->topslot = snap->topslot;
  checkmclim(as);
  ra_allocref(as, REF_BASE, RID2RSET(RID_BASE));

  if (as->T->link == 0) {
    /* Setup fixed registers for exit to interpreter. */
    const BCIns *pc = snap_pc(as->T->snapmap[snap->mapofs + snap->nent]);
    int32_t mres;
    if (bc_op(*pc) == BC_JLOOP) {  /* NYI: find a better way to do this. */
      BCIns *retpc = &traceref(as->J, bc_d(*pc))->startins;
      if (bc_isret(bc_op(*retpc)))
	pc = retpc;
    }
    ra_allockreg(as, i32ptr(J2GG(as->J)->dispatch), RID_DISPATCH);
    ra_allockreg(as, i32ptr(pc), RID_LPC);
    mres = (int32_t)(snap->nslots - baseslot);
    switch (bc_op(*pc)) {
    case BC_CALLM: case BC_CALLMT:
      mres -= (int32_t)(1 + LJ_FR2 + bc_a(*pc) + bc_c(*pc)); break;
    case BC_RETM: mres -= (int32_t)(bc_a(*pc) + bc_d(*pc)); break;
    case BC_TSETM: mres -= (int32_t)bc_a(*pc); break;
    default: if (bc_op(*pc) < BC_FUNCF) mres = 0; break;
    }
    ra_allockreg(as, mres, RID_RET);  /* Return MULTRES or 0. */
  } else if (baseslot) {
    /* Save modified BASE for linking to trace with higher start frame. */
    emit_setgl(as, RID_BASE, jit_base);
  }
  emit_addptr(as, RID_BASE, 8*(int32_t)baseslot);

  /* Sync the interpreter state with the on-trace state. */
  asm_stack_restore(as, snap);

  /* Root traces that add frames need to check the stack at the end. */
  if (!as->parent && gotframe)
    asm_stack_check(as, as->topslot, NULL, as->freeset & RSET_GPR, snapno);
}