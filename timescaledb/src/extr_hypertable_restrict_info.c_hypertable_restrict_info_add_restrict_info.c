#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  num_base_restrictions; } ;
struct TYPE_10__ {int /*<<< orphan*/  opno; int /*<<< orphan*/  args; } ;
struct TYPE_9__ {int /*<<< orphan*/ * clause; } ;
struct TYPE_8__ {int useOr; int /*<<< orphan*/  opno; int /*<<< orphan*/  args; } ;
typedef  TYPE_1__ ScalarArrayOpExpr ;
typedef  TYPE_2__ RestrictInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_3__ OpExpr ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_4__ HypertableRestrictInfo ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
#define  T_OpExpr 129 
#define  T_ScalarArrayOpExpr 128 
 scalar_t__ contain_mutable_functions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dimension_values_create_from_array ; 
 int /*<<< orphan*/  dimension_values_create_from_single_element ; 
 int hypertable_restrict_info_add_expr (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nodeTag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hypertable_restrict_info_add_restrict_info(HypertableRestrictInfo *hri, PlannerInfo *root,
										   RestrictInfo *ri)
{
	bool added = false;

	Expr *e = ri->clause;

	/* Same as constraint_exclusion */
	if (contain_mutable_functions((Node *) e))
		return;

	switch (nodeTag(e))
	{
		case T_OpExpr:
		{
			OpExpr *op_expr = (OpExpr *) e;

			added = hypertable_restrict_info_add_expr(hri,
													  root,
													  op_expr->args,
													  op_expr->opno,
													  dimension_values_create_from_single_element,
													  false);
			break;
		}

		case T_ScalarArrayOpExpr:
		{
			ScalarArrayOpExpr *scalar_expr = (ScalarArrayOpExpr *) e;

			added = hypertable_restrict_info_add_expr(hri,
													  root,
													  scalar_expr->args,
													  scalar_expr->opno,
													  dimension_values_create_from_array,
													  scalar_expr->useOr);
			break;
		}
		default:
			/* we don't support other node types */
			break;
	}

	if (added)
		hri->num_base_restrictions++;
}