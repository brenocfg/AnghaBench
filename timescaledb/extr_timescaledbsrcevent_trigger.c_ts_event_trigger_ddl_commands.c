#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rsinfo ;
typedef  scalar_t__ fmNodePtr ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_10__ {int natts; } ;
struct TYPE_9__ {scalar_t__ resultinfo; } ;
struct TYPE_8__ {int /*<<< orphan*/  econtext; TYPE_3__* setDesc; int /*<<< orphan*/  setResult; int /*<<< orphan*/  allowedModes; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ReturnSetInfo ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__ FunctionCallInfoData ;
typedef  int /*<<< orphan*/  EState ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  CollectedCommand ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateExecutorState () ; 
 int /*<<< orphan*/  CreateExprContext (int /*<<< orphan*/ *) ; 
 int DDL_INFO_NATTS ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecDropSingleTupleTableSlot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecFetchSlotTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeExecutorState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeExprContext (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FunctionCallInvoke (TYPE_2__*) ; 
 int /*<<< orphan*/  InitFunctionCallInfoData (TYPE_2__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * MakeSingleTupleTableSlot (TYPE_3__*) ; 
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  SFRM_Materialize ; 
 int /*<<< orphan*/  T_ReturnSetInfo ; 
 int /*<<< orphan*/  ddl_commands_fmgrinfo ; 
 int /*<<< orphan*/  heap_deform_tuple (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ tuplestore_gettupleslot (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

List *
ts_event_trigger_ddl_commands(void)
{
	ReturnSetInfo rsinfo;
	FunctionCallInfoData fcinfo;
	TupleTableSlot *slot;
	EState *estate = CreateExecutorState();
	List *objects = NIL;

	InitFunctionCallInfoData(fcinfo, &ddl_commands_fmgrinfo, 1, InvalidOid, NULL, NULL);
	MemSet(&rsinfo, 0, sizeof(rsinfo));
	rsinfo.type = T_ReturnSetInfo;
	rsinfo.allowedModes = SFRM_Materialize;
	rsinfo.econtext = CreateExprContext(estate);
	fcinfo.resultinfo = (fmNodePtr) &rsinfo;

	FunctionCallInvoke(&fcinfo);

	slot = MakeSingleTupleTableSlot(rsinfo.setDesc);

	while (tuplestore_gettupleslot(rsinfo.setResult, true, false, slot))
	{
		HeapTuple tuple = ExecFetchSlotTuple(slot);
		CollectedCommand *cmd;
		Datum values[DDL_INFO_NATTS];
		bool nulls[DDL_INFO_NATTS];

		heap_deform_tuple(tuple, rsinfo.setDesc, values, nulls);

		if (rsinfo.setDesc->natts > 8 && !nulls[8])
		{
			cmd = (CollectedCommand *) DatumGetPointer(values[8]);
			objects = lappend(objects, cmd);
		}
	}

	FreeExprContext(rsinfo.econtext, false);
	FreeExecutorState(estate);
	ExecDropSingleTupleTableSlot(slot);

	return objects;
}