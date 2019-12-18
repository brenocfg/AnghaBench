#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  ccbin; } ;
struct TYPE_11__ {TYPE_2__* rd_att; } ;
struct TYPE_10__ {int /*<<< orphan*/ ** ri_ConstraintExprs; } ;
struct TYPE_9__ {TYPE_1__* constr; } ;
struct TYPE_8__ {int num_check; TYPE_5__* check; } ;
typedef  TYPE_3__ ResultRelInfo ;
typedef  TYPE_4__* Relation ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  int /*<<< orphan*/  Expr ;
typedef  TYPE_5__ ConstrCheck ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * make_ands_implicit (int /*<<< orphan*/ *) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/ * prepare_constr_expr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stringToNode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
create_chunk_rri_constraint_expr(ResultRelInfo *rri, Relation rel)
{
	int ncheck, i;
	ConstrCheck *check;

	Assert(rel->rd_att->constr != NULL && rri->ri_ConstraintExprs == NULL);

	ncheck = rel->rd_att->constr->num_check;
	check = rel->rd_att->constr->check;
#if PG96
	rri->ri_ConstraintExprs = (List **) palloc(ncheck * sizeof(List *));

	for (i = 0; i < ncheck; i++)
	{
		/* ExecQual wants implicit-AND form */
		List *qual = make_ands_implicit(stringToNode(check[i].ccbin));

		rri->ri_ConstraintExprs[i] = (List *) prepare_constr_expr((Expr *) qual);
	}
#else
	rri->ri_ConstraintExprs = (ExprState **) palloc(ncheck * sizeof(ExprState *));

	for (i = 0; i < ncheck; i++)
	{
		Expr *checkconstr = stringToNode(check[i].ccbin);

		rri->ri_ConstraintExprs[i] = prepare_constr_expr(checkconstr);
	}
#endif
}