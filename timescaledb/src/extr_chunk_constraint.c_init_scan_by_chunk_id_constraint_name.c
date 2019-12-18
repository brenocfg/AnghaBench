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
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_5__ {int /*<<< orphan*/  index; } ;
struct TYPE_6__ {TYPE_1__ ctx; } ;
typedef  TYPE_2__ ScanIterator ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_chunk_constraint_chunk_id_constraint_name_idx_chunk_id ; 
 int /*<<< orphan*/  Anum_chunk_constraint_chunk_id_constraint_name_idx_constraint_name ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CHUNK_CONSTRAINT ; 
 int /*<<< orphan*/  CHUNK_CONSTRAINT_CHUNK_ID_CONSTRAINT_NAME_IDX ; 
 int /*<<< orphan*/  CStringGetDatum (char const*) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  catalog_get_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namein ; 
 int /*<<< orphan*/  ts_catalog_get () ; 
 int /*<<< orphan*/  ts_scan_iterator_scan_key_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_scan_by_chunk_id_constraint_name(ScanIterator *iterator, int32 chunk_id,
									  const char *constraint_name)
{
	iterator->ctx.index = catalog_get_index(ts_catalog_get(),
											CHUNK_CONSTRAINT,
											CHUNK_CONSTRAINT_CHUNK_ID_CONSTRAINT_NAME_IDX);

	ts_scan_iterator_scan_key_init(iterator,
								   Anum_chunk_constraint_chunk_id_constraint_name_idx_chunk_id,
								   BTEqualStrategyNumber,
								   F_INT4EQ,
								   Int32GetDatum(chunk_id));

	ts_scan_iterator_scan_key_init(
		iterator,
		Anum_chunk_constraint_chunk_id_constraint_name_idx_constraint_name,
		BTEqualStrategyNumber,
		F_NAMEEQ,
		DirectFunctionCall1(namein, CStringGetDatum(constraint_name)));
}