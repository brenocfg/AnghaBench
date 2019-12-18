#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ expr; } ;
typedef  TYPE_4__ TargetEntry ;
struct TYPE_18__ {int /*<<< orphan*/ * plan; } ;
struct TYPE_19__ {TYPE_1__ ps; } ;
struct TYPE_20__ {TYPE_2__ ss; } ;
struct TYPE_24__ {int /*<<< orphan*/  sort_options; TYPE_3__ csstate; } ;
struct TYPE_23__ {scalar_t__ verbose; int /*<<< orphan*/ * rtable; int /*<<< orphan*/  deparse_cxt; } ;
struct TYPE_22__ {int /*<<< orphan*/  data; } ;
struct TYPE_17__ {int /*<<< orphan*/  custom_scan_tlist; } ;
typedef  TYPE_5__ StringInfoData ;
typedef  int /*<<< orphan*/  Plan ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_6__ ExplainState ;
typedef  TYPE_7__ ChunkAppendState ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  CustomScan ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExplainPropertyList (char*,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_5__*,char*) ; 
 TYPE_14__* castNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* deparse_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* get_tle_by_resno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_5__*) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lfourth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * linitial (int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_nth_oid (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lsecond (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lthird (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetStringInfo (TYPE_5__*) ; 
 int /*<<< orphan*/ * set_deparse_context_planstate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_sortorder_options (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
show_sort_group_keys(ChunkAppendState *state, List *ancestors, ExplainState *es)
{
	Plan *plan = state->csstate.ss.ps.plan;
	List *context;
	List *result = NIL;
	StringInfoData sortkeybuf;
	bool useprefix;
	int keyno;
	int nkeys = list_length(linitial(state->sort_options));
	List *sort_indexes = linitial(state->sort_options);
	List *sort_ops = lsecond(state->sort_options);
	List *sort_collations = lthird(state->sort_options);
	List *sort_nulls = lfourth(state->sort_options);

	if (nkeys <= 0)
		return;

	initStringInfo(&sortkeybuf);

	/* Set up deparsing context */
	context = set_deparse_context_planstate(es->deparse_cxt, (Node *) state, ancestors);
	useprefix = (list_length(es->rtable) > 1 || es->verbose);

	for (keyno = 0; keyno < nkeys; keyno++)
	{
		/* find key expression in tlist */
		AttrNumber keyresno = list_nth_oid(sort_indexes, keyno);
		TargetEntry *target =
			get_tle_by_resno(castNode(CustomScan, plan)->custom_scan_tlist, keyresno);
		char *exprstr;

		if (!target)
			elog(ERROR, "no tlist entry for key %d", keyresno);
		/* Deparse the expression, showing any top-level cast */
		exprstr = deparse_expression((Node *) target->expr, context, useprefix, true);
		resetStringInfo(&sortkeybuf);
		appendStringInfoString(&sortkeybuf, exprstr);
		/* Append sort order information, if relevant */
		if (sort_ops != NIL)
			show_sortorder_options(&sortkeybuf,
								   (Node *) target->expr,
								   list_nth_oid(sort_ops, keyno),
								   list_nth_oid(sort_collations, keyno),
								   list_nth_oid(sort_nulls, keyno));
		/* Emit one property-list item per sort key */
		result = lappend(result, pstrdup(sortkeybuf.data));
	}

	ExplainPropertyList("Order", result, es);
}