#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_21__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_29__ {scalar_t__ root; int /*<<< orphan*/  startins; int /*<<< orphan*/  startpc; int /*<<< orphan*/  nk; } ;
struct TYPE_24__ {int /*<<< orphan*/  pc; scalar_t__ idx; } ;
struct TYPE_30__ {scalar_t__ instunroll; scalar_t__* param; scalar_t__ loopunroll; scalar_t__ parent; size_t exitno; int prev_line; int /*<<< orphan*/ * prev_pt; TYPE_12__* pt; int /*<<< orphan*/ * startpc; TYPE_3__ cur; TYPE_11__ scev; int /*<<< orphan*/ * pc; int /*<<< orphan*/  bc_extent; int /*<<< orphan*/ * bc_min; scalar_t__ loopref; scalar_t__ tailcalled; scalar_t__ retdepth; scalar_t__ framedepth; scalar_t__ maxslot; scalar_t__ baseslot; scalar_t__ slot; scalar_t__ base; scalar_t__ bpropcache; scalar_t__ rbchash; scalar_t__ chain; } ;
typedef  TYPE_4__ jit_State ;
typedef  scalar_t__ TraceNo ;
struct TYPE_32__ {scalar_t__ root; scalar_t__ nchild; TYPE_2__* snap; } ;
struct TYPE_26__ {scalar_t__ irt; } ;
struct TYPE_31__ {scalar_t__ prev; int /*<<< orphan*/  o; TYPE_1__ t; scalar_t__ i; } ;
struct TYPE_28__ {scalar_t__ nent; scalar_t__ count; } ;
struct TYPE_27__ {int /*<<< orphan*/  hookmask; } ;
struct TYPE_25__ {scalar_t__ framesize; } ;
typedef  int /*<<< orphan*/  TRef ;
typedef  int /*<<< orphan*/  MSize ;
typedef  TYPE_5__ IRIns ;
typedef  TYPE_6__ GCtrace ;

/* Variables and functions */
 int /*<<< orphan*/  BCINS_AD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BC_FORL ; 
 scalar_t__ BC_ITERC ; 
 scalar_t__ BC_JFORI ; 
 int /*<<< orphan*/  BC_JMP ; 
 TYPE_5__* IR (scalar_t__) ; 
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTGI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTI (int /*<<< orphan*/ ) ; 
 scalar_t__ IRT_NIL ; 
 int /*<<< orphan*/  IRT_PGC ; 
 int /*<<< orphan*/  IRT_U8 ; 
 int /*<<< orphan*/  IRXLOAD_VOLATILE ; 
 int /*<<< orphan*/  IR_BAND ; 
 int /*<<< orphan*/  IR_BASE ; 
 int /*<<< orphan*/  IR_EQ ; 
 int /*<<< orphan*/  IR_KPRI ; 
 int /*<<< orphan*/  IR_XLOAD ; 
 TYPE_21__* J2G (TYPE_4__*) ; 
 size_t JIT_P_hotexit ; 
 size_t JIT_P_instunroll ; 
 size_t JIT_P_loopunroll ; 
 size_t JIT_P_maxside ; 
 size_t JIT_P_tryside ; 
 scalar_t__ LJ_FR2 ; 
 scalar_t__ LJ_MAX_JSLOTS ; 
 int /*<<< orphan*/  LJ_TRERR_STACKOV ; 
 int /*<<< orphan*/  LJ_TRLINK_INTERP ; 
 int LUA_MASKCOUNT ; 
 int LUA_MASKLINE ; 
 scalar_t__ REF_NIL ; 
 int /*<<< orphan*/  REF_TRUE ; 
 scalar_t__ bc_d (int /*<<< orphan*/ ) ; 
 int bc_j (int /*<<< orphan*/ ) ; 
 scalar_t__ bc_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitir_raw (int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int /*<<< orphan*/  lj_ir_kint (TYPE_4__*,int) ; 
 int /*<<< orphan*/  lj_ir_kptr (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_record_stop (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_snap_add (TYPE_4__*) ; 
 int /*<<< orphan*/  lj_snap_replay (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * proto_bc (TYPE_12__*) ; 
 int /*<<< orphan*/  rec_for_loop (TYPE_4__*,int /*<<< orphan*/ *,TYPE_11__*,int) ; 
 int /*<<< orphan*/ * rec_setup_root (TYPE_4__*) ; 
 int /*<<< orphan*/  setmref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_6__* traceref (TYPE_4__*,scalar_t__) ; 

void lj_record_setup(jit_State *J)
{
  uint32_t i;

  /* Initialize state related to current trace. */
  memset(J->slot, 0, sizeof(J->slot));
  memset(J->chain, 0, sizeof(J->chain));
#ifdef LUAJIT_ENABLE_TABLE_BUMP
  memset(J->rbchash, 0, sizeof(J->rbchash));
#endif
  memset(J->bpropcache, 0, sizeof(J->bpropcache));
  J->scev.idx = REF_NIL;
  setmref(J->scev.pc, NULL);

  J->baseslot = 1+LJ_FR2;  /* Invoking function is at base[-1-LJ_FR2]. */
  J->base = J->slot + J->baseslot;
  J->maxslot = 0;
  J->framedepth = 0;
  J->retdepth = 0;

  J->instunroll = J->param[JIT_P_instunroll];
  J->loopunroll = J->param[JIT_P_loopunroll];
  J->tailcalled = 0;
  J->loopref = 0;

  J->bc_min = NULL;  /* Means no limit. */
  J->bc_extent = ~(MSize)0;

  /* Emit instructions for fixed references. Also triggers initial IR alloc. */
  emitir_raw(IRT(IR_BASE, IRT_PGC), J->parent, J->exitno);
  for (i = 0; i <= 2; i++) {
    IRIns *ir = IR(REF_NIL-i);
    ir->i = 0;
    ir->t.irt = (uint8_t)(IRT_NIL+i);
    ir->o = IR_KPRI;
    ir->prev = 0;
  }
  J->cur.nk = REF_TRUE;

  J->startpc = J->pc;
  setmref(J->cur.startpc, J->pc);
  if (J->parent) {  /* Side trace. */
    GCtrace *T = traceref(J, J->parent);
    TraceNo root = T->root ? T->root : J->parent;
    J->cur.root = (uint16_t)root;
    J->cur.startins = BCINS_AD(BC_JMP, 0, 0);
    /* Check whether we could at least potentially form an extra loop. */
    if (J->exitno == 0 && T->snap[0].nent == 0) {
      /* We can narrow a FORL for some side traces, too. */
      if (J->pc > proto_bc(J->pt) && bc_op(J->pc[-1]) == BC_JFORI &&
	  bc_d(J->pc[bc_j(J->pc[-1])-1]) == root) {
	lj_snap_add(J);
	rec_for_loop(J, J->pc-1, &J->scev, 1);
	goto sidecheck;
      }
    } else {
      J->startpc = NULL;  /* Prevent forming an extra loop. */
    }
    lj_snap_replay(J, T);
  sidecheck:
    if (traceref(J, J->cur.root)->nchild >= J->param[JIT_P_maxside] ||
	T->snap[J->exitno].count >= J->param[JIT_P_hotexit] +
				    J->param[JIT_P_tryside]) {
      lj_record_stop(J, LJ_TRLINK_INTERP, 0);
    }
  } else {  /* Root trace. */
    J->cur.root = 0;
    J->cur.startins = *J->pc;
    J->pc = rec_setup_root(J);
    /* Note: the loop instruction itself is recorded at the end and not
    ** at the start! So snapshot #0 needs to point to the *next* instruction.
    */
    lj_snap_add(J);
    if (bc_op(J->cur.startins) == BC_FORL)
      rec_for_loop(J, J->pc-1, &J->scev, 1);
    else if (bc_op(J->cur.startins) == BC_ITERC)
      J->startpc = NULL;
    if (1 + J->pt->framesize >= LJ_MAX_JSLOTS)
      lj_trace_err(J, LJ_TRERR_STACKOV);
  }
#if LJ_HASPROFILE
  J->prev_pt = NULL;
  J->prev_line = -1;
#endif
#ifdef LUAJIT_ENABLE_CHECKHOOK
  /* Regularly check for instruction/line hooks from compiled code and
  ** exit to the interpreter if the hooks are set.
  **
  ** This is a compile-time option and disabled by default, since the
  ** hook checks may be quite expensive in tight loops.
  **
  ** Note this is only useful if hooks are *not* set most of the time.
  ** Use this only if you want to *asynchronously* interrupt the execution.
  **
  ** You can set the instruction hook via lua_sethook() with a count of 1
  ** from a signal handler or another native thread. Please have a look
  ** at the first few functions in luajit.c for an example (Ctrl-C handler).
  */
  {
    TRef tr = emitir(IRT(IR_XLOAD, IRT_U8),
		     lj_ir_kptr(J, &J2G(J)->hookmask), IRXLOAD_VOLATILE);
    tr = emitir(IRTI(IR_BAND), tr, lj_ir_kint(J, (LUA_MASKLINE|LUA_MASKCOUNT)));
    emitir(IRTGI(IR_EQ), tr, lj_ir_kint(J, 0));
  }
#endif
}