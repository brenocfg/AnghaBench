#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int flags; int o; scalar_t__ r; int /*<<< orphan*/  op1; int /*<<< orphan*/  curins; int /*<<< orphan*/ * flagmcp; } ;
typedef  int /*<<< orphan*/  Reg ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_1__ ASMState ;

/* Variables and functions */
#define  IR_ADD 133 
#define  IR_CALLN 132 
#define  IR_CALLXS 131 
#define  IR_CNEWI 130 
 int IR_CONV ; 
 int IR_NE ; 
#define  IR_NEG 129 
#define  IR_SUB 128 
 int IR_XSTORE ; 
 int JIT_F_OPT_DCE ; 
 scalar_t__ LJ_UNLIKELY (int) ; 
 int /*<<< orphan*/  RID2RSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RID_RETLO ; 
 scalar_t__ RID_SINK ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int /*<<< orphan*/  UNUSED (TYPE_1__*) ; 
 int /*<<< orphan*/  XO_ARITHi8 ; 
 int /*<<< orphan*/  XO_GROUP3 ; 
 int /*<<< orphan*/  XOg_ADC ; 
 int /*<<< orphan*/  XOg_ADD ; 
 int /*<<< orphan*/  XOg_NEG ; 
 int /*<<< orphan*/  XOg_SBB ; 
 int /*<<< orphan*/  XOg_SUB ; 
 int /*<<< orphan*/  asm_comp_int64 (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_conv64 (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_fxstore (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_intarith (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_neg_not (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_i8 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_rr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_allocref (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_dest (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_left (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ra_used (TYPE_1__*) ; 

__attribute__((used)) static void asm_hiop(ASMState *as, IRIns *ir)
{
#if LJ_32 && LJ_HASFFI
  /* HIOP is marked as a store because it needs its own DCE logic. */
  int uselo = ra_used(ir-1), usehi = ra_used(ir);  /* Loword/hiword used? */
  if (LJ_UNLIKELY(!(as->flags & JIT_F_OPT_DCE))) uselo = usehi = 1;
  if ((ir-1)->o == IR_CONV) {  /* Conversions to/from 64 bit. */
    as->curins--;  /* Always skip the CONV. */
    if (usehi || uselo)
      asm_conv64(as, ir);
    return;
  } else if ((ir-1)->o <= IR_NE) {  /* 64 bit integer comparisons. ORDER IR. */
    asm_comp_int64(as, ir);
    return;
  } else if ((ir-1)->o == IR_XSTORE) {
    if ((ir-1)->r != RID_SINK)
      asm_fxstore(as, ir);
    return;
  }
  if (!usehi) return;  /* Skip unused hiword op for all remaining ops. */
  switch ((ir-1)->o) {
  case IR_ADD:
    as->flagmcp = NULL;
    as->curins--;
    asm_intarith(as, ir, XOg_ADC);
    asm_intarith(as, ir-1, XOg_ADD);
    break;
  case IR_SUB:
    as->flagmcp = NULL;
    as->curins--;
    asm_intarith(as, ir, XOg_SBB);
    asm_intarith(as, ir-1, XOg_SUB);
    break;
  case IR_NEG: {
    Reg dest = ra_dest(as, ir, RSET_GPR);
    emit_rr(as, XO_GROUP3, XOg_NEG, dest);
    emit_i8(as, 0);
    emit_rr(as, XO_ARITHi8, XOg_ADC, dest);
    ra_left(as, dest, ir->op1);
    as->curins--;
    asm_neg_not(as, ir-1, XOg_NEG);
    break;
    }
  case IR_CALLN:
  case IR_CALLXS:
    if (!uselo)
      ra_allocref(as, ir->op1, RID2RSET(RID_RETLO));  /* Mark lo op as used. */
    break;
  case IR_CNEWI:
    /* Nothing to do here. Handled by CNEWI itself. */
    break;
  default: lua_assert(0); break;
  }
#else
  UNUSED(as); UNUSED(ir); lua_assert(0);  /* Unused on x64 or without FFI. */
#endif
}