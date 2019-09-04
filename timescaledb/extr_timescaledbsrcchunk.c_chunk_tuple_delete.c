#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  tuple; int /*<<< orphan*/  scanrel; int /*<<< orphan*/  mctx; } ;
typedef  TYPE_2__ TupleInfo ;
struct TYPE_10__ {int /*<<< orphan*/  dimension_slice_id; } ;
struct TYPE_14__ {TYPE_1__ fd; } ;
struct TYPE_13__ {int num_constraints; TYPE_5__* constraints; } ;
struct TYPE_12__ {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  TYPE_3__ FormData_chunk ;
typedef  TYPE_4__ ChunkConstraints ;
typedef  TYPE_5__ ChunkConstraint ;
typedef  int /*<<< orphan*/  CatalogSecurityContext ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCAN_CONTINUE ; 
 scalar_t__ is_dimension_constraint (TYPE_5__*) ; 
 int /*<<< orphan*/  ts_bgw_policy_chunk_stats_delete_by_chunk_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_catalog_database_info_become_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_database_info_get () ; 
 int /*<<< orphan*/  ts_catalog_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_catalog_restore_user (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_chunk_constraint_delete_by_chunk_id (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ ts_chunk_constraint_scan_by_dimension_slice_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* ts_chunk_constraints_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunk_index_delete_by_chunk_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ts_dimension_slice_delete_by_id (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ScanTupleResult
chunk_tuple_delete(TupleInfo *ti, void *data)
{
	FormData_chunk *form = (FormData_chunk *) GETSTRUCT(ti->tuple);
	CatalogSecurityContext sec_ctx;
	ChunkConstraints *ccs = ts_chunk_constraints_alloc(2, ti->mctx);
	int i;

	ts_chunk_constraint_delete_by_chunk_id(form->id, ccs);
	ts_chunk_index_delete_by_chunk_id(form->id, true);

	/* Check for dimension slices that are orphaned by the chunk deletion */
	for (i = 0; i < ccs->num_constraints; i++)
	{
		ChunkConstraint *cc = &ccs->constraints[i];

		/*
		 * Delete the dimension slice if there are no remaining constraints
		 * referencing it
		 */
		if (is_dimension_constraint(cc) &&
			ts_chunk_constraint_scan_by_dimension_slice_id(cc->fd.dimension_slice_id,
														   NULL,
														   CurrentMemoryContext) == 0)
			ts_dimension_slice_delete_by_id(cc->fd.dimension_slice_id, false);
	}

	/* Delete any row in bgw_policy_chunk-stats corresponding to this chunk */
	ts_bgw_policy_chunk_stats_delete_by_chunk_id(form->id);

	ts_catalog_database_info_become_owner(ts_catalog_database_info_get(), &sec_ctx);
	ts_catalog_delete(ti->scanrel, ti->tuple);
	ts_catalog_restore_user(&sec_ctx);

	return SCAN_CONTINUE;
}