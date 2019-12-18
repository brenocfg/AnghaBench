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
struct TYPE_5__ {scalar_t__ o; int /*<<< orphan*/  op1; int /*<<< orphan*/  op2; } ;
typedef  TYPE_1__ IRIns ;

/* Variables and functions */
 TYPE_1__* IR (int /*<<< orphan*/ ) ; 
 scalar_t__ IR_ADD ; 
 scalar_t__ IR_AREF ; 
 scalar_t__ IR_CNEW ; 
 scalar_t__ IR_FREF ; 
 scalar_t__ IR_HREF ; 
 scalar_t__ IR_HREFK ; 
 scalar_t__ IR_NEWREF ; 
 scalar_t__ IR_TDUP ; 
 scalar_t__ IR_TNEW ; 
 int /*<<< orphan*/  irref_isk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static IRIns *sink_checkalloc(jit_State *J, IRIns *irs)
{
  IRIns *ir = IR(irs->op1);
  if (!irref_isk(ir->op2))
    return NULL;  /* Non-constant key. */
  if (ir->o == IR_HREFK || ir->o == IR_AREF)
    ir = IR(ir->op1);
  else if (!(ir->o == IR_HREF || ir->o == IR_NEWREF ||
	     ir->o == IR_FREF || ir->o == IR_ADD))
    return NULL;  /* Unhandled reference type (for XSTORE). */
  ir = IR(ir->op1);
  if (!(ir->o == IR_TNEW || ir->o == IR_TDUP || ir->o == IR_CNEW))
    return NULL;  /* Not an allocation. */
  return ir;  /* Return allocation. */
}