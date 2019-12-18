#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ nins; } ;
struct TYPE_7__ {TYPE_1__ cur; int /*<<< orphan*/ * chain; } ;
typedef  TYPE_2__ jit_State ;
struct TYPE_8__ {size_t o; int /*<<< orphan*/  prev; } ;
typedef  scalar_t__ IRRef ;
typedef  TYPE_3__ IRIns ;

/* Variables and functions */
 TYPE_3__* IR (scalar_t__) ; 

void lj_ir_rollback(jit_State *J, IRRef ref)
{
  IRRef nins = J->cur.nins;
  while (nins > ref) {
    IRIns *ir;
    nins--;
    ir = IR(nins);
    J->chain[ir->o] = ir->prev;
  }
  J->cur.nins = nins;
}