#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_12__ {scalar_t__ num_append_subplans; } ;
struct TYPE_8__ {int ps_TupFromTlist; int /*<<< orphan*/  ps_ProjInfo; TYPE_3__* ps_ExprContext; } ;
struct TYPE_9__ {TYPE_1__ ps; } ;
struct TYPE_11__ {TYPE_2__ ss; int /*<<< orphan*/  custom_ps; } ;
struct TYPE_10__ {int /*<<< orphan*/ * ecxt_scantuple; } ;
typedef  scalar_t__ ExprDoneCond ;
typedef  TYPE_3__ ExprContext ;
typedef  TYPE_4__ CustomScanState ;
typedef  TYPE_5__ ConstraintAwareAppendState ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecProcNode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ExecProject (int /*<<< orphan*/ ,...) ; 
 scalar_t__ ExprEndResult ; 
 scalar_t__ ExprMultipleResult ; 
 int /*<<< orphan*/  ResetExprContext (TYPE_3__*) ; 
 scalar_t__ TupIsNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ ) ; 

__attribute__((used)) static TupleTableSlot *
ca_append_exec(CustomScanState *node)
{
	ConstraintAwareAppendState *state = (ConstraintAwareAppendState *) node;
	TupleTableSlot *subslot;
	ExprContext *econtext = node->ss.ps.ps_ExprContext;
#if PG96
	TupleTableSlot *resultslot;
	ExprDoneCond isDone;
#endif

	/*
	 * Check if all append subplans were pruned. In that case there is nothing
	 * to do.
	 */
	if (state->num_append_subplans == 0)
		return NULL;

#if PG96
	if (node->ss.ps.ps_TupFromTlist)
	{
		resultslot = ExecProject(node->ss.ps.ps_ProjInfo, &isDone);

		if (isDone == ExprMultipleResult)
			return resultslot;

		node->ss.ps.ps_TupFromTlist = false;
	}
#endif

	ResetExprContext(econtext);

	while (true)
	{
		subslot = ExecProcNode(linitial(node->custom_ps));

		if (TupIsNull(subslot))
			return NULL;

		if (!node->ss.ps.ps_ProjInfo)
			return subslot;

		econtext->ecxt_scantuple = subslot;

#if PG96
		resultslot = ExecProject(node->ss.ps.ps_ProjInfo, &isDone);

		if (isDone != ExprEndResult)
		{
			node->ss.ps.ps_TupFromTlist = (isDone == ExprMultipleResult);
			return resultslot;
		}
#else
		return ExecProject(node->ss.ps.ps_ProjInfo);
#endif
	}
}