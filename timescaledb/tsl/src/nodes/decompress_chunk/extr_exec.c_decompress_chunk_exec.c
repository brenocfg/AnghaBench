#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_9__ {int ps_TupFromTlist; int /*<<< orphan*/  ps_ProjInfo; scalar_t__ qual; TYPE_3__* ps_ExprContext; } ;
struct TYPE_10__ {TYPE_1__ ps; } ;
struct TYPE_12__ {scalar_t__ custom_ps; TYPE_2__ ss; } ;
struct TYPE_11__ {int /*<<< orphan*/ * ecxt_scantuple; } ;
typedef  scalar_t__ ExprDoneCond ;
typedef  TYPE_3__ ExprContext ;
typedef  int /*<<< orphan*/  DecompressChunkState ;
typedef  TYPE_4__ CustomScanState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExecProject (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ExecQual (scalar_t__,TYPE_3__*,...) ; 
 scalar_t__ ExprEndResult ; 
 scalar_t__ ExprMultipleResult ; 
 int /*<<< orphan*/  InstrCountFiltered1 (TYPE_4__*,int) ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  ResetExprContext (TYPE_3__*) ; 
 scalar_t__ TupIsNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * decompress_chunk_create_tuple (int /*<<< orphan*/ *) ; 

__attribute__((used)) static TupleTableSlot *
decompress_chunk_exec(CustomScanState *node)
{
	DecompressChunkState *state = (DecompressChunkState *) node;
	ExprContext *econtext = node->ss.ps.ps_ExprContext;
#if PG96
	TupleTableSlot *resultslot;
	ExprDoneCond isDone;
#endif

	if (node->custom_ps == NIL)
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
		TupleTableSlot *slot = decompress_chunk_create_tuple(state);

		if (TupIsNull(slot))
			return NULL;

		econtext->ecxt_scantuple = slot;

#if PG96
		if (node->ss.ps.qual && !ExecQual(node->ss.ps.qual, econtext, false))
#else
		if (node->ss.ps.qual && !ExecQual(node->ss.ps.qual, econtext))
#endif
		{
			InstrCountFiltered1(node, 1);
			ExecClearTuple(slot);
			continue;
		}

		if (!node->ss.ps.ps_ProjInfo)
			return slot;

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