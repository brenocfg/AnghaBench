#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ objectType; int /*<<< orphan*/  newschema; int /*<<< orphan*/ * relation; } ;
struct TYPE_5__ {scalar_t__ parsetree; } ;
typedef  TYPE_1__ ProcessUtilityArgs ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Hypertable ;
typedef  int /*<<< orphan*/  Chunk ;
typedef  int /*<<< orphan*/  Cache ;
typedef  TYPE_2__ AlterObjectSchemaStmt ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ OBJECT_TABLE ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RangeVarGetRelid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_add_hypertable (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_cache_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ts_chunk_get_by_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ts_chunk_set_schema (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_get_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_pin () ; 
 int /*<<< orphan*/  ts_hypertable_set_schema (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_altertableschema(ProcessUtilityArgs *args)
{
	AlterObjectSchemaStmt *alterstmt = (AlterObjectSchemaStmt *) args->parsetree;
	Oid relid;
	Cache *hcache;
	Hypertable *ht;

	Assert(alterstmt->objectType == OBJECT_TABLE);

	if (NULL == alterstmt->relation)
		return;

	relid = RangeVarGetRelid(alterstmt->relation, NoLock, true);

	if (!OidIsValid(relid))
		return;

	hcache = ts_hypertable_cache_pin();
	ht = ts_hypertable_cache_get_entry(hcache, relid);

	if (ht == NULL)
	{
		Chunk *chunk = ts_chunk_get_by_relid(relid, 0, false);

		if (NULL != chunk)
			ts_chunk_set_schema(chunk, alterstmt->newschema);
	}
	else
	{
		ts_hypertable_set_schema(ht, alterstmt->newschema);

		process_add_hypertable(args, ht);
	}

	ts_cache_release(hcache);
}