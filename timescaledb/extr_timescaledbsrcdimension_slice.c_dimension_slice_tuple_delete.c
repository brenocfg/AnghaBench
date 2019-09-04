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
struct TYPE_3__ {int /*<<< orphan*/  tuple; int /*<<< orphan*/  scanrel; int /*<<< orphan*/  desc; } ;
typedef  TYPE_1__ TupleInfo ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  CatalogSecurityContext ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_dimension_slice_id ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCAN_CONTINUE ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ts_catalog_database_info_become_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_database_info_get () ; 
 int /*<<< orphan*/  ts_catalog_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_catalog_restore_user (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_chunk_constraint_delete_by_dimension_slice_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ScanTupleResult
dimension_slice_tuple_delete(TupleInfo *ti, void *data)
{
	bool isnull;
	Datum dimension_slice_id = heap_getattr(ti->tuple, Anum_dimension_slice_id, ti->desc, &isnull);
	bool *delete_constraints = data;
	CatalogSecurityContext sec_ctx;

	Assert(!isnull);

	/* delete chunk constraints */
	if (NULL != delete_constraints && *delete_constraints)
		ts_chunk_constraint_delete_by_dimension_slice_id(DatumGetInt32(dimension_slice_id));

	ts_catalog_database_info_become_owner(ts_catalog_database_info_get(), &sec_ctx);
	ts_catalog_delete(ti->scanrel, ti->tuple);
	ts_catalog_restore_user(&sec_ctx);

	return SCAN_CONTINUE;
}