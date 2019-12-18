#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  total; int /*<<< orphan*/  threshold; } ;
struct TYPE_16__ {scalar_t__ gcsteps; int /*<<< orphan*/  J; } ;
typedef  int /*<<< orphan*/  Reg ;
typedef  int /*<<< orphan*/  MCLabel ;
typedef  int /*<<< orphan*/  IRRef ;
typedef  int /*<<< orphan*/  CCallInfo ;
typedef  TYPE_1__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  ASMREF_TMP1 ; 
 int /*<<< orphan*/  ASMREF_TMP2 ; 
 int /*<<< orphan*/  CC_B ; 
 int /*<<< orphan*/  CC_NE ; 
 size_t IRCALL_lj_gc_step_jit ; 
 int /*<<< orphan*/  J2G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RID_RET ; 
 int /*<<< orphan*/  RSET_SCRATCH ; 
 int /*<<< orphan*/  XO_ARITH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XO_TEST ; 
 int /*<<< orphan*/  XOg_CMP ; 
 int /*<<< orphan*/  asm_gencall (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asm_guardcc (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checkmclim (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_getgl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_loada (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_loadi (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  emit_opgl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_rr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_sjcc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ gc ; 
 int /*<<< orphan*/ * lj_ir_callinfo ; 
 int /*<<< orphan*/  ra_evictset (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_releasetmp (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asm_gc_check(ASMState *as)
{
  const CCallInfo *ci = &lj_ir_callinfo[IRCALL_lj_gc_step_jit];
  IRRef args[2];
  MCLabel l_end;
  Reg tmp;
  ra_evictset(as, RSET_SCRATCH);
  l_end = emit_label(as);
  /* Exit trace if in GCSatomic or GCSfinalize. Avoids syncing GC objects. */
  asm_guardcc(as, CC_NE);  /* Assumes asm_snap_prep() already done. */
  emit_rr(as, XO_TEST, RID_RET, RID_RET);
  args[0] = ASMREF_TMP1;  /* global_State *g */
  args[1] = ASMREF_TMP2;  /* MSize steps     */
  asm_gencall(as, ci, args);
  tmp = ra_releasetmp(as, ASMREF_TMP1);
  emit_loada(as, tmp, J2G(as->J));
  emit_loadi(as, ra_releasetmp(as, ASMREF_TMP2), as->gcsteps);
  /* Jump around GC step if GC total < GC threshold. */
  emit_sjcc(as, CC_B, l_end);
  emit_opgl(as, XO_ARITH(XOg_CMP), tmp, gc.threshold);
  emit_getgl(as, tmp, gc.total);
  as->gcsteps = 0;
  checkmclim(as);
}