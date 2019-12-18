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
typedef  struct TYPE_32__   TYPE_26__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptrdiff_t ;
struct TYPE_33__ {scalar_t__ base; TYPE_4__* top; int /*<<< orphan*/  maxstack; int /*<<< orphan*/  cframe; } ;
typedef  TYPE_2__ lua_State ;
struct TYPE_34__ {size_t exitno; TYPE_2__* L; int /*<<< orphan*/  parent; } ;
typedef  TYPE_3__ jit_State ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_38__ {int* snapmap; TYPE_6__* ir; TYPE_5__* snap; } ;
struct TYPE_37__ {scalar_t__ r; } ;
struct TYPE_36__ {size_t nent; size_t mapofs; int topslot; int /*<<< orphan*/  nslots; } ;
struct TYPE_31__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct TYPE_35__ {TYPE_1__ u32; } ;
struct TYPE_32__ {int framesize; } ;
typedef  TYPE_4__ TValue ;
typedef  TYPE_5__ SnapShot ;
typedef  size_t SnapNo ;
typedef  int SnapEntry ;
typedef  size_t MSize ;
typedef  size_t IRRef ;
typedef  TYPE_6__ IRIns ;
typedef  TYPE_7__ GCtrace ;
typedef  int /*<<< orphan*/  ExitState ;
typedef  int /*<<< orphan*/  BloomFilter ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
#define  BC_CALLM 131 
#define  BC_CALLMT 130 
 int BC_FUNCF ; 
#define  BC_RETM 129 
#define  BC_TSETM 128 
 int /*<<< orphan*/  LJ_FR2 ; 
 scalar_t__ LJ_SOFTFP ; 
 scalar_t__ LJ_UNLIKELY (int) ; 
 scalar_t__ RID_SUNK ; 
 int SNAP_CONT ; 
 int SNAP_FRAME ; 
 int SNAP_NORESTORE ; 
 int SNAP_SOFTFPNUM ; 
 int bc_op (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  cframe_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copyTV (TYPE_2__*,TYPE_4__*,TYPE_4__*) ; 
 TYPE_26__* curr_proto (TYPE_2__*) ; 
 void* curr_topL (TYPE_2__*) ; 
 int /*<<< orphan*/  frame_ftsz (TYPE_4__*) ; 
 int /*<<< orphan*/  lj_state_growstack (TYPE_2__*,int) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  setcframe_pc (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  setframe_ftsz (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int snap_nextofs (TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/ * snap_pc (int) ; 
 size_t snap_ref (int) ; 
 int /*<<< orphan*/  snap_renamefilter (TYPE_7__*,size_t) ; 
 int /*<<< orphan*/  snap_restoreval (TYPE_3__*,TYPE_7__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,size_t,TYPE_4__*) ; 
 size_t snap_slot (int) ; 
 int /*<<< orphan*/  snap_unsink (TYPE_3__*,TYPE_7__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,TYPE_6__*,TYPE_4__*) ; 
 TYPE_7__* traceref (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ tvisint (TYPE_4__*) ; 
 scalar_t__ tvref (int /*<<< orphan*/ ) ; 

const BCIns *lj_snap_restore(jit_State *J, void *exptr)
{
  ExitState *ex = (ExitState *)exptr;
  SnapNo snapno = J->exitno;  /* For now, snapno == exitno. */
  GCtrace *T = traceref(J, J->parent);
  SnapShot *snap = &T->snap[snapno];
  MSize n, nent = snap->nent;
  SnapEntry *map = &T->snapmap[snap->mapofs];
  SnapEntry *flinks = &T->snapmap[snap_nextofs(T, snap)-1];
  ptrdiff_t ftsz0;
  TValue *frame;
  BloomFilter rfilt = snap_renamefilter(T, snapno);
  const BCIns *pc = snap_pc(map[nent]);
  lua_State *L = J->L;

  /* Set interpreter PC to the next PC to get correct error messages. */
  setcframe_pc(cframe_raw(L->cframe), pc+1);

  /* Make sure the stack is big enough for the slots from the snapshot. */
  if (LJ_UNLIKELY(L->base + snap->topslot >= tvref(L->maxstack))) {
    L->top = curr_topL(L);
    lj_state_growstack(L, snap->topslot - curr_proto(L)->framesize);
  }

  /* Fill stack slots with data from the registers and spill slots. */
  frame = L->base-1;
  ftsz0 = frame_ftsz(frame);  /* Preserve link to previous frame in slot #0. */
  for (n = 0; n < nent; n++) {
    SnapEntry sn = map[n];
    if (!(sn & SNAP_NORESTORE)) {
      TValue *o = &frame[snap_slot(sn)];
      IRRef ref = snap_ref(sn);
      IRIns *ir = &T->ir[ref];
      if (ir->r == RID_SUNK) {
	MSize j;
	for (j = 0; j < n; j++)
	  if (snap_ref(map[j]) == ref) {  /* De-duplicate sunk allocations. */
	    copyTV(L, o, &frame[snap_slot(map[j])]);
	    goto dupslot;
	  }
	snap_unsink(J, T, ex, snapno, rfilt, ir, o);
      dupslot:
	continue;
      }
      snap_restoreval(J, T, ex, snapno, rfilt, ref, o);
      if (LJ_SOFTFP && (sn & SNAP_SOFTFPNUM) && tvisint(o)) {
	TValue tmp;
	snap_restoreval(J, T, ex, snapno, rfilt, ref+1, &tmp);
	o->u32.hi = tmp.u32.lo;
      } else if ((sn & (SNAP_CONT|SNAP_FRAME))) {
	lua_assert(!LJ_FR2);  /* TODO_FR2: store 64 bit PCs. */
	/* Overwrite tag with frame link. */
	setframe_ftsz(o, snap_slot(sn) != 0 ? (int32_t)*flinks-- : ftsz0);
	L->base = o+1;
      }
    }
  }
  lua_assert(map + nent == flinks);

  /* Compute current stack top. */
  switch (bc_op(*pc)) {
  default:
    if (bc_op(*pc) < BC_FUNCF) {
      L->top = curr_topL(L);
      break;
    }
    /* fallthrough */
  case BC_CALLM: case BC_CALLMT: case BC_RETM: case BC_TSETM:
    L->top = frame + snap->nslots;
    break;
  }
  return pc;
}