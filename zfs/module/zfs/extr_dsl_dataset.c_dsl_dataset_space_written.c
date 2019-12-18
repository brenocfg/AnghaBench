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
struct TYPE_5__ {int /*<<< orphan*/  zbm_uncompressed_bytes_refd; int /*<<< orphan*/  zbm_compressed_bytes_refd; int /*<<< orphan*/  zbm_referenced_bytes_refd; int /*<<< orphan*/  zbm_creation_time; int /*<<< orphan*/  zbm_creation_txg; int /*<<< orphan*/  zbm_guid; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ zfs_bookmark_phys_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
struct TYPE_6__ {int /*<<< orphan*/  ds_uncompressed_bytes; int /*<<< orphan*/  ds_compressed_bytes; int /*<<< orphan*/  ds_referenced_bytes; int /*<<< orphan*/  ds_creation_time; int /*<<< orphan*/  ds_creation_txg; int /*<<< orphan*/  ds_guid; } ;
typedef  TYPE_2__ dsl_dataset_phys_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_is_before (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* dsl_dataset_phys (int /*<<< orphan*/ *) ; 
 int dsl_dataset_space_written_impl (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
dsl_dataset_space_written(dsl_dataset_t *oldsnap, dsl_dataset_t *new,
    uint64_t *usedp, uint64_t *compp, uint64_t *uncompp)
{
	if (!dsl_dataset_is_before(new, oldsnap, 0))
		return (SET_ERROR(EINVAL));

	zfs_bookmark_phys_t zbm = { 0 };
	dsl_dataset_phys_t *dsp = dsl_dataset_phys(oldsnap);
	zbm.zbm_guid = dsp->ds_guid;
	zbm.zbm_creation_txg = dsp->ds_creation_txg;
	zbm.zbm_creation_time = dsp->ds_creation_time;
	zbm.zbm_referenced_bytes_refd = dsp->ds_referenced_bytes;
	zbm.zbm_compressed_bytes_refd = dsp->ds_compressed_bytes;
	zbm.zbm_uncompressed_bytes_refd = dsp->ds_uncompressed_bytes;

	/*
	 * If oldsnap is the origin (or origin's origin, ...) of new,
	 * we can't easily calculate the effective FBN.  Therefore,
	 * we do not set ZBM_FLAG_HAS_FBN, so that the _impl will calculate
	 * it relative to the correct "next": the next snapshot towards "new",
	 * rather than the next snapshot in oldsnap's dsl_dir.
	 */
	return (dsl_dataset_space_written_impl(&zbm, new,
	    usedp, compp, uncompp));
}