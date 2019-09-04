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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Catalog ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_INDEX ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  catalog_get_table_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int chunk_index_insert_relation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_catalog_get () ; 

__attribute__((used)) static bool
chunk_index_insert(int32 chunk_id, const char *chunk_index, int32 hypertable_id,
				   const char *hypertable_index)
{
	Catalog *catalog = ts_catalog_get();
	Relation rel;
	bool result;

	rel = heap_open(catalog_get_table_id(catalog, CHUNK_INDEX), RowExclusiveLock);
	result =
		chunk_index_insert_relation(rel, chunk_id, chunk_index, hypertable_id, hypertable_index);
	heap_close(rel, RowExclusiveLock);

	return result;
}