#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_8__ {TYPE_1__* T; int /*<<< orphan*/  ir; int /*<<< orphan*/  J; int /*<<< orphan*/  loopsnapno; int /*<<< orphan*/ * phireg; scalar_t__ phiset; } ;
struct TYPE_7__ {int /*<<< orphan*/  s; scalar_t__ r; int /*<<< orphan*/  t; } ;
struct TYPE_6__ {int /*<<< orphan*/  ir; } ;
typedef  scalar_t__ RegSet ;
typedef  size_t Reg ;
typedef  int /*<<< orphan*/  IRRef ;
typedef  TYPE_2__ IRIns ;
typedef  TYPE_3__ ASMState ;

/* Variables and functions */
 TYPE_2__* IR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRT_NIL ; 
 int /*<<< orphan*/  IR_RENAME ; 
 int /*<<< orphan*/  SPS_NONE ; 
 int /*<<< orphan*/  irt_clearmark (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_ismarked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_emit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_hasspill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_clear (scalar_t__,size_t) ; 
 size_t rset_picktop (scalar_t__) ; 
 int /*<<< orphan*/  tref_ref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asm_phi_fixup(ASMState *as)
{
  RegSet work = as->phiset;
  while (work) {
    Reg r = rset_picktop(work);
    IRRef lref = as->phireg[r];
    IRIns *ir = IR(lref);
    if (irt_ismarked(ir->t)) {
      irt_clearmark(ir->t);
      /* Left PHI gained a spill slot before the loop? */
      if (ra_hasspill(ir->s)) {
	IRRef ren;
	lj_ir_set(as->J, IRT(IR_RENAME, IRT_NIL), lref, as->loopsnapno);
	ren = tref_ref(lj_ir_emit(as->J));
	as->ir = as->T->ir;  /* The IR may have been reallocated. */
	IR(ren)->r = (uint8_t)r;
	IR(ren)->s = SPS_NONE;
      }
    }
    rset_clear(work, r);
  }
}