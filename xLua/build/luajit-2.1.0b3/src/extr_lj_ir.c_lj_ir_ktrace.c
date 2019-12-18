#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jit_State ;
struct TYPE_4__ {int /*<<< orphan*/  irt; } ;
struct TYPE_5__ {scalar_t__ prev; scalar_t__ op12; int /*<<< orphan*/  o; TYPE_1__ t; } ;
typedef  int /*<<< orphan*/  TRef ;
typedef  int /*<<< orphan*/  IRRef ;
typedef  TYPE_2__ IRIns ;

/* Variables and functions */
 TYPE_2__* IR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRT_P64 ; 
 int /*<<< orphan*/  IR_KNULL ; 
 int /*<<< orphan*/  IR_KNUM ; 
 scalar_t__ LJ_GC64 ; 
 scalar_t__ LJ_TTRACE ; 
 int /*<<< orphan*/  TREF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_nextkgc (int /*<<< orphan*/ *) ; 
 scalar_t__ irt_toitype_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

TRef lj_ir_ktrace(jit_State *J)
{
  IRRef ref = ir_nextkgc(J);
  IRIns *ir = IR(ref);
  lua_assert(irt_toitype_(IRT_P64) == LJ_TTRACE);
  ir->t.irt = IRT_P64;
  ir->o = LJ_GC64 ? IR_KNUM : IR_KNULL;  /* Not IR_KGC yet, but same size. */
  ir->op12 = 0;
  ir->prev = 0;
  return TREF(ref, IRT_P64);
}