#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jit_State ;
struct TYPE_8__ {int /*<<< orphan*/  u64; } ;
struct TYPE_7__ {int /*<<< orphan*/  o; int /*<<< orphan*/  t; int /*<<< orphan*/  i; } ;
typedef  int /*<<< orphan*/  TRef ;
typedef  int /*<<< orphan*/  IROp ;
typedef  TYPE_1__ IRIns ;

/* Variables and functions */
#define  IR_KGC 133 
#define  IR_KINT 132 
#define  IR_KINT64 131 
#define  IR_KNUM 130 
#define  IR_KPRI 129 
#define  IR_KPTR 128 
 int /*<<< orphan*/  TREF_NIL ; 
 int /*<<< orphan*/  TREF_PRI (int /*<<< orphan*/ ) ; 
 TYPE_5__* ir_k64 (TYPE_1__*) ; 
 int /*<<< orphan*/  ir_kgc (TYPE_1__*) ; 
 int /*<<< orphan*/  ir_kptr (TYPE_1__*) ; 
 int /*<<< orphan*/  irt_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_k64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kgc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static TRef snap_replay_const(jit_State *J, IRIns *ir)
{
  /* Only have to deal with constants that can occur in stack slots. */
  switch ((IROp)ir->o) {
  case IR_KPRI: return TREF_PRI(irt_type(ir->t));
  case IR_KINT: return lj_ir_kint(J, ir->i);
  case IR_KGC: return lj_ir_kgc(J, ir_kgc(ir), irt_t(ir->t));
  case IR_KNUM: case IR_KINT64:
    return lj_ir_k64(J, (IROp)ir->o, ir_k64(ir)->u64);
  case IR_KPTR: return lj_ir_kptr(J, ir_kptr(ir));  /* Continuation. */
  default: lua_assert(0); return TREF_NIL; break;
  }
}