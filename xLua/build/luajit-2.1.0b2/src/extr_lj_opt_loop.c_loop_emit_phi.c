#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nins; size_t nsnap; int /*<<< orphan*/ * snapmap; TYPE_3__* snap; } ;
struct TYPE_9__ {size_t* chain; size_t baseslot; size_t maxslot; int /*<<< orphan*/ * slot; TYPE_1__ cur; } ;
typedef  TYPE_2__ jit_State ;
struct TYPE_11__ {size_t op1; size_t op2; scalar_t__ o; int /*<<< orphan*/  t; } ;
struct TYPE_10__ {size_t mapofs; size_t nent; } ;
typedef  TYPE_3__ SnapShot ;
typedef  size_t SnapNo ;
typedef  int /*<<< orphan*/  SnapEntry ;
typedef  size_t MSize ;
typedef  size_t IRRef1 ;
typedef  size_t IRRef ;
typedef  TYPE_4__ IRIns ;

/* Variables and functions */
 TYPE_4__* IR (size_t) ; 
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IR_CALLN ; 
 scalar_t__ IR_CARG ; 
 size_t IR_LOOP ; 
 int /*<<< orphan*/  IR_PHI ; 
 size_t LJ_MAX_PHI ; 
 int /*<<< orphan*/  LJ_TRERR_PHIOV ; 
 size_t REF_DROP ; 
 int /*<<< orphan*/  emitir_raw (int /*<<< orphan*/ ,size_t,size_t) ; 
 scalar_t__ irref_isk (size_t) ; 
 int /*<<< orphan*/  irt_clearmark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_clearphi (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_ismarked (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isphi (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_ispri (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_setmark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_setphi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_2__*,int /*<<< orphan*/ ) ; 
 size_t snap_ref (int /*<<< orphan*/ ) ; 
 size_t tref_ref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void loop_emit_phi(jit_State *J, IRRef1 *subst, IRRef1 *phi, IRRef nphi,
			  SnapNo onsnap)
{
  int passx = 0;
  IRRef i, j, nslots;
  IRRef invar = J->chain[IR_LOOP];
  /* Pass #1: mark redundant and potentially redundant PHIs. */
  for (i = 0, j = 0; i < nphi; i++) {
    IRRef lref = phi[i];
    IRRef rref = subst[lref];
    if (lref == rref || rref == REF_DROP) {  /* Invariants are redundant. */
      irt_clearphi(IR(lref)->t);
    } else {
      phi[j++] = (IRRef1)lref;
      if (!(IR(rref)->op1 == lref || IR(rref)->op2 == lref)) {
	/* Quick check for simple recurrences failed, need pass2. */
	irt_setmark(IR(lref)->t);
	passx = 1;
      }
    }
  }
  nphi = j;
  /* Pass #2: traverse variant part and clear marks of non-redundant PHIs. */
  if (passx) {
    SnapNo s;
    for (i = J->cur.nins-1; i > invar; i--) {
      IRIns *ir = IR(i);
      if (!irref_isk(ir->op2)) irt_clearmark(IR(ir->op2)->t);
      if (!irref_isk(ir->op1)) {
	irt_clearmark(IR(ir->op1)->t);
	if (ir->op1 < invar &&
	    ir->o >= IR_CALLN && ir->o <= IR_CARG) {  /* ORDER IR */
	  ir = IR(ir->op1);
	  while (ir->o == IR_CARG) {
	    if (!irref_isk(ir->op2)) irt_clearmark(IR(ir->op2)->t);
	    if (irref_isk(ir->op1)) break;
	    ir = IR(ir->op1);
	    irt_clearmark(ir->t);
	  }
	}
      }
    }
    for (s = J->cur.nsnap-1; s >= onsnap; s--) {
      SnapShot *snap = &J->cur.snap[s];
      SnapEntry *map = &J->cur.snapmap[snap->mapofs];
      MSize n, nent = snap->nent;
      for (n = 0; n < nent; n++) {
	IRRef ref = snap_ref(map[n]);
	if (!irref_isk(ref)) irt_clearmark(IR(ref)->t);
      }
    }
  }
  /* Pass #3: add PHIs for variant slots without a corresponding SLOAD. */
  nslots = J->baseslot+J->maxslot;
  for (i = 1; i < nslots; i++) {
    IRRef ref = tref_ref(J->slot[i]);
    while (!irref_isk(ref) && ref != subst[ref]) {
      IRIns *ir = IR(ref);
      irt_clearmark(ir->t);  /* Unmark potential uses, too. */
      if (irt_isphi(ir->t) || irt_ispri(ir->t))
	break;
      irt_setphi(ir->t);
      if (nphi >= LJ_MAX_PHI)
	lj_trace_err(J, LJ_TRERR_PHIOV);
      phi[nphi++] = (IRRef1)ref;
      ref = subst[ref];
      if (ref > invar)
	break;
    }
  }
  /* Pass #4: propagate non-redundant PHIs. */
  while (passx) {
    passx = 0;
    for (i = 0; i < nphi; i++) {
      IRRef lref = phi[i];
      IRIns *ir = IR(lref);
      if (!irt_ismarked(ir->t)) {  /* Propagate only from unmarked PHIs. */
	IRIns *irr = IR(subst[lref]);
	if (irt_ismarked(irr->t)) {  /* Right ref points to other PHI? */
	  irt_clearmark(irr->t);  /* Mark that PHI as non-redundant. */
	  passx = 1;  /* Retry. */
	}
      }
    }
  }
  /* Pass #5: emit PHI instructions or eliminate PHIs. */
  for (i = 0; i < nphi; i++) {
    IRRef lref = phi[i];
    IRIns *ir = IR(lref);
    if (!irt_ismarked(ir->t)) {  /* Emit PHI if not marked. */
      IRRef rref = subst[lref];
      if (rref > invar)
	irt_setphi(IR(rref)->t);
      emitir_raw(IRT(IR_PHI, irt_type(ir->t)), lref, rref);
    } else {  /* Otherwise eliminate PHI. */
      irt_clearmark(ir->t);
      irt_clearphi(ir->t);
    }
  }
}