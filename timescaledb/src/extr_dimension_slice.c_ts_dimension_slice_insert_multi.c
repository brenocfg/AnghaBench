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
typedef  size_t Size ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  DimensionSlice ;
typedef  int /*<<< orphan*/  Catalog ;

/* Variables and functions */
 int /*<<< orphan*/  DIMENSION_SLICE ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  catalog_get_table_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dimension_slice_insert_relation (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_catalog_get () ; 

void
ts_dimension_slice_insert_multi(DimensionSlice **slices, Size num_slices)
{
	Catalog *catalog = ts_catalog_get();
	Relation rel;
	Size i;

	rel = heap_open(catalog_get_table_id(catalog, DIMENSION_SLICE), RowExclusiveLock);

	for (i = 0; i < num_slices; i++)
		dimension_slice_insert_relation(rel, slices[i]);

	heap_close(rel, RowExclusiveLock);
}