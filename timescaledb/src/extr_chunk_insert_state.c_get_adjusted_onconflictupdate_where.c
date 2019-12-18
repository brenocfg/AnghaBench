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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Index ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * ExecInitExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExecInitQual (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INNER_VAR ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ map_variable_attnos_compat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static ExprState *
get_adjusted_onconflictupdate_where(ExprState *hyper_where_state, List *where_quals,
									AttrNumber *map, int map_size, Index varno, Oid rowtype)
{
	bool found_whole_row;

	Assert(where_quals != NIL);
	/* map hypertable attnos -> chunk attnos for the hypertable */
	where_quals = (List *) map_variable_attnos_compat((Node *) where_quals,
													  varno,
													  0,
													  map,
													  map_size,
													  rowtype,
													  &found_whole_row);
	/* map hypertable attnos -> chunk attnos for the "excluded" table */
	where_quals = (List *) map_variable_attnos_compat((Node *) where_quals,
													  INNER_VAR,
													  0,
													  map,
													  map_size,
													  rowtype,
													  &found_whole_row);
#if PG96
	return ExecInitExpr((Expr *) where_quals, NULL);
#else
	return ExecInitQual(where_quals, NULL);
#endif
}