#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  state; scalar_t__ exitno; scalar_t__ parent; int /*<<< orphan*/ * pc; int /*<<< orphan*/ * pt; } ;
typedef  TYPE_1__ jit_State ;

/* Variables and functions */
 scalar_t__ BC_RETM ; 
 int /*<<< orphan*/  LJ_TRACE_RECORD ; 
 int /*<<< orphan*/  bc_isret (scalar_t__) ; 
 scalar_t__ bc_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_start (TYPE_1__*) ; 

__attribute__((used)) static int trace_downrec(jit_State *J)
{
  /* Restart recording at the return instruction. */
  lua_assert(J->pt != NULL);
  lua_assert(bc_isret(bc_op(*J->pc)));
  if (bc_op(*J->pc) == BC_RETM)
    return 0;  /* NYI: down-recursion with RETM. */
  J->parent = 0;
  J->exitno = 0;
  J->state = LJ_TRACE_RECORD;
  trace_start(J);
  return 1;
}