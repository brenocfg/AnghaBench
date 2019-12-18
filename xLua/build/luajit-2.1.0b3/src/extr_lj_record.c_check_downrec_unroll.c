#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__* chain; scalar_t__ pc; scalar_t__ startpc; scalar_t__ tailcalled; scalar_t__* param; } ;
typedef  TYPE_1__ jit_State ;
struct TYPE_7__ {scalar_t__ prev; scalar_t__ op1; } ;
typedef  scalar_t__ IRRef ;
typedef  int /*<<< orphan*/  GCproto ;

/* Variables and functions */
 TYPE_3__* IR (scalar_t__) ; 
 size_t IR_KGC ; 
 size_t IR_RETF ; 
 size_t JIT_P_recunroll ; 
 int /*<<< orphan*/  LJ_TRERR_DOWNREC ; 
 scalar_t__ ir_kgc (TYPE_3__*) ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ obj2gco (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_downrec_unroll(jit_State *J, GCproto *pt)
{
  IRRef ptref;
  for (ptref = J->chain[IR_KGC]; ptref; ptref = IR(ptref)->prev)
    if (ir_kgc(IR(ptref)) == obj2gco(pt)) {
      int count = 0;
      IRRef ref;
      for (ref = J->chain[IR_RETF]; ref; ref = IR(ref)->prev)
	if (IR(ref)->op1 == ptref)
	  count++;
      if (count) {
	if (J->pc == J->startpc) {
	  if (count + J->tailcalled > J->param[JIT_P_recunroll])
	    return 1;
	} else {
	  lj_trace_err(J, LJ_TRERR_DOWNREC);
	}
      }
    }
  return 0;
}