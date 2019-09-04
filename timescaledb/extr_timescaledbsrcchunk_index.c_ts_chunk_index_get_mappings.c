#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ Hypertable ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_chunk_index_hypertable_id_hypertable_index_name_idx_hypertable_id ; 
 int /*<<< orphan*/  Anum_chunk_index_hypertable_id_hypertable_index_name_idx_hypertable_index_name ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CHUNK_INDEX_HYPERTABLE_ID_HYPERTABLE_INDEX_NAME_IDX ; 
 int /*<<< orphan*/  CStringGetDatum (char const*) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_index_collect ; 
 int /*<<< orphan*/  chunk_index_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namein ; 

List *
ts_chunk_index_get_mappings(Hypertable *ht, Oid hypertable_indexrelid)
{
	ScanKeyData scankey[2];
	const char *indexname = get_rel_name(hypertable_indexrelid);
	List *mappings = NIL;

	ScanKeyInit(&scankey[0],
				Anum_chunk_index_hypertable_id_hypertable_index_name_idx_hypertable_id,
				BTEqualStrategyNumber,
				F_INT4EQ,
				Int32GetDatum(ht->fd.id));
	ScanKeyInit(&scankey[1],
				Anum_chunk_index_hypertable_id_hypertable_index_name_idx_hypertable_index_name,
				BTEqualStrategyNumber,
				F_NAMEEQ,
				DirectFunctionCall1(namein, CStringGetDatum((indexname))));

	chunk_index_scan(CHUNK_INDEX_HYPERTABLE_ID_HYPERTABLE_INDEX_NAME_IDX,
					 scankey,
					 2,
					 chunk_index_collect,
					 NULL,
					 &mappings,
					 AccessShareLock);

	return mappings;
}