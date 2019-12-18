#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* tuple; int /*<<< orphan*/  scanrel; int /*<<< orphan*/  desc; } ;
typedef  TYPE_3__ TupleInfo ;
struct TYPE_17__ {int /*<<< orphan*/  func_name; int /*<<< orphan*/  func_schema; int /*<<< orphan*/  func; int /*<<< orphan*/ * colname; int /*<<< orphan*/  table_relid; } ;
struct TYPE_12__ {int /*<<< orphan*/  column_name; } ;
struct TYPE_16__ {TYPE_1__ fd; } ;
struct TYPE_11__ {int /*<<< orphan*/  chunk_sizing_func_name; int /*<<< orphan*/  chunk_sizing_func_schema; } ;
struct TYPE_15__ {TYPE_10__ fd; int /*<<< orphan*/  chunk_sizing_func; int /*<<< orphan*/  main_table_relid; int /*<<< orphan*/  space; } ;
struct TYPE_13__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  TYPE_4__ Hypertable ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_5__ Dimension ;
typedef  TYPE_6__ ChunkSizingInfo ;
typedef  int /*<<< orphan*/  CatalogSecurityContext ;

/* Variables and functions */
 int /*<<< orphan*/  DIMENSION_TYPE_OPEN ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCAN_DONE ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypertable_formdata_make_tuple (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_database_info_become_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_database_info_get () ; 
 int /*<<< orphan*/  ts_catalog_restore_user (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_update_tid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunk_adaptive_sizing_info_validate (TYPE_6__*) ; 
 TYPE_5__* ts_hyperspace_get_dimension (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ScanTupleResult
hypertable_tuple_update(TupleInfo *ti, void *data)
{
	Hypertable *ht = data;
	HeapTuple new_tuple;
	CatalogSecurityContext sec_ctx;

	if (OidIsValid(ht->chunk_sizing_func))
	{
		Dimension *dim = ts_hyperspace_get_dimension(ht->space, DIMENSION_TYPE_OPEN, 0);
		ChunkSizingInfo info = {
			.table_relid = ht->main_table_relid,
			.colname = dim == NULL ? NULL : NameStr(dim->fd.column_name),
			.func = ht->chunk_sizing_func,
		};

		ts_chunk_adaptive_sizing_info_validate(&info);

		namestrcpy(&ht->fd.chunk_sizing_func_schema, NameStr(info.func_schema));
		namestrcpy(&ht->fd.chunk_sizing_func_name, NameStr(info.func_name));
	}
	else
	{
		elog(ERROR, "hypertable_tuple_update chunk_sizing_function cannot be NULL");
	}

	new_tuple = hypertable_formdata_make_tuple(&ht->fd, ti->desc);

	ts_catalog_database_info_become_owner(ts_catalog_database_info_get(), &sec_ctx);
	ts_catalog_update_tid(ti->scanrel, &ti->tuple->t_self, new_tuple);
	ts_catalog_restore_user(&sec_ctx);
	heap_freetuple(new_tuple);
	return SCAN_DONE;
}