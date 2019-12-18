#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int modset; int freeset; int /*<<< orphan*/ * cost; } ;
typedef  int RegSet ;
typedef  size_t Reg ;
typedef  TYPE_1__ ASMState ;

/* Variables and functions */
 int RSET_FPR ; 
 int /*<<< orphan*/  checkmclim (TYPE_1__*) ; 
 int /*<<< orphan*/  ra_restore (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcost_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_clear (int,size_t) ; 
 size_t rset_pickbot (int) ; 

__attribute__((used)) static void ra_evictset(ASMState *as, RegSet drop)
{
  RegSet work;
  as->modset |= drop;
#if !LJ_SOFTFP
  work = (drop & ~as->freeset) & RSET_FPR;
  while (work) {
    Reg r = rset_pickbot(work);
    ra_restore(as, regcost_ref(as->cost[r]));
    rset_clear(work, r);
    checkmclim(as);
  }
#endif
  work = (drop & ~as->freeset);
  while (work) {
    Reg r = rset_pickbot(work);
    ra_restore(as, regcost_ref(as->cost[r]));
    rset_clear(work, r);
    checkmclim(as);
  }
}