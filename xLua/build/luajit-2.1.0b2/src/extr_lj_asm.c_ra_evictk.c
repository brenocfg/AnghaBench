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
struct TYPE_5__ {int freeset; int /*<<< orphan*/ * cost; } ;
typedef  int RegSet ;
typedef  size_t Reg ;
typedef  int /*<<< orphan*/  IRRef ;
typedef  TYPE_1__ ASMState ;

/* Variables and functions */
 int RSET_FPR ; 
 int RSET_GPR ; 
 int /*<<< orphan*/  checkmclim (TYPE_1__*) ; 
 scalar_t__ emit_canremat (int /*<<< orphan*/ ) ; 
 scalar_t__ irref_isk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_rematk (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcost_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_clear (int,size_t) ; 
 size_t rset_pickbot (int) ; 

__attribute__((used)) static void ra_evictk(ASMState *as)
{
  RegSet work;
#if !LJ_SOFTFP
  work = ~as->freeset & RSET_FPR;
  while (work) {
    Reg r = rset_pickbot(work);
    IRRef ref = regcost_ref(as->cost[r]);
    if (emit_canremat(ref) && irref_isk(ref)) {
      ra_rematk(as, ref);
      checkmclim(as);
    }
    rset_clear(work, r);
  }
#endif
  work = ~as->freeset & RSET_GPR;
  while (work) {
    Reg r = rset_pickbot(work);
    IRRef ref = regcost_ref(as->cost[r]);
    if (emit_canremat(ref) && irref_isk(ref)) {
      ra_rematk(as, ref);
      checkmclim(as);
    }
    rset_clear(work, r);
  }
}