#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_20__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_18__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_27__ {scalar_t__ ktrace; int /*<<< orphan*/  curfinal; } ;
struct TYPE_26__ {int /*<<< orphan*/  const startins; } ;
struct TYPE_25__ {int freeset; int /*<<< orphan*/  topslot; int /*<<< orphan*/  parent; TYPE_5__* J; TYPE_1__* T; } ;
struct TYPE_24__ {size_t mapofs; size_t nent; scalar_t__ nslots; int /*<<< orphan*/  topslot; } ;
struct TYPE_23__ {int /*<<< orphan*/  o; int /*<<< orphan*/  gcr; } ;
struct TYPE_22__ {size_t nsnap; scalar_t__ link; int /*<<< orphan*/ * snapmap; TYPE_2__* snap; } ;
struct TYPE_21__ {int /*<<< orphan*/  const* dispatch; } ;
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
 TYPE_20__* IR (scalar_t__) ; 
 int /*<<< orphan*/  IR_KGC ; 
 TYPE_18__* J2GG (TYPE_5__*) ; 
 scalar_t__ LJ_FR2 ; 
 size_t LJ_GC64 ; 
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
 int /*<<< orphan*/  emit_loadu64 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_setgl (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i32ptr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  jit_base ; 
 int /*<<< orphan*/  obj2gco (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_allockreg (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_allocref (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* snap_pc (int /*<<< orphan*/ *) ; 
 TYPE_4__* traceref (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  u64ptr (int /*<<< orphan*/  const*) ; 

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
    const BCIns *pc = snap_pc(&as->T->snapmap[snap->mapofs + snap->nent]);
    int32_t mres;
    if (bc_op(*pc) == BC_JLOOP) {  /* NYI: find a better way to do this. */
      BCIns *retpc = &traceref(as->J, bc_d(*pc))->startins;
      if (bc_isret(bc_op(*retpc)))
	pc = retpc;
    }
#if LJ_GC64
    emit_loadu64(as, RID_LPC, u64ptr(pc));
#else
    ra_allockreg(as, i32ptr(J2GG(as->J)->dispatch), RID_DISPATCH);
    ra_allockreg(as, i32ptr(pc), RID_LPC);
#endif
    mres = (int32_t)(snap->nslots - baseslot - LJ_FR2);
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

  if (as->J->ktrace) {  /* Patch ktrace slot with the final GCtrace pointer. */
    setgcref(IR(as->J->ktrace)[LJ_GC64].gcr, obj2gco(as->J->curfinal));
    IR(as->J->ktrace)->o = IR_KGC;
  }

  /* Sync the interpreter state with the on-trace state. */
  asm_stack_restore(as, snap);

  /* Root traces that add frames need to check the stack at the end. */
  if (!as->parent && gotframe)
    asm_stack_check(as, as->topslot, NULL, as->freeset & RSET_GPR, snapno);
}