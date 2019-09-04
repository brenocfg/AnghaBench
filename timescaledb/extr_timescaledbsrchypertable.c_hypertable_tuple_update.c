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
typedef  int /*<<< orphan*/  nulls ;
struct TYPE_14__ {TYPE_10__* tuple; int /*<<< orphan*/  scanrel; int /*<<< orphan*/  desc; } ;
typedef  TYPE_3__ TupleInfo ;
struct TYPE_17__ {int /*<<< orphan*/  func_name; int /*<<< orphan*/  func_schema; int /*<<< orphan*/  func; int /*<<< orphan*/ * colname; int /*<<< orphan*/  table_relid; } ;
struct TYPE_12__ {int /*<<< orphan*/  column_name; } ;
struct TYPE_16__ {TYPE_1__ fd; } ;
struct TYPE_13__ {int /*<<< orphan*/  chunk_sizing_func_name; int /*<<< orphan*/  chunk_sizing_func_schema; int /*<<< orphan*/  chunk_target_size; int /*<<< orphan*/  num_dimensions; int /*<<< orphan*/  associated_table_prefix; int /*<<< orphan*/  associated_schema_name; int /*<<< orphan*/  table_name; int /*<<< orphan*/  schema_name; } ;
struct TYPE_15__ {TYPE_2__ fd; int /*<<< orphan*/  chunk_sizing_func; int /*<<< orphan*/  main_table_relid; int /*<<< orphan*/  space; } ;
struct TYPE_11__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  TYPE_4__ Hypertable ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_5__ Dimension ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_6__ ChunkSizingInfo ;
typedef  int /*<<< orphan*/  CatalogSecurityContext ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_hypertable_associated_schema_name ; 
 int /*<<< orphan*/  Anum_hypertable_associated_table_prefix ; 
 int /*<<< orphan*/  Anum_hypertable_chunk_sizing_func_name ; 
 int /*<<< orphan*/  Anum_hypertable_chunk_sizing_func_schema ; 
 int /*<<< orphan*/  Anum_hypertable_chunk_target_size ; 
 int /*<<< orphan*/  Anum_hypertable_num_dimensions ; 
 int /*<<< orphan*/  Anum_hypertable_schema_name ; 
 int /*<<< orphan*/  Anum_hypertable_table_name ; 
 size_t AttrNumberGetAttrOffset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIMENSION_TYPE_OPEN ; 
 int /*<<< orphan*/  Int16GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int64GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NameStr (int /*<<< orphan*/ ) ; 
 int Natts_hypertable ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCAN_DONE ; 
 int /*<<< orphan*/  heap_deform_tuple (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
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
	Datum values[Natts_hypertable];
	bool nulls[Natts_hypertable];
	HeapTuple copy;
	CatalogSecurityContext sec_ctx;

	heap_deform_tuple(ti->tuple, ti->desc, values, nulls);

	values[AttrNumberGetAttrOffset(Anum_hypertable_schema_name)] =
		NameGetDatum(&ht->fd.schema_name);
	values[AttrNumberGetAttrOffset(Anum_hypertable_table_name)] = NameGetDatum(&ht->fd.table_name);
	values[AttrNumberGetAttrOffset(Anum_hypertable_associated_schema_name)] =
		NameGetDatum(&ht->fd.associated_schema_name);
	values[AttrNumberGetAttrOffset(Anum_hypertable_associated_table_prefix)] =
		NameGetDatum(&ht->fd.associated_table_prefix);
	values[AttrNumberGetAttrOffset(Anum_hypertable_num_dimensions)] =
		Int16GetDatum(ht->fd.num_dimensions);
	values[AttrNumberGetAttrOffset(Anum_hypertable_chunk_target_size)] =
		Int64GetDatum(ht->fd.chunk_target_size);

	memset(nulls, 0, sizeof(nulls));

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

		values[AttrNumberGetAttrOffset(Anum_hypertable_chunk_sizing_func_schema)] =
			NameGetDatum(&ht->fd.chunk_sizing_func_schema);
		values[AttrNumberGetAttrOffset(Anum_hypertable_chunk_sizing_func_name)] =
			NameGetDatum(&ht->fd.chunk_sizing_func_name);
	}
	else
	{
		nulls[AttrNumberGetAttrOffset(Anum_hypertable_chunk_sizing_func_schema)] = true;
		nulls[AttrNumberGetAttrOffset(Anum_hypertable_chunk_sizing_func_name)] = true;
	}

	copy = heap_form_tuple(ti->desc, values, nulls);

	ts_catalog_database_info_become_owner(ts_catalog_database_info_get(), &sec_ctx);
	ts_catalog_update_tid(ti->scanrel, &ti->tuple->t_self, copy);
	ts_catalog_restore_user(&sec_ctx);

	heap_freetuple(copy);

	return SCAN_DONE;
}