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
 int /*<<< orphan*/  Anum_bgw_job_pkey_idx_id ; 
 int /*<<< orphan*/  BGW_JOB ; 
 int /*<<< orphan*/  BGW_JOB_PKEY_IDX ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  catalog_get_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_catalog_get () ; 
 int /*<<< orphan*/  ts_scan_iterator_scan_key_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_scan_by_job_id(ScanIterator *iterator, int32 job_id)
{
	iterator->ctx.index = catalog_get_index(ts_catalog_get(), BGW_JOB, BGW_JOB_PKEY_IDX);
	ts_scan_iterator_scan_key_init(iterator,
								   Anum_bgw_job_pkey_idx_id,
								   BTEqualStrategyNumber,
								   F_INT4EQ,
								   Int32GetDatum(job_id));
}