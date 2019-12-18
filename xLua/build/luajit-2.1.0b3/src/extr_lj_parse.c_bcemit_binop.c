#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int info; } ;
struct TYPE_16__ {TYPE_1__ s; } ;
struct TYPE_17__ {scalar_t__ t; scalar_t__ f; scalar_t__ k; TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  FuncState ;
typedef  TYPE_3__ ExpDesc ;
typedef  scalar_t__ BinOpr ;

/* Variables and functions */
 scalar_t__ BC_CAT ; 
 scalar_t__ NO_JMP ; 
 scalar_t__ OPR_AND ; 
 scalar_t__ OPR_CONCAT ; 
 scalar_t__ OPR_EQ ; 
 scalar_t__ OPR_GE ; 
 scalar_t__ OPR_GT ; 
 scalar_t__ OPR_LE ; 
 scalar_t__ OPR_LT ; 
 scalar_t__ OPR_NE ; 
 scalar_t__ OPR_OR ; 
 scalar_t__ OPR_POW ; 
 scalar_t__ VRELOCABLE ; 
 int bc_b (int /*<<< orphan*/ ) ; 
 scalar_t__ bc_op (int /*<<< orphan*/ ) ; 
 int bcemit_ABC (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bcemit_arith (int /*<<< orphan*/ *,scalar_t__,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  bcemit_comp (int /*<<< orphan*/ *,scalar_t__,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/ * bcptr (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  expr_discharge (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  expr_free (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  expr_tonextreg (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  expr_toval (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  jmp_append (int /*<<< orphan*/ *,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  setbc_b (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void bcemit_binop(FuncState *fs, BinOpr op, ExpDesc *e1, ExpDesc *e2)
{
  if (op <= OPR_POW) {
    bcemit_arith(fs, op, e1, e2);
  } else if (op == OPR_AND) {
    lua_assert(e1->t == NO_JMP);  /* List must be closed. */
    expr_discharge(fs, e2);
    jmp_append(fs, &e2->f, e1->f);
    *e1 = *e2;
  } else if (op == OPR_OR) {
    lua_assert(e1->f == NO_JMP);  /* List must be closed. */
    expr_discharge(fs, e2);
    jmp_append(fs, &e2->t, e1->t);
    *e1 = *e2;
  } else if (op == OPR_CONCAT) {
    expr_toval(fs, e2);
    if (e2->k == VRELOCABLE && bc_op(*bcptr(fs, e2)) == BC_CAT) {
      lua_assert(e1->u.s.info == bc_b(*bcptr(fs, e2))-1);
      expr_free(fs, e1);
      setbc_b(bcptr(fs, e2), e1->u.s.info);
      e1->u.s.info = e2->u.s.info;
    } else {
      expr_tonextreg(fs, e2);
      expr_free(fs, e2);
      expr_free(fs, e1);
      e1->u.s.info = bcemit_ABC(fs, BC_CAT, 0, e1->u.s.info, e2->u.s.info);
    }
    e1->k = VRELOCABLE;
  } else {
    lua_assert(op == OPR_NE || op == OPR_EQ ||
	       op == OPR_LT || op == OPR_GE || op == OPR_LE || op == OPR_GT);
    bcemit_comp(fs, op, e1, e2);
  }
}