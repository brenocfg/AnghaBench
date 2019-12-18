#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  paramkind; } ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  PARAM_EXTERN ; 
 int /*<<< orphan*/  Param ; 
#define  T_BoolExpr 139 
#define  T_CaseExpr 138 
#define  T_CaseWhen 137 
#define  T_CoerceViaIO 136 
#define  T_Const 135 
#define  T_DistinctExpr 134 
#define  T_FuncExpr 133 
#define  T_NamedArgExpr 132 
#define  T_NullIfExpr 131 
#define  T_OpExpr 130 
#define  T_Param 129 
#define  T_ScalarArrayOpExpr 128 
 TYPE_1__* castNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int expression_tree_walker (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *,void*),void*) ; 
 int nodeTag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
is_simple_expr_walker(Node *node, void *context)
{
	if (node == NULL)
		return false;

	/*
	 * since expression_tree_walker does early exit on true
	 * logic is reverted and return value of true means expression
	 * is not simple, this is reverted in parent
	 */
	switch (nodeTag(node))
	{
			/*
			 * whitelist expression types we deem safe to execute in a
			 * separate expression context
			 */
		case T_Const:
		case T_FuncExpr:
		case T_NamedArgExpr:
		case T_OpExpr:
		case T_DistinctExpr:
		case T_NullIfExpr:
		case T_ScalarArrayOpExpr:
		case T_BoolExpr:
		case T_CoerceViaIO:
		case T_CaseExpr:
		case T_CaseWhen:
			break;
		case T_Param:
			if (castNode(Param, node)->paramkind != PARAM_EXTERN)
				return true;
			break;
		default:
			return true;
	}
	return expression_tree_walker(node, is_simple_expr_walker, context);
}