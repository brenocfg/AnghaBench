#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
typedef  scalar_t__ int32 ;
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_3__ {scalar_t__ id; scalar_t__ chunk_target_size; int compressed; scalar_t__ compressed_hypertable_id; int /*<<< orphan*/  chunk_sizing_func_name; int /*<<< orphan*/  chunk_sizing_func_schema; int /*<<< orphan*/  num_dimensions; int /*<<< orphan*/  associated_table_prefix; int /*<<< orphan*/  associated_schema_name; int /*<<< orphan*/  table_name; int /*<<< orphan*/  schema_name; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  NameData ;
typedef  int /*<<< orphan*/ * Name ;
typedef  TYPE_1__ FormData_hypertable ;
typedef  int /*<<< orphan*/  CatalogSecurityContext ;
typedef  int /*<<< orphan*/  Catalog ;

/* Variables and functions */
 char* DEFAULT_ASSOCIATED_TABLE_PREFIX_FORMAT ; 
 int /*<<< orphan*/  HYPERTABLE ; 
 scalar_t__ INVALID_HYPERTABLE_ID ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  catalog_get_table_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypertable_insert_relation (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ts_catalog_database_info_become_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_database_info_get () ; 
 int /*<<< orphan*/ * ts_catalog_get () ; 
 int /*<<< orphan*/  ts_catalog_restore_user (int /*<<< orphan*/ *) ; 
 scalar_t__ ts_catalog_table_next_seq_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hypertable_insert(int32 hypertable_id, Name schema_name, Name table_name,
				  Name associated_schema_name, Name associated_table_prefix,
				  Name chunk_sizing_func_schema, Name chunk_sizing_func_name,
				  int64 chunk_target_size, int16 num_dimensions, bool compressed)
{
	Catalog *catalog = ts_catalog_get();
	Relation rel;
	FormData_hypertable fd;

	fd.id = hypertable_id;
	if (fd.id == INVALID_HYPERTABLE_ID)
	{
		CatalogSecurityContext sec_ctx;
		ts_catalog_database_info_become_owner(ts_catalog_database_info_get(), &sec_ctx);
		fd.id = ts_catalog_table_next_seq_id(ts_catalog_get(), HYPERTABLE);
		ts_catalog_restore_user(&sec_ctx);
	}

	namestrcpy(&fd.schema_name, NameStr(*schema_name));
	namestrcpy(&fd.table_name, NameStr(*table_name));
	namestrcpy(&fd.associated_schema_name, NameStr(*associated_schema_name));

	if (NULL == associated_table_prefix)
	{
		NameData default_associated_table_prefix;
		memset(NameStr(default_associated_table_prefix), '\0', NAMEDATALEN);
		snprintf(NameStr(default_associated_table_prefix),
				 NAMEDATALEN,
				 DEFAULT_ASSOCIATED_TABLE_PREFIX_FORMAT,
				 fd.id);
		namestrcpy(&fd.associated_table_prefix, NameStr(default_associated_table_prefix));
	}
	else
	{
		namestrcpy(&fd.associated_table_prefix, NameStr(*associated_table_prefix));
	}
	fd.num_dimensions = num_dimensions;

	namestrcpy(&fd.chunk_sizing_func_schema, NameStr(*chunk_sizing_func_schema));
	namestrcpy(&fd.chunk_sizing_func_name, NameStr(*chunk_sizing_func_name));

	fd.chunk_target_size = chunk_target_size;
	if (fd.chunk_target_size < 0)
		fd.chunk_target_size = 0;

	fd.compressed = compressed;

	/* when creating a hypertable, there is never an associated compressed dual */
	fd.compressed_hypertable_id = INVALID_HYPERTABLE_ID;

	rel = heap_open(catalog_get_table_id(catalog, HYPERTABLE), RowExclusiveLock);
	hypertable_insert_relation(rel, &fd);
	heap_close(rel, RowExclusiveLock);
}