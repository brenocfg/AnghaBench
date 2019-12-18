#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* L; int /*<<< orphan*/ * pc; } ;
typedef  TYPE_3__ jit_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_10__ {scalar_t__ ffid; } ;
struct TYPE_12__ {TYPE_2__ c; } ;
struct TYPE_9__ {int /*<<< orphan*/ * base; } ;
typedef  int /*<<< orphan*/  TRef ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
 scalar_t__ BC_CALLM ; 
 scalar_t__ FF_select ; 
 int /*<<< orphan*/  IRTG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRT_FUNC ; 
 int /*<<< orphan*/  IR_EQ ; 
 size_t bc_a (int /*<<< orphan*/ ) ; 
 int bc_b (int /*<<< orphan*/ ) ; 
 int bc_c (int /*<<< orphan*/ ) ; 
 scalar_t__ bc_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* funcV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getslot (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  lj_ir_kfunc (TYPE_3__*,TYPE_6__*) ; 
 scalar_t__ tvisfunc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int select_detect(jit_State *J)
{
  BCIns ins = J->pc[1];
  if (bc_op(ins) == BC_CALLM && bc_b(ins) == 2 && bc_c(ins) == 1) {
    cTValue *func = &J->L->base[bc_a(ins)];
    if (tvisfunc(func) && funcV(func)->c.ffid == FF_select) {
      TRef kfunc = lj_ir_kfunc(J, funcV(func));
      emitir(IRTG(IR_EQ, IRT_FUNC), getslot(J, bc_a(ins)), kfunc);
      return 1;
    }
  }
  return 0;
}