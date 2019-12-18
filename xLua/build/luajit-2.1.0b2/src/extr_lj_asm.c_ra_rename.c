#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
struct TYPE_14__ {TYPE_1__* T; int /*<<< orphan*/  ir; int /*<<< orphan*/  J; int /*<<< orphan*/  snapno; scalar_t__* cost; int /*<<< orphan*/  freeset; } ;
struct TYPE_13__ {int /*<<< orphan*/  s; void* r; } ;
struct TYPE_12__ {int /*<<< orphan*/  ir; } ;
typedef  size_t Reg ;
typedef  int /*<<< orphan*/  IRRef ;
typedef  TYPE_2__ IRIns ;
typedef  TYPE_3__ ASMState ;

/* Variables and functions */
 TYPE_2__* IR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRT_NIL ; 
 int /*<<< orphan*/  IR_RENAME ; 
 int /*<<< orphan*/  RA_DBGX (TYPE_3__*) ; 
 size_t RID_MAX_GPR ; 
 int /*<<< orphan*/  SPS_NONE ; 
 int /*<<< orphan*/  emit_movrr (TYPE_3__*,TYPE_2__*,size_t,size_t) ; 
 int /*<<< orphan*/  lj_ir_emit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  ra_free (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  ra_hasspill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_modified (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  ra_noweak (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  regcost_ref (scalar_t__) ; 
 int /*<<< orphan*/  rset_clear (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ rset_test (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  tref_ref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ra_rename(ASMState *as, Reg down, Reg up)
{
  IRRef ren, ref = regcost_ref(as->cost[up] = as->cost[down]);
  IRIns *ir = IR(ref);
  ir->r = (uint8_t)up;
  as->cost[down] = 0;
  lua_assert((down < RID_MAX_GPR) == (up < RID_MAX_GPR));
  lua_assert(!rset_test(as->freeset, down) && rset_test(as->freeset, up));
  ra_free(as, down);  /* 'down' is free ... */
  ra_modified(as, down);
  rset_clear(as->freeset, up);  /* ... and 'up' is now allocated. */
  ra_noweak(as, up);
  RA_DBGX((as, "rename    $f $r $r", regcost_ref(as->cost[up]), down, up));
  emit_movrr(as, ir, down, up);  /* Backwards codegen needs inverse move. */
  if (!ra_hasspill(IR(ref)->s)) {  /* Add the rename to the IR. */
    lj_ir_set(as->J, IRT(IR_RENAME, IRT_NIL), ref, as->snapno);
    ren = tref_ref(lj_ir_emit(as->J));
    as->ir = as->T->ir;  /* The IR may have been reallocated. */
    IR(ren)->r = (uint8_t)down;
    IR(ren)->s = SPS_NONE;
  }
}