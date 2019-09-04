#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rsinfo ;
typedef  scalar_t__ fmNodePtr ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_7__ {scalar_t__ resultinfo; } ;
struct TYPE_6__ {int /*<<< orphan*/  econtext; int /*<<< orphan*/  setDesc; int /*<<< orphan*/  setResult; int /*<<< orphan*/  allowedModes; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ReturnSetInfo ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__ FunctionCallInfoData ;
typedef  int /*<<< orphan*/  EState ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
#define  ConstraintRelationId 131 
 int /*<<< orphan*/ * CreateExecutorState () ; 
 int /*<<< orphan*/  CreateExprContext (int /*<<< orphan*/ *) ; 
 int DROPPED_OBJECTS_NATTS ; 
 int /*<<< orphan*/  DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 int DatumGetObjectId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecDropSingleTupleTableSlot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecFetchSlotTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeExecutorState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeExprContext (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FunctionCallInvoke (TYPE_2__*) ; 
 int /*<<< orphan*/  InitFunctionCallInfoData (TYPE_2__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * MakeSingleTupleTableSlot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * NIL ; 
#define  NamespaceRelationId 130 
#define  RelationRelationId 129 
 int /*<<< orphan*/  SFRM_Materialize ; 
 int /*<<< orphan*/  T_ReturnSetInfo ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
#define  TriggerRelationId 128 
 int /*<<< orphan*/  dropped_objects_fmgrinfo ; 
 int /*<<< orphan*/ * extract_addrnames (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_deform_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsecond (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lthird (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_event_trigger_drop_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_event_trigger_drop_schema (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_event_trigger_drop_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_event_trigger_drop_table_constraint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_event_trigger_drop_trigger (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_event_trigger_drop_view (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ tuplestore_gettupleslot (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

List *
ts_event_trigger_dropped_objects(void)
{
	ReturnSetInfo rsinfo;
	FunctionCallInfoData fcinfo;
	TupleTableSlot *slot;
	EState *estate = CreateExecutorState();
	List *objects = NIL;

	InitFunctionCallInfoData(fcinfo, &dropped_objects_fmgrinfo, 0, InvalidOid, NULL, NULL);
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
		Datum values[DROPPED_OBJECTS_NATTS];
		bool nulls[DROPPED_OBJECTS_NATTS];
		Oid class_id;
		char *objtype;

		heap_deform_tuple(tuple, rsinfo.setDesc, values, nulls);

		class_id = DatumGetObjectId(values[0]);

		switch (class_id)
		{
			case ConstraintRelationId:
				objtype = TextDatumGetCString(values[6]);
				if (objtype != NULL && strcmp(objtype, "table constraint") == 0)
				{
					List *addrnames = extract_addrnames(DatumGetArrayTypeP(values[10]));

					objects = lappend(objects,
									  make_event_trigger_drop_table_constraint(lthird(addrnames),
																			   linitial(addrnames),
																			   lsecond(addrnames)));
				}
				break;
			case RelationRelationId:
				objtype = TextDatumGetCString(values[6]);
				if (objtype == NULL)
					break;
				if (strcmp(objtype, "index") == 0)
				{
					List *addrnames = extract_addrnames(DatumGetArrayTypeP(values[10]));

					objects = lappend(objects,
									  make_event_trigger_drop_index(lsecond(addrnames),
																	linitial(addrnames)));
				}
				else if (strcmp(objtype, "table") == 0)
				{
					List *addrnames = extract_addrnames(DatumGetArrayTypeP(values[10]));

					objects = lappend(objects,
									  make_event_trigger_drop_table(lsecond(addrnames),
																	linitial(addrnames)));
				}
				else if (strcmp(objtype, "view") == 0)
				{
					List *addrnames = extract_addrnames(DatumGetArrayTypeP(values[10]));

					objects = lappend(objects,
									  make_event_trigger_drop_view(lsecond(addrnames),
																   linitial(addrnames)));
				}
				break;
			case NamespaceRelationId:
			{
				List *addrnames = extract_addrnames(DatumGetArrayTypeP(values[10]));

				objects = lappend(objects, make_event_trigger_drop_schema(linitial(addrnames)));
			}
			break;
			case TriggerRelationId:
			{
				List *addrnames = extract_addrnames(DatumGetArrayTypeP(values[10]));

				objects = lappend(objects,
								  make_event_trigger_drop_trigger(lthird(addrnames),
																  linitial(addrnames),
																  lsecond(addrnames)));
			}
			break;

			default:
				break;
		}
	}

	FreeExprContext(rsinfo.econtext, false);
	FreeExecutorState(estate);
	ExecDropSingleTupleTableSlot(slot);

	return objects;
}