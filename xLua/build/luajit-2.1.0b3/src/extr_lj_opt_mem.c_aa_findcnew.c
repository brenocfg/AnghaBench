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
typedef  int /*<<< orphan*/  jit_State ;
struct TYPE_5__ {scalar_t__ o; int /*<<< orphan*/  op2; int /*<<< orphan*/  op1; } ;
typedef  TYPE_1__ IRIns ;

/* Variables and functions */
 TYPE_1__* IR (int /*<<< orphan*/ ) ; 
 scalar_t__ IR_ADD ; 
 scalar_t__ IR_CNEW ; 
 scalar_t__ irref_isk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static IRIns *aa_findcnew(jit_State *J, IRIns *ir)
{
  while (ir->o == IR_ADD) {
    if (!irref_isk(ir->op1)) {
      IRIns *ir1 = aa_findcnew(J, IR(ir->op1));  /* Left-recursion. */
      if (ir1) return ir1;
    }
    if (irref_isk(ir->op2)) return NULL;
    ir = IR(ir->op2);  /* Flatten right-recursion. */
  }
  return ir->o == IR_CNEW ? ir : NULL;
}