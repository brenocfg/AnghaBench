#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ curins; TYPE_1__* ir; } ;
struct TYPE_4__ {scalar_t__ o; scalar_t__ op1; scalar_t__ op2; } ;
typedef  scalar_t__ IRRef ;
typedef  scalar_t__ IROp ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 scalar_t__ CONFLICT_SEARCH_LIM ; 

__attribute__((used)) static int noconflict(ASMState *as, IRRef ref, IROp conflict, int noload)
{
  IRIns *ir = as->ir;
  IRRef i = as->curins;
  if (i > ref + CONFLICT_SEARCH_LIM)
    return 0;  /* Give up, ref is too far away. */
  while (--i > ref) {
    if (ir[i].o == conflict)
      return 0;  /* Conflict found. */
    else if (!noload && (ir[i].op1 == ref || ir[i].op2 == ref))
      return 0;
  }
  return 1;  /* Ok, no conflict. */
}