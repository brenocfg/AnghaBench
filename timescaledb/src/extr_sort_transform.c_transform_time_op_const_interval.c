#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  args; int /*<<< orphan*/  opno; } ;
typedef  TYPE_1__ OpExpr ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  Const ; 
 scalar_t__ DATEOID ; 
 scalar_t__ INTERVALOID ; 
 scalar_t__ IsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 scalar_t__ TIMESTAMPOID ; 
 scalar_t__ TIMESTAMPTZOID ; 
 int /*<<< orphan*/  Var ; 
 int /*<<< orphan*/ * copyObject (int /*<<< orphan*/ *) ; 
 scalar_t__ exprType (int /*<<< orphan*/ *) ; 
 char* get_opname (int /*<<< orphan*/ ) ; 
 scalar_t__ linitial (int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lsecond (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_sort_transform_expr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline Expr *
transform_time_op_const_interval(OpExpr *op)
{
	/*
	 * optimize timestamp(tz) +/- const interval
	 *
	 * Sort of ts + 1 minute fulfilled by sort of ts
	 */
	if (list_length(op->args) == 2 && IsA(lsecond(op->args), Const))
	{
		Oid left = exprType((Node *) linitial(op->args));
		Oid right = exprType((Node *) lsecond(op->args));

		if ((left == TIMESTAMPOID && right == INTERVALOID) ||
			(left == TIMESTAMPTZOID && right == INTERVALOID) ||
			(left == DATEOID && right == INTERVALOID))
		{
			char *name = get_opname(op->opno);

			if (strncmp(name, "-", NAMEDATALEN) == 0 || strncmp(name, "+", NAMEDATALEN) == 0)
			{
				Expr *first = ts_sort_transform_expr((Expr *) linitial(op->args));

				if (IsA(first, Var))
					return copyObject(first);
			}
		}
	}
	return (Expr *) op;
}