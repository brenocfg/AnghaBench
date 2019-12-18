#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_24__ {scalar_t__ o; int /*<<< orphan*/  r; } ;
struct TYPE_23__ {int /*<<< orphan*/  J; } ;
struct TYPE_20__ {int /*<<< orphan*/  marked; } ;
struct TYPE_22__ {TYPE_1__ gch; } ;
struct TYPE_21__ {int /*<<< orphan*/  op2; int /*<<< orphan*/  op1; } ;
typedef  int /*<<< orphan*/  Reg ;
typedef  int /*<<< orphan*/  MCLabel ;
typedef  int /*<<< orphan*/  IRRef ;
typedef  TYPE_2__ IRIns ;
typedef  TYPE_3__ GCobj ;
typedef  int /*<<< orphan*/  CCallInfo ;
typedef  TYPE_4__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  ASMREF_TMP1 ; 
 int /*<<< orphan*/  CC_Z ; 
 int /*<<< orphan*/  GChead ; 
 int /*<<< orphan*/  GCupval ; 
 TYPE_9__* IR (int /*<<< orphan*/ ) ; 
 size_t IRCALL_lj_gc_barrieruv ; 
 scalar_t__ IR_UREFC ; 
 int /*<<< orphan*/  J2G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LJ_GC_BLACK ; 
 int /*<<< orphan*/  LJ_GC_WHITES ; 
 int RSET_GPR ; 
 int RSET_SCRATCH ; 
 int /*<<< orphan*/  XO_GROUP3b ; 
 int /*<<< orphan*/  XOg_TEST ; 
 int /*<<< orphan*/  asm_gencall (TYPE_4__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_i8 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label (TYPE_4__*) ; 
 int /*<<< orphan*/  emit_loada (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_rma (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_rmro (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  emit_sjcc (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* ir_kgc (TYPE_9__*) ; 
 scalar_t__ irref_isk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_ir_callinfo ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  marked ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_alloc1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_evictset (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ra_releasetmp (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_exclude (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tv ; 

__attribute__((used)) static void asm_obar(ASMState *as, IRIns *ir)
{
  const CCallInfo *ci = &lj_ir_callinfo[IRCALL_lj_gc_barrieruv];
  IRRef args[2];
  MCLabel l_end;
  Reg obj;
  /* No need for other object barriers (yet). */
  lua_assert(IR(ir->op1)->o == IR_UREFC);
  ra_evictset(as, RSET_SCRATCH);
  l_end = emit_label(as);
  args[0] = ASMREF_TMP1;  /* global_State *g */
  args[1] = ir->op1;      /* TValue *tv      */
  asm_gencall(as, ci, args);
  emit_loada(as, ra_releasetmp(as, ASMREF_TMP1), J2G(as->J));
  obj = IR(ir->op1)->r;
  emit_sjcc(as, CC_Z, l_end);
  emit_i8(as, LJ_GC_WHITES);
  if (irref_isk(ir->op2)) {
    GCobj *vp = ir_kgc(IR(ir->op2));
    emit_rma(as, XO_GROUP3b, XOg_TEST, &vp->gch.marked);
  } else {
    Reg val = ra_alloc1(as, ir->op2, rset_exclude(RSET_SCRATCH&RSET_GPR, obj));
    emit_rmro(as, XO_GROUP3b, XOg_TEST, val, (int32_t)offsetof(GChead, marked));
  }
  emit_sjcc(as, CC_Z, l_end);
  emit_i8(as, LJ_GC_BLACK);
  emit_rmro(as, XO_GROUP3b, XOg_TEST, obj,
	    (int32_t)offsetof(GCupval, marked)-(int32_t)offsetof(GCupval, tv));
}