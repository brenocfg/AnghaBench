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
struct TYPE_4__ {int maxslot; int /*<<< orphan*/ * pc; int /*<<< orphan*/ * base; } ;
typedef  TYPE_1__ jit_State ;
typedef  int /*<<< orphan*/  LoopEvent ;
typedef  int BCReg ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_FR2 ; 
 int /*<<< orphan*/  LOOPEV_ENTER ; 
 int /*<<< orphan*/  LOOPEV_LEAVE ; 
 int bc_a (int /*<<< orphan*/  const) ; 
 int bc_b (int /*<<< orphan*/ ) ; 
 scalar_t__ bc_j (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  getslot (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  tref_isnil (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LoopEvent rec_iterl(jit_State *J, const BCIns iterins)
{
  BCReg ra = bc_a(iterins);
  lua_assert(!LJ_FR2);  /* TODO_FR2: handle different frame setup. */
  if (!tref_isnil(getslot(J, ra))) {  /* Looping back? */
    J->base[ra-1] = J->base[ra];  /* Copy result of ITERC to control var. */
    J->maxslot = ra-1+bc_b(J->pc[-1]);
    J->pc += bc_j(iterins)+1;
    return LOOPEV_ENTER;
  } else {
    J->maxslot = ra-3;
    J->pc++;
    return LOOPEV_LEAVE;
  }
}