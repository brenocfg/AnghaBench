#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  int16 ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Name ;
typedef  int /*<<< orphan*/  Catalog ;

/* Variables and functions */
 int /*<<< orphan*/  HYPERTABLE ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  catalog_get_table_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypertable_insert_relation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_catalog_get () ; 

__attribute__((used)) static void
hypertable_insert(int32 hypertable_id, Name schema_name, Name table_name,
				  Name associated_schema_name, Name associated_table_prefix,
				  Name chunk_sizing_func_schema, Name chunk_sizing_func_name,
				  int64 chunk_target_size, int16 num_dimensions)
{
	Catalog *catalog = ts_catalog_get();
	Relation rel;

	rel = heap_open(catalog_get_table_id(catalog, HYPERTABLE), RowExclusiveLock);
	hypertable_insert_relation(rel,
							   hypertable_id,
							   schema_name,
							   table_name,
							   associated_schema_name,
							   associated_table_prefix,
							   chunk_sizing_func_schema,
							   chunk_sizing_func_name,
							   chunk_target_size,
							   num_dimensions);
	heap_close(rel, RowExclusiveLock);
}