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
typedef  int /*<<< orphan*/  WithClauseResult ;
struct TYPE_2__ {int /*<<< orphan*/  (* continuous_agg_update_options ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  ContinuousAgg ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  continuous_agg_with_clause_perm_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* ts_cm_functions ; 
 int /*<<< orphan*/ * ts_continuous_agg_with_clause_parse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_with_clause_filter (int /*<<< orphan*/  const*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
process_altercontinuousagg_set_with(ContinuousAgg *cagg, Oid view_relid, const List *defelems)
{
	WithClauseResult *parse_results;
	List *pg_options = NIL, *cagg_options = NIL;

	continuous_agg_with_clause_perm_check(cagg, view_relid);

	ts_with_clause_filter(defelems, &cagg_options, &pg_options);
	if (list_length(pg_options) > 0)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("only timescaledb parameters allowed in WITH clause for continuous "
						"aggregate")));

	if (list_length(cagg_options) > 0)
	{
		parse_results = ts_continuous_agg_with_clause_parse(cagg_options);
		ts_cm_functions->continuous_agg_update_options(cagg, parse_results);
	}
}