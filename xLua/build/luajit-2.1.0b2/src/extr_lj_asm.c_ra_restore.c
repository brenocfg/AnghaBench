#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_14__ {int /*<<< orphan*/  weakset; } ;
struct TYPE_13__ {int /*<<< orphan*/  r; } ;
typedef  int /*<<< orphan*/  Reg ;
typedef  int /*<<< orphan*/  IRRef ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 TYPE_1__* IR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RA_DBGX (TYPE_2__*) ; 
 scalar_t__ emit_canremat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_spload (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_hasreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_modified (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_rematk (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_sethint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_spill (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  rset_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Reg ra_restore(ASMState *as, IRRef ref)
{
  if (emit_canremat(ref)) {
    return ra_rematk(as, ref);
  } else {
    IRIns *ir = IR(ref);
    int32_t ofs = ra_spill(as, ir);  /* Force a spill slot. */
    Reg r = ir->r;
    lua_assert(ra_hasreg(r));
    ra_sethint(ir->r, r);  /* Keep hint. */
    ra_free(as, r);
    if (!rset_test(as->weakset, r)) {  /* Only restore non-weak references. */
      ra_modified(as, r);
      RA_DBGX((as, "restore   $i $r", ir, r));
      emit_spload(as, ir, r, ofs);
    }
    return r;
  }
}