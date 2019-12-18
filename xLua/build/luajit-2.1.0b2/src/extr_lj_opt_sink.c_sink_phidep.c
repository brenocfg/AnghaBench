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
typedef  int /*<<< orphan*/  jit_State ;
struct TYPE_3__ {scalar_t__ op1; scalar_t__ op2; int /*<<< orphan*/  t; } ;
typedef  scalar_t__ IRRef ;
typedef  TYPE_1__ IRIns ;

/* Variables and functions */
 TYPE_1__* IR (scalar_t__) ; 
 scalar_t__ REF_FIRST ; 
 scalar_t__ irt_isphi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sink_phidep(jit_State *J, IRRef ref)
{
  IRIns *ir = IR(ref);
  if (irt_isphi(ir->t)) return 1;
  if (ir->op1 >= REF_FIRST && sink_phidep(J, ir->op1)) return 1;
  if (ir->op2 >= REF_FIRST && sink_phidep(J, ir->op2)) return 1;
  return 0;
}