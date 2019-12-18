#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  loopsnapno; int /*<<< orphan*/ * phireg; scalar_t__ phiset; } ;
struct TYPE_6__ {int /*<<< orphan*/  s; int /*<<< orphan*/  t; } ;
typedef  scalar_t__ RegSet ;
typedef  size_t Reg ;
typedef  int /*<<< orphan*/  IRRef ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 TYPE_1__* IR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_clearmark (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_ismarked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_addrename (TYPE_2__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_hasspill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_clear (scalar_t__,size_t) ; 
 size_t rset_picktop (scalar_t__) ; 

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
	ra_addrename(as, r, lref, as->loopsnapno);
      }
    }
    rset_clear(work, r);
  }
}