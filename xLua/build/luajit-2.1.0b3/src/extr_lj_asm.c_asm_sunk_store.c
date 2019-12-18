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
struct TYPE_5__ {int s; scalar_t__ o; int /*<<< orphan*/  op1; } ;
typedef  TYPE_1__ IRIns ;
typedef  int /*<<< orphan*/  ASMState ;

/* Variables and functions */
 TYPE_1__* IR (int /*<<< orphan*/ ) ; 
 scalar_t__ IR_AREF ; 
 scalar_t__ IR_ASTORE ; 
 scalar_t__ IR_FSTORE ; 
 scalar_t__ IR_HREFK ; 
 scalar_t__ IR_HSTORE ; 
 scalar_t__ IR_XSTORE ; 

__attribute__((used)) static int asm_sunk_store(ASMState *as, IRIns *ira, IRIns *irs)
{
  if (irs->s == 255) {
    if (irs->o == IR_ASTORE || irs->o == IR_HSTORE ||
	irs->o == IR_FSTORE || irs->o == IR_XSTORE) {
      IRIns *irk = IR(irs->op1);
      if (irk->o == IR_AREF || irk->o == IR_HREFK)
	irk = IR(irk->op1);
      return (IR(irk->op1) == ira);
    }
    return 0;
  } else {
    return (ira + irs->s == irs);  /* Quick check. */
  }
}