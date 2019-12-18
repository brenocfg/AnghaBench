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
typedef  int ptrdiff_t ;
struct TYPE_5__ {TYPE_1__* bcbase; } ;
struct TYPE_4__ {int /*<<< orphan*/  ins; } ;
typedef  TYPE_2__ FuncState ;
typedef  size_t BCPos ;

/* Variables and functions */
 size_t NO_JMP ; 
 int bc_j (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BCPos jmp_next(FuncState *fs, BCPos pc)
{
  ptrdiff_t delta = bc_j(fs->bcbase[pc].ins);
  if ((BCPos)delta == NO_JMP)
    return NO_JMP;
  else
    return (BCPos)(((ptrdiff_t)pc+1)+delta);
}