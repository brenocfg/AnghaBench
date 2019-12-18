#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_5__* ir; } ;
struct TYPE_10__ {int* chain; int* slot; TYPE_2__ cur; int /*<<< orphan*/  baseslot; TYPE_1__* L; } ;
typedef  TYPE_3__ jit_State ;
struct TYPE_11__ {int /*<<< orphan*/  u64; } ;
typedef  TYPE_4__ cTValue ;
struct TYPE_12__ {scalar_t__ o; size_t op1; int op2; int /*<<< orphan*/  t; } ;
struct TYPE_8__ {int /*<<< orphan*/  base; } ;
typedef  int TRef ;
typedef  int SnapEntry ;
typedef  scalar_t__ MSize ;
typedef  int IRRef ;
typedef  TYPE_5__ IRIns ;
typedef  size_t BCReg ;

/* Variables and functions */
 int IRSLOAD_CONVERT ; 
 int IRSLOAD_INHERIT ; 
 int IRSLOAD_PARENT ; 
 int IRSLOAD_READONLY ; 
 int /*<<< orphan*/  IR_KNUM ; 
 size_t IR_RETF ; 
 scalar_t__ IR_SLOAD ; 
 scalar_t__ LJ_DUALNUM ; 
 scalar_t__ LJ_FR2 ; 
 scalar_t__ LJ_SOFTFP ; 
 int /*<<< orphan*/  REF_NIL ; 
 int SNAP (int,int,int /*<<< orphan*/ ) ; 
 int SNAP_CONT ; 
 int SNAP_FRAME ; 
 int SNAP_NORESTORE ; 
 int SNAP_SOFTFPNUM ; 
 int SNAP_TR (size_t,int) ; 
 int TREF_CONT ; 
 int TREF_FRAME ; 
 scalar_t__ irt_isnum (int /*<<< orphan*/ ) ; 
 int lj_ir_k64 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tref_ref (int) ; 

__attribute__((used)) static MSize snapshot_slots(jit_State *J, SnapEntry *map, BCReg nslots)
{
  IRRef retf = J->chain[IR_RETF];  /* Limits SLOAD restore elimination. */
  BCReg s;
  MSize n = 0;
  for (s = 0; s < nslots; s++) {
    TRef tr = J->slot[s];
    IRRef ref = tref_ref(tr);
#if LJ_FR2
    if (s == 1) {  /* Ignore slot 1 in LJ_FR2 mode, except if tailcalled. */
      if ((tr & TREF_FRAME))
	map[n++] = SNAP(1, SNAP_FRAME | SNAP_NORESTORE, REF_NIL);
      continue;
    }
    if ((tr & (TREF_FRAME | TREF_CONT)) && !ref) {
      cTValue *base = J->L->base - J->baseslot;
      tr = J->slot[s] = (tr & 0xff0000) | lj_ir_k64(J, IR_KNUM, base[s].u64);
      ref = tref_ref(tr);
    }
#endif
    if (ref) {
      SnapEntry sn = SNAP_TR(s, tr);
      IRIns *ir = &J->cur.ir[ref];
      if ((LJ_FR2 || !(sn & (SNAP_CONT|SNAP_FRAME))) &&
	  ir->o == IR_SLOAD && ir->op1 == s && ref > retf) {
	/* No need to snapshot unmodified non-inherited slots. */
	if (!(ir->op2 & IRSLOAD_INHERIT))
	  continue;
	/* No need to restore readonly slots and unmodified non-parent slots. */
	if (!(LJ_DUALNUM && (ir->op2 & IRSLOAD_CONVERT)) &&
	    (ir->op2 & (IRSLOAD_READONLY|IRSLOAD_PARENT)) != IRSLOAD_PARENT)
	  sn |= SNAP_NORESTORE;
      }
      if (LJ_SOFTFP && irt_isnum(ir->t))
	sn |= SNAP_SOFTFPNUM;
      map[n++] = sn;
    }
  }
  return n;
}