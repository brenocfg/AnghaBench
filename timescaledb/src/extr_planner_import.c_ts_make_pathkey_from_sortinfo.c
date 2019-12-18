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
typedef  int /*<<< orphan*/  int16 ;
typedef  int /*<<< orphan*/  Relids ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  PathKey ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Index ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  EquivalenceClass ;

/* Variables and functions */
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  BTGreaterStrategyNumber ; 
 int /*<<< orphan*/  BTLessStrategyNumber ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * get_eclass_for_sort_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * get_mergejoin_opfamilies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_opfamily_member (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * make_canonical_pathkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

PathKey *
ts_make_pathkey_from_sortinfo(PlannerInfo *root, Expr *expr, Relids nullable_relids, Oid opfamily,
							  Oid opcintype, Oid collation, bool reverse_sort, bool nulls_first,
							  Index sortref, Relids rel, bool create_it)
{
	int16 strategy;
	Oid equality_op;
	List *opfamilies;
	EquivalenceClass *eclass;

	strategy = reverse_sort ? BTGreaterStrategyNumber : BTLessStrategyNumber;

	/*
	 * EquivalenceClasses need to contain opfamily lists based on the family
	 * membership of mergejoinable equality operators, which could belong to
	 * more than one opfamily.  So we have to look up the opfamily's equality
	 * operator and get its membership.
	 */
	equality_op = get_opfamily_member(opfamily, opcintype, opcintype, BTEqualStrategyNumber);
	if (!OidIsValid(equality_op)) /* shouldn't happen */
		elog(ERROR,
			 "missing operator %d(%u,%u) in opfamily %u",
			 BTEqualStrategyNumber,
			 opcintype,
			 opcintype,
			 opfamily);
	opfamilies = get_mergejoin_opfamilies(equality_op);
	if (!opfamilies) /* certainly should find some */
		elog(ERROR, "could not find opfamilies for equality operator %u", equality_op);

	/* Now find or (optionally) create a matching EquivalenceClass */
	eclass = get_eclass_for_sort_expr(root,
									  expr,
									  nullable_relids,
									  opfamilies,
									  opcintype,
									  collation,
									  sortref,
									  rel,
									  create_it);

	/* Fail if no EC and !create_it */
	if (!eclass)
		return NULL;

	/* And finally we can find or create a PathKey node */
	return make_canonical_pathkey(root, eclass, opfamily, strategy, nulls_first);
}