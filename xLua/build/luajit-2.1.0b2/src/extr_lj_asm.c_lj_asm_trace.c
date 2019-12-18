#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;

/* Type definitions */
struct TYPE_33__ {size_t nins; TYPE_1__* ir; } ;
struct TYPE_35__ {int flags; scalar_t__ parent; int /*<<< orphan*/  loopref; TYPE_2__ cur; } ;
typedef  TYPE_4__ jit_State ;
struct TYPE_38__ {int flags; scalar_t__ curins; scalar_t__ gcsteps; scalar_t__ stopins; scalar_t__ freeset; int /*<<< orphan*/ * mcp; int /*<<< orphan*/ * mctop; int /*<<< orphan*/  loopref; int /*<<< orphan*/ * mcloop; TYPE_4__* J; int /*<<< orphan*/ * parent; TYPE_6__* T; int /*<<< orphan*/  fuseref; int /*<<< orphan*/  sectref; scalar_t__ topslot; int /*<<< orphan*/ * flagmcp; int /*<<< orphan*/ * mcp_prev; int /*<<< orphan*/ * realign; scalar_t__ mcbot; scalar_t__ mclim; scalar_t__ loopinv; int /*<<< orphan*/  ir; } ;
struct TYPE_37__ {scalar_t__ nins; int /*<<< orphan*/ * mcode; void* szmcode; int /*<<< orphan*/  link; void* mcloop; TYPE_3__* snap; int /*<<< orphan*/  ir; } ;
struct TYPE_36__ {int /*<<< orphan*/  t; } ;
struct TYPE_34__ {scalar_t__ ref; } ;
struct TYPE_32__ {int /*<<< orphan*/  o; } ;
typedef  void* MSize ;
typedef  int /*<<< orphan*/  MCode ;
typedef  TYPE_5__ IRIns ;
typedef  TYPE_6__ GCtrace ;
typedef  TYPE_7__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_DISABLED ; 
 TYPE_5__* IR (scalar_t__) ; 
 int /*<<< orphan*/  IR_NOP ; 
 int JIT_F_OPT_DCE ; 
 int JIT_F_OPT_FUSE ; 
 scalar_t__ LJ_32 ; 
 int /*<<< orphan*/  LJ_TRERR_BADRA ; 
 scalar_t__ MCLIM_REDZONE ; 
 int /*<<< orphan*/  RA_DBGX (TYPE_7__*) ; 
 int /*<<< orphan*/  RA_DBG_FLUSH () ; 
 int /*<<< orphan*/  RA_DBG_REF () ; 
 int /*<<< orphan*/  RA_DBG_START () ; 
 scalar_t__ RSET_ALL ; 
 int /*<<< orphan*/  asm_gc_check (TYPE_7__*) ; 
 int /*<<< orphan*/  asm_head_root (TYPE_7__*) ; 
 int /*<<< orphan*/  asm_head_side (TYPE_7__*) ; 
 int /*<<< orphan*/  asm_ir (TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  asm_phi_fixup (TYPE_7__*) ; 
 int /*<<< orphan*/  asm_setup_regsp (TYPE_7__*) ; 
 int /*<<< orphan*/  asm_setup_target (TYPE_7__*) ; 
 int /*<<< orphan*/  asm_snap_prep (TYPE_7__*) ; 
 int /*<<< orphan*/  asm_tail_fixup (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_tail_link (TYPE_7__*) ; 
 int /*<<< orphan*/  asm_tail_prep (TYPE_7__*) ; 
 int /*<<< orphan*/  checkmclim (TYPE_7__*) ; 
 int /*<<< orphan*/  ir_sideeff (TYPE_5__*) ; 
 scalar_t__ irt_isguard (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isint64 (int /*<<< orphan*/ ) ; 
 size_t lj_ir_nextins (TYPE_4__*) ; 
 int /*<<< orphan*/ * lj_mcode_reserve (TYPE_4__*,scalar_t__*) ; 
 int /*<<< orphan*/  lj_mcode_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  ra_evictk (TYPE_7__*) ; 
 int /*<<< orphan*/  ra_used (TYPE_5__*) ; 
 int /*<<< orphan*/ * traceref (TYPE_4__*,scalar_t__) ; 

void lj_asm_trace(jit_State *J, GCtrace *T)
{
  ASMState as_;
  ASMState *as = &as_;
  MCode *origtop;

  /* Ensure an initialized instruction beyond the last one for HIOP checks. */
  J->cur.nins = lj_ir_nextins(J);
  J->cur.ir[J->cur.nins].o = IR_NOP;

  /* Setup initial state. Copy some fields to reduce indirections. */
  as->J = J;
  as->T = T;
  as->ir = T->ir;
  as->flags = J->flags;
  as->loopref = J->loopref;
  as->realign = NULL;
  as->loopinv = 0;
  as->parent = J->parent ? traceref(J, J->parent) : NULL;

  /* Reserve MCode memory. */
  as->mctop = origtop = lj_mcode_reserve(J, &as->mcbot);
  as->mcp = as->mctop;
  as->mclim = as->mcbot + MCLIM_REDZONE;
  asm_setup_target(as);

  do {
    as->mcp = as->mctop;
#ifdef LUA_USE_ASSERT
    as->mcp_prev = as->mcp;
#endif
    as->curins = T->nins;
    RA_DBG_START();
    RA_DBGX((as, "===== STOP ====="));

    /* General trace setup. Emit tail of trace. */
    asm_tail_prep(as);
    as->mcloop = NULL;
    as->flagmcp = NULL;
    as->topslot = 0;
    as->gcsteps = 0;
    as->sectref = as->loopref;
    as->fuseref = (as->flags & JIT_F_OPT_FUSE) ? as->loopref : FUSE_DISABLED;
    asm_setup_regsp(as);
    if (!as->loopref)
      asm_tail_link(as);

    /* Assemble a trace in linear backwards order. */
    for (as->curins--; as->curins > as->stopins; as->curins--) {
      IRIns *ir = IR(as->curins);
      lua_assert(!(LJ_32 && irt_isint64(ir->t)));  /* Handled by SPLIT. */
      if (!ra_used(ir) && !ir_sideeff(ir) && (as->flags & JIT_F_OPT_DCE))
	continue;  /* Dead-code elimination can be soooo easy. */
      if (irt_isguard(ir->t))
	asm_snap_prep(as);
      RA_DBG_REF();
      checkmclim(as);
      asm_ir(as, ir);
    }
  } while (as->realign);  /* Retry in case the MCode needs to be realigned. */

  /* Emit head of trace. */
  RA_DBG_REF();
  checkmclim(as);
  if (as->gcsteps > 0) {
    as->curins = as->T->snap[0].ref;
    asm_snap_prep(as);  /* The GC check is a guard. */
    asm_gc_check(as);
  }
  ra_evictk(as);
  if (as->parent)
    asm_head_side(as);
  else
    asm_head_root(as);
  asm_phi_fixup(as);

  RA_DBGX((as, "===== START ===="));
  RA_DBG_FLUSH();
  if (as->freeset != RSET_ALL)
    lj_trace_err(as->J, LJ_TRERR_BADRA);  /* Ouch! Should never happen. */

  /* Set trace entry point before fixing up tail to allow link to self. */
  T->mcode = as->mcp;
  T->mcloop = as->mcloop ? (MSize)((char *)as->mcloop - (char *)as->mcp) : 0;
  if (!as->loopref)
    asm_tail_fixup(as, T->link);  /* Note: this may change as->mctop! */
  T->szmcode = (MSize)((char *)as->mctop - (char *)as->mcp);
  lj_mcode_sync(T->mcode, origtop);
}