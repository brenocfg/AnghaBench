#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_13__ {int /*<<< orphan*/  (* continuous_agg_drop_chunks_by_chunk_id ) (int /*<<< orphan*/ ,TYPE_4__**,int) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_2__ table_name; TYPE_1__ schema_name; } ;
struct TYPE_12__ {TYPE_3__ fd; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_4__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DROP_CASCADE ; 
 int /*<<< orphan*/  DROP_RESTRICT ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetUserId () ; 
#define  HypertableIsMaterialization 130 
#define  HypertableIsMaterializationAndRaw 129 
#define  HypertableIsRawTable 128 
 int /*<<< orphan*/ * NIL ; 
 TYPE_4__** chunk_get_chunks_in_time_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,char*) ; 
 char* palloc (size_t) ; 
 char* quote_identifier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_4__**,int) ; 
 int /*<<< orphan*/  ts_chunk_drop (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* ts_cm_functions ; 
 int ts_continuous_agg_hypertable_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_hypertable_permissions_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_hypertable_relid_to_id (int /*<<< orphan*/ ) ; 

List *
ts_chunk_do_drop_chunks(Oid table_relid, Datum older_than_datum, Datum newer_than_datum,
						Oid older_than_type, Oid newer_than_type, bool cascade,
						bool cascades_to_materializations, int32 log_level)
{
	int i = 0;
	uint64 num_chunks = 0;
	Chunk **chunks;
	List *dropped_chunk_names = NIL;
	const char *schema_name, *table_name;
	int32 hypertable_id = ts_hypertable_relid_to_id(table_relid);

	ts_hypertable_permissions_check(table_relid, GetUserId());

	switch (ts_continuous_agg_hypertable_status(hypertable_id))
	{
		case HypertableIsMaterialization:
		case HypertableIsMaterializationAndRaw:
			elog(ERROR, "cannot drop_chunks on a continuous aggregate materialization table");
		case HypertableIsRawTable:
			if (!cascades_to_materializations)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						 errmsg("cannot drop_chunks on hypertable that has a continuous aggregate "
								"without cascade_to_materializations set to true")));
			break;
		default:
			cascades_to_materializations = false;
			break;
	}

	chunks = chunk_get_chunks_in_time_range(table_relid,
											older_than_datum,
											newer_than_datum,
											older_than_type,
											newer_than_type,
											"drop_chunks",
											CurrentMemoryContext,
											&num_chunks);

	for (; i < num_chunks; i++)
	{
		size_t len;
		char *chunk_name;

		/* store chunk name for output */
		schema_name = quote_identifier(chunks[i]->fd.schema_name.data);
		table_name = quote_identifier(chunks[i]->fd.table_name.data);

		len = strlen(schema_name) + strlen(table_name) + 2;
		chunk_name = palloc(len);

		snprintf(chunk_name, len, "%s.%s", schema_name, table_name);
		dropped_chunk_names = lappend(dropped_chunk_names, chunk_name);

		ts_chunk_drop(chunks[i], (cascade ? DROP_CASCADE : DROP_RESTRICT), log_level);
	}

	if (cascades_to_materializations)
		ts_cm_functions->continuous_agg_drop_chunks_by_chunk_id(hypertable_id, chunks, num_chunks);

	return dropped_chunk_names;
}