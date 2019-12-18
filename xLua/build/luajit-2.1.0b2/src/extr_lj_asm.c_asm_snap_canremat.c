#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * cost; } ;
typedef  size_t Reg ;
typedef  TYPE_1__ ASMState ;

/* Variables and functions */
 size_t RID_MAX_FPR ; 
 size_t RID_MIN_FPR ; 
 scalar_t__ irref_isk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcost_ref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asm_snap_canremat(ASMState *as)
{
  Reg r;
  for (r = RID_MIN_FPR; r < RID_MAX_FPR; r++)
    if (irref_isk(regcost_ref(as->cost[r])))
      return 1;
  return 0;
}