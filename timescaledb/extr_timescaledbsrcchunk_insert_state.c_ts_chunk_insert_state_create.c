#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_9__ ;
typedef  struct TYPE_43__   TYPE_8__ ;
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_28__ ;
typedef  struct TYPE_35__   TYPE_1__ ;
typedef  struct TYPE_34__   TYPE_11__ ;
typedef  struct TYPE_33__   TYPE_10__ ;

/* Type definitions */
struct TYPE_44__ {int /*<<< orphan*/  slot; scalar_t__ tup_conv_map; TYPE_2__* estate; TYPE_7__* result_relation_info; TYPE_8__* rel; int /*<<< orphan*/  mctx; } ;
struct TYPE_43__ {TYPE_1__* rd_rel; } ;
struct TYPE_42__ {TYPE_5__* ri_TrigDesc; int /*<<< orphan*/ * ri_IndexRelationDescs; TYPE_4__* ri_RelationDesc; } ;
struct TYPE_41__ {int /*<<< orphan*/  main_table_relid; } ;
struct TYPE_40__ {scalar_t__ trig_insert_before_statement; scalar_t__ trig_insert_after_statement; scalar_t__ trig_insert_instead_row; } ;
struct TYPE_39__ {TYPE_3__* rd_rel; } ;
struct TYPE_38__ {scalar_t__ relhasindex; } ;
struct TYPE_37__ {int /*<<< orphan*/  es_query_cxt; } ;
struct TYPE_36__ {int /*<<< orphan*/  reltype; } ;
struct TYPE_35__ {scalar_t__ relkind; } ;
struct TYPE_34__ {int /*<<< orphan*/  table_id; } ;
struct TYPE_33__ {scalar_t__ on_conflict; TYPE_6__* hypertable; TYPE_2__* estate; int /*<<< orphan*/  cmd_type; } ;
typedef  TYPE_7__ ResultRelInfo ;
typedef  TYPE_8__* Relation ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Index ;
typedef  TYPE_9__ ChunkInsertState ;
typedef  TYPE_10__ ChunkDispatch ;
typedef  TYPE_11__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckValidResultRelCompat (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecOpenIndices (TYPE_7__*,int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  MakeTupleTableSlotCompat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ ONCONFLICT_NONE ; 
 scalar_t__ RELKIND_RELATION ; 
 scalar_t__ RLS_ENABLED ; 
 int /*<<< orphan*/  RelationGetDescr (TYPE_8__*) ; 
 TYPE_28__* RelationGetForm (TYPE_8__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  adjust_projections (TYPE_9__*,TYPE_10__*,int /*<<< orphan*/ ) ; 
 scalar_t__ check_enable_rls (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  chunk_insert_state_set_arbiter_indexes (TYPE_9__*,TYPE_10__*,TYPE_8__*) ; 
 scalar_t__ convert_tuples_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_chunk_range_table_entry (TYPE_10__*,TYPE_8__*) ; 
 TYPE_7__* create_chunk_result_relation_info (TYPE_10__*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  gettext_noop (char*) ; 
 int /*<<< orphan*/  heap_close (TYPE_8__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__* palloc0 (int) ; 
 scalar_t__ tuple_conversion_needed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

extern ChunkInsertState *
ts_chunk_insert_state_create(Chunk *chunk, ChunkDispatch *dispatch)
{
	ChunkInsertState *state;
	Relation rel, parent_rel;
	Index rti;
	MemoryContext old_mcxt;
	MemoryContext cis_context = AllocSetContextCreate(dispatch->estate->es_query_cxt,
													  "chunk insert state memory context",
													  ALLOCSET_DEFAULT_SIZES);
	ResultRelInfo *resrelinfo;

	/* permissions NOT checked here; were checked at hypertable level */
	if (check_enable_rls(chunk->table_id, InvalidOid, false) == RLS_ENABLED)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("hypertables do not support row-level security")));

	/*
	 * We must allocate the range table entry on the executor's per-query
	 * context
	 */
	old_mcxt = MemoryContextSwitchTo(dispatch->estate->es_query_cxt);

	rel = heap_open(chunk->table_id, RowExclusiveLock);

	if (rel->rd_rel->relkind != RELKIND_RELATION)
		elog(ERROR, "insert is not on a table");

	rti = create_chunk_range_table_entry(dispatch, rel);

	MemoryContextSwitchTo(cis_context);
	resrelinfo = create_chunk_result_relation_info(dispatch, rel, rti);
	CheckValidResultRelCompat(resrelinfo, dispatch->cmd_type);

	state = palloc0(sizeof(ChunkInsertState));
	state->mctx = cis_context;
	state->rel = rel;
	state->result_relation_info = resrelinfo;
	state->estate = dispatch->estate;

	if (resrelinfo->ri_RelationDesc->rd_rel->relhasindex &&
		resrelinfo->ri_IndexRelationDescs == NULL)
		ExecOpenIndices(resrelinfo, dispatch->on_conflict != ONCONFLICT_NONE);

	if (resrelinfo->ri_TrigDesc != NULL)
	{
		if (resrelinfo->ri_TrigDesc->trig_insert_instead_row ||
			resrelinfo->ri_TrigDesc->trig_insert_after_statement ||
			resrelinfo->ri_TrigDesc->trig_insert_before_statement)
			elog(ERROR, "insert trigger on chunk table not supported");
	}

	/* Set the chunk's arbiter indexes for ON CONFLICT statements */
	if (dispatch->on_conflict != ONCONFLICT_NONE)
		chunk_insert_state_set_arbiter_indexes(state, dispatch, rel);

	/* Set tuple conversion map, if tuple needs conversion */
	parent_rel = heap_open(dispatch->hypertable->main_table_relid, AccessShareLock);

	if (tuple_conversion_needed(RelationGetDescr(parent_rel), RelationGetDescr(rel)))
	{
		state->tup_conv_map = convert_tuples_by_name(RelationGetDescr(parent_rel),
													 RelationGetDescr(rel),
													 gettext_noop("could not convert row type"));
		adjust_projections(state, dispatch, RelationGetForm(rel)->reltype);
	}

	/* Need a tuple table slot to store converted tuples */
	if (state->tup_conv_map)
		state->slot = MakeTupleTableSlotCompat(NULL);

	heap_close(parent_rel, AccessShareLock);

	MemoryContextSwitchTo(old_mcxt);

	return state;
}