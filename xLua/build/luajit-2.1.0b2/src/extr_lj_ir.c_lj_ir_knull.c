#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_8__ {TYPE_3__* ir; } ;
struct TYPE_9__ {int* chain; TYPE_1__ cur; } ;
typedef  TYPE_2__ jit_State ;
struct TYPE_11__ {scalar_t__ irt; } ;
struct TYPE_10__ {int prev; size_t o; TYPE_5__ t; scalar_t__ i; } ;
typedef  int /*<<< orphan*/  TRef ;
typedef  scalar_t__ IRType ;
typedef  int IRRef1 ;
typedef  int IRRef ;
typedef  TYPE_3__ IRIns ;

/* Variables and functions */
 TYPE_3__* IR (int) ; 
 size_t IR_KNULL ; 
 int /*<<< orphan*/  TREF (int,scalar_t__) ; 
 int ir_nextk (TYPE_2__*) ; 
 scalar_t__ irt_t (TYPE_5__) ; 

TRef lj_ir_knull(jit_State *J, IRType t)
{
  IRIns *ir, *cir = J->cur.ir;
  IRRef ref;
  for (ref = J->chain[IR_KNULL]; ref; ref = cir[ref].prev)
    if (irt_t(cir[ref].t) == t)
      goto found;
  ref = ir_nextk(J);
  ir = IR(ref);
  ir->i = 0;
  ir->t.irt = (uint8_t)t;
  ir->o = IR_KNULL;
  ir->prev = J->chain[IR_KNULL];
  J->chain[IR_KNULL] = (IRRef1)ref;
found:
  return TREF(ref, t);
}