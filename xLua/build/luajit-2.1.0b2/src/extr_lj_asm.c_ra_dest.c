#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int freeset; } ;
struct TYPE_11__ {int /*<<< orphan*/  s; int /*<<< orphan*/  r; } ;
typedef  int RegSet ;
typedef  int /*<<< orphan*/  Reg ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 scalar_t__ LJ_UNLIKELY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RA_DBGX (TYPE_2__*) ; 
 int /*<<< orphan*/  ra_free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_gethint (int /*<<< orphan*/ ) ; 
 scalar_t__ ra_hashint (int /*<<< orphan*/ ) ; 
 scalar_t__ ra_hasreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_hasspill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_modified (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_save (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_scratch (TYPE_2__*,int) ; 
 scalar_t__ rset_test (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Reg ra_dest(ASMState *as, IRIns *ir, RegSet allow)
{
  Reg dest = ir->r;
  if (ra_hasreg(dest)) {
    ra_free(as, dest);
    ra_modified(as, dest);
  } else {
    if (ra_hashint(dest) && rset_test((as->freeset&allow), ra_gethint(dest))) {
      dest = ra_gethint(dest);
      ra_modified(as, dest);
      RA_DBGX((as, "dest           $r", dest));
    } else {
      dest = ra_scratch(as, allow);
    }
    ir->r = dest;
  }
  if (LJ_UNLIKELY(ra_hasspill(ir->s))) ra_save(as, ir, dest);
  return dest;
}