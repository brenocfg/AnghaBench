#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  state; } ;
struct TYPE_12__ {int /*<<< orphan*/  ecxt_scantuple; } ;
struct TYPE_9__ {TYPE_7__ ps; } ;
struct TYPE_10__ {TYPE_1__ ss; } ;
struct TYPE_11__ {int /*<<< orphan*/  scanslot; TYPE_2__ csstate; } ;
typedef  TYPE_3__ GapFillState ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  TYPE_4__ ExprContext ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ExecEvalExprSwitchContext (int /*<<< orphan*/ *,TYPE_4__*,int*,...) ; 
 int /*<<< orphan*/ * ExecInitExpr (int /*<<< orphan*/ *,TYPE_7__*) ; 
 TYPE_4__* GetPerTupleExprContext (int /*<<< orphan*/ ) ; 

Datum
gapfill_exec_expr(GapFillState *state, Expr *expr, bool *isnull)
{
	ExprState *exprstate = ExecInitExpr(expr, &state->csstate.ss.ps);
	ExprContext *exprcontext = GetPerTupleExprContext(state->csstate.ss.ps.state);

	exprcontext->ecxt_scantuple = state->scanslot;

#if PG96
	return ExecEvalExprSwitchContext(exprstate, exprcontext, isnull, NULL);
#else
	return ExecEvalExprSwitchContext(exprstate, exprcontext, isnull);
#endif
}