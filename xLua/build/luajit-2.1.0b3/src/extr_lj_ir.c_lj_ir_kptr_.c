#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* ir; } ;
struct TYPE_12__ {int* chain; TYPE_1__ cur; } ;
typedef  TYPE_3__ jit_State ;
struct TYPE_11__ {int /*<<< orphan*/  irt; } ;
struct TYPE_13__ {int prev; size_t o; TYPE_2__ t; int /*<<< orphan*/  ptr; scalar_t__ op12; } ;
typedef  int /*<<< orphan*/  TRef ;
typedef  int IRRef1 ;
typedef  int IRRef ;
typedef  size_t IROp ;
typedef  TYPE_4__ IRIns ;

/* Variables and functions */
 TYPE_4__* IR (int) ; 
 int /*<<< orphan*/  IRT_PGC ; 
 size_t LJ_GC64 ; 
 int /*<<< orphan*/  TREF (int,int /*<<< orphan*/ ) ; 
 void* ir_kptr (TYPE_4__*) ; 
 int ir_nextk (TYPE_3__*) ; 
 int ir_nextk64 (TYPE_3__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  setmref (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ u32ptr (void*) ; 

TRef lj_ir_kptr_(jit_State *J, IROp op, void *ptr)
{
  IRIns *ir, *cir = J->cur.ir;
  IRRef ref;
#if LJ_64 && !LJ_GC64
  lua_assert((void *)(uintptr_t)u32ptr(ptr) == ptr);
#endif
  for (ref = J->chain[op]; ref; ref = cir[ref].prev)
    if (ir_kptr(&cir[ref]) == ptr)
      goto found;
#if LJ_GC64
  ref = ir_nextk64(J);
#else
  ref = ir_nextk(J);
#endif
  ir = IR(ref);
  ir->op12 = 0;
  setmref(ir[LJ_GC64].ptr, ptr);
  ir->t.irt = IRT_PGC;
  ir->o = op;
  ir->prev = J->chain[op];
  J->chain[op] = (IRRef1)ref;
found:
  return TREF(ref, IRT_PGC);
}