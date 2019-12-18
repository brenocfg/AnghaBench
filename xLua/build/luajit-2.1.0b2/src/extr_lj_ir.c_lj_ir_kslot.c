#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* ir; } ;
struct TYPE_10__ {scalar_t__* chain; TYPE_1__ cur; } ;
typedef  TYPE_3__ jit_State ;
struct TYPE_9__ {int /*<<< orphan*/  irt; } ;
struct TYPE_11__ {scalar_t__ prev; scalar_t__ op12; size_t o; TYPE_2__ t; } ;
typedef  scalar_t__ TRef ;
typedef  scalar_t__ IRRef2 ;
typedef  scalar_t__ IRRef1 ;
typedef  scalar_t__ IRRef ;
typedef  TYPE_4__ IRIns ;

/* Variables and functions */
 TYPE_4__* IR (scalar_t__) ; 
 scalar_t__ IRREF2 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  IRT_P32 ; 
 size_t IR_KSLOT ; 
 scalar_t__ TREF (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ir_nextk (TYPE_3__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 scalar_t__ tref_isk (scalar_t__) ; 

TRef lj_ir_kslot(jit_State *J, TRef key, IRRef slot)
{
  IRIns *ir, *cir = J->cur.ir;
  IRRef2 op12 = IRREF2((IRRef1)key, (IRRef1)slot);
  IRRef ref;
  /* Const part is not touched by CSE/DCE, so 0-65535 is ok for IRMlit here. */
  lua_assert(tref_isk(key) && slot == (IRRef)(IRRef1)slot);
  for (ref = J->chain[IR_KSLOT]; ref; ref = cir[ref].prev)
    if (cir[ref].op12 == op12)
      goto found;
  ref = ir_nextk(J);
  ir = IR(ref);
  ir->op12 = op12;
  ir->t.irt = IRT_P32;
  ir->o = IR_KSLOT;
  ir->prev = J->chain[IR_KSLOT];
  J->chain[IR_KSLOT] = (IRRef1)ref;
found:
  return TREF(ref, IRT_P32);
}