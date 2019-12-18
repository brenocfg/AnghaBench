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
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_4__ {int /*<<< orphan*/  gapfill_typid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ GapFillState ;
typedef  scalar_t__ GapFillBoundary ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GAPFILL_START ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  exprType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gapfill_datum_get_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gapfill_exec_expr (TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  get_cast_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ *) ; 
 scalar_t__ makeFuncExpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64
get_boundary_expr_value(GapFillState *state, GapFillBoundary boundary, Expr *expr)
{
	Datum arg_value;
	bool isnull;

	/*
	 * add an explicit cast here if types do not match
	 */
	if (exprType((Node *) expr) != state->gapfill_typid)
	{
		Oid cast_oid = get_cast_func(exprType((Node *) expr), state->gapfill_typid);

		expr = (Expr *) makeFuncExpr(cast_oid,
									 state->gapfill_typid,
									 list_make1(expr),
									 InvalidOid,
									 InvalidOid,
									 0);
	}

	arg_value = gapfill_exec_expr(state, expr, &isnull);

	if (isnull)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("invalid time_bucket_gapfill argument: %s cannot be NULL",
						boundary == GAPFILL_START ? "start" : "finish"),
				 errhint(
					 "You can either pass start and finish as arguments or in the WHERE clause")));

	return gapfill_datum_get_internal(arg_value, state->gapfill_typid);
}