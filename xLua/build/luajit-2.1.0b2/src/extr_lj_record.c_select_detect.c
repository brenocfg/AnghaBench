#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* L; int /*<<< orphan*/ * pc; } ;
typedef  TYPE_3__ jit_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_7__ {scalar_t__ ffid; } ;
struct TYPE_9__ {TYPE_2__ c; } ;
struct TYPE_6__ {int /*<<< orphan*/ * base; } ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
 scalar_t__ BC_CALLM ; 
 scalar_t__ FF_select ; 
 size_t bc_a (int /*<<< orphan*/ ) ; 
 int bc_b (int /*<<< orphan*/ ) ; 
 int bc_c (int /*<<< orphan*/ ) ; 
 scalar_t__ bc_op (int /*<<< orphan*/ ) ; 
 TYPE_5__* funcV (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisfunc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int select_detect(jit_State *J)
{
  BCIns ins = J->pc[1];
  if (bc_op(ins) == BC_CALLM && bc_b(ins) == 2 && bc_c(ins) == 1) {
    cTValue *func = &J->L->base[bc_a(ins)];
    if (tvisfunc(func) && funcV(func)->c.ffid == FF_select)
      return 1;
  }
  return 0;
}