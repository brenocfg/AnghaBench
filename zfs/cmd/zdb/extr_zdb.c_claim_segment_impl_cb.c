#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metaslab_claim_impl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_min_claim_txg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_is_concrete (TYPE_1__*) ; 

__attribute__((used)) static void
claim_segment_impl_cb(uint64_t inner_offset, vdev_t *vd, uint64_t offset,
    uint64_t size, void *arg)
{
	/*
	 * This callback was called through a remap from
	 * a device being removed. Therefore, the vdev that
	 * this callback is applied to is a concrete
	 * vdev.
	 */
	ASSERT(vdev_is_concrete(vd));

	VERIFY0(metaslab_claim_impl(vd, offset, size,
	    spa_min_claim_txg(vd->vdev_spa)));
}