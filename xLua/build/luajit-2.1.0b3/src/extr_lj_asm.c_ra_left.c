#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int freeset; scalar_t__* phireg; } ;
struct TYPE_16__ {size_t r; scalar_t__ o; int /*<<< orphan*/  t; int /*<<< orphan*/  i; } ;
typedef  size_t Reg ;
typedef  scalar_t__ IRRef ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 TYPE_1__* IR (scalar_t__) ; 
 scalar_t__ IR_KGC ; 
 scalar_t__ IR_KINT ; 
 scalar_t__ IR_KINT64 ; 
 scalar_t__ IR_KKPTR ; 
 scalar_t__ IR_KNULL ; 
 scalar_t__ IR_KNUM ; 
 scalar_t__ IR_KPRI ; 
 scalar_t__ IR_KPTR ; 
 size_t RID_MAX_GPR ; 
 int RSET_FPR ; 
 int RSET_GPR ; 
 int /*<<< orphan*/  emit_loadi (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_loadk64 (TYPE_2__*,size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  emit_movrr (TYPE_2__*,TYPE_1__*,size_t,size_t) ; 
 int /*<<< orphan*/  ir_knum (TYPE_1__*) ; 
 scalar_t__ irref_isk (scalar_t__) ; 
 scalar_t__ irt_isphi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscrossref (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 size_t ra_allocref (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  ra_hashint (size_t) ; 
 int /*<<< orphan*/  ra_modified (TYPE_2__*,size_t) ; 
 scalar_t__ ra_noreg (size_t) ; 
 int /*<<< orphan*/  ra_noweak (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  ra_rename (TYPE_2__*,size_t,size_t) ; 
 int /*<<< orphan*/  ra_sethint (size_t,size_t) ; 
 scalar_t__ tvispzero (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ra_left(ASMState *as, Reg dest, IRRef lref)
{
  IRIns *ir = IR(lref);
  Reg left = ir->r;
  if (ra_noreg(left)) {
    if (irref_isk(lref)) {
      if (ir->o == IR_KNUM) {
	/* FP remat needs a load except for +0. Still better than eviction. */
	if (tvispzero(ir_knum(ir)) || !(as->freeset & RSET_FPR)) {
	  emit_loadk64(as, dest, ir);
	  return;
	}
#if LJ_64
      } else if (ir->o == IR_KINT64) {
	emit_loadk64(as, dest, ir);
	return;
#if LJ_GC64
      } else if (ir->o == IR_KGC || ir->o == IR_KPTR || ir->o == IR_KKPTR) {
	emit_loadk64(as, dest, ir);
	return;
#endif
#endif
      } else if (ir->o != IR_KPRI) {
	lua_assert(ir->o == IR_KINT || ir->o == IR_KGC ||
		   ir->o == IR_KPTR || ir->o == IR_KKPTR || ir->o == IR_KNULL);
	emit_loadi(as, dest, ir->i);
	return;
      }
    }
    if (!ra_hashint(left) && !iscrossref(as, lref))
      ra_sethint(ir->r, dest);  /* Propagate register hint. */
    left = ra_allocref(as, lref, dest < RID_MAX_GPR ? RSET_GPR : RSET_FPR);
  }
  ra_noweak(as, left);
  /* Move needed for true 3-operand instruction: y=a+b ==> y=a; y+=b. */
  if (dest != left) {
    /* Use register renaming if dest is the PHI reg. */
    if (irt_isphi(ir->t) && as->phireg[dest] == lref) {
      ra_modified(as, left);
      ra_rename(as, left, dest);
    } else {
      emit_movrr(as, ir, dest, left);
    }
  }
}