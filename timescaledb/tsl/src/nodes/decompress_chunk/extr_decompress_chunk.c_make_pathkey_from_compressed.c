#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ int16 ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  PathKey ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Index ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 scalar_t__ BTGreaterStrategyNumber ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  bms_make_singleton (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exprCollation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ordering_op_properties (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/ * ts_make_pathkey_from_sortinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static PathKey *
make_pathkey_from_compressed(PlannerInfo *root, Index compressed_relid, Expr *expr, Oid ordering_op,
							 bool nulls_first)
{
	Oid opfamily, opcintype, collation;
	int16 strategy;

	/* Find the operator in pg_amop --- failure shouldn't happen */
	if (!get_ordering_op_properties(ordering_op, &opfamily, &opcintype, &strategy))
		elog(ERROR, "operator %u is not a valid ordering operator", ordering_op);

	/* Because SortGroupClause doesn't carry collation, consult the expr */
	collation = exprCollation((Node *) expr);

	return ts_make_pathkey_from_sortinfo(root,
										 expr,
										 NULL,
										 opfamily,
										 opcintype,
										 collation,
										 (strategy == BTGreaterStrategyNumber),
										 nulls_first,
										 0,
										 bms_make_singleton(compressed_relid),
										 true);
}