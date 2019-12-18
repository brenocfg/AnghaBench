#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* bcbase; } ;
struct TYPE_5__ {int /*<<< orphan*/  ins; } ;
typedef  TYPE_2__ FuncState ;
typedef  int BCPos ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
 scalar_t__ BC_ISFC ; 
 scalar_t__ BC_ISTC ; 
 int NO_JMP ; 
 scalar_t__ NO_REG ; 
 scalar_t__ bc_a (int /*<<< orphan*/ ) ; 
 scalar_t__ bc_op (int /*<<< orphan*/ ) ; 
 int jmp_next (TYPE_2__*,int) ; 

__attribute__((used)) static int jmp_novalue(FuncState *fs, BCPos list)
{
  for (; list != NO_JMP; list = jmp_next(fs, list)) {
    BCIns p = fs->bcbase[list >= 1 ? list-1 : list].ins;
    if (!(bc_op(p) == BC_ISTC || bc_op(p) == BC_ISFC || bc_a(p) == NO_REG))
      return 1;
  }
  return 0;
}