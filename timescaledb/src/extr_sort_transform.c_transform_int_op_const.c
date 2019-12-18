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
 scalar_t__ INT2OID ; 
 scalar_t__ INT4OID ; 
 scalar_t__ INT8OID ; 
 scalar_t__ IsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Var ; 
 int /*<<< orphan*/ * copyObject (int /*<<< orphan*/ *) ; 
 scalar_t__ exprType (int /*<<< orphan*/ *) ; 
 char* get_opname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * linitial (int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lsecond (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_sort_transform_expr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline Expr *
transform_int_op_const(OpExpr *op)
{
	/*
	 * Optimize int op const (or const op int), whenever possible. e.g. sort
	 * of  some_int + const fulfilled by sort of some_int same for the
	 * following operator: + - / *
	 *
	 * Note that / is not commutative and const / var does NOT work (namely it
	 * reverses sort order, which we don't handle yet)
	 */
	if (list_length(op->args) == 2 &&
		(IsA(lsecond(op->args), Const) || IsA(linitial(op->args), Const)))
	{
		Oid left = exprType((Node *) linitial(op->args));
		Oid right = exprType((Node *) lsecond(op->args));

		if ((left == INT8OID && right == INT8OID) || (left == INT4OID && right == INT4OID) ||
			(left == INT2OID && right == INT2OID))
		{
			char *name = get_opname(op->opno);

			if (name[1] == '\0')
			{
				switch (name[0])
				{
					case '-':
					case '+':
					case '*':
						/* commutative cases */
						if (IsA(linitial(op->args), Const))
						{
							Expr *nonconst = ts_sort_transform_expr((Expr *) lsecond(op->args));

							if (IsA(nonconst, Var))
								return copyObject(nonconst);
						}
						else
						{
							Expr *nonconst = ts_sort_transform_expr((Expr *) linitial(op->args));

							if (IsA(nonconst, Var))
								return copyObject(nonconst);
						}
						break;
					case '/':
						/* only if second arg is const */
						if (IsA(lsecond(op->args), Const))
						{
							Expr *nonconst = ts_sort_transform_expr((Expr *) linitial(op->args));

							if (IsA(nonconst, Var))
								return copyObject(nonconst);
						}
						break;
				}
			}
		}
	}
	return (Expr *) op;
}