#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_2__ {int /*<<< orphan*/  drica_blk_birth; int /*<<< orphan*/ * drica_tx; int /*<<< orphan*/ * drica_os; } ;
typedef  TYPE_1__ dbuf_remap_impl_callback_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_ds (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_objset_spa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_block_remapped (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_sync_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_get_dsl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * spa_meta_objset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_vdev_indirect_mark_obsolete (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dbuf_remap_impl_callback(uint64_t vdev, uint64_t offset, uint64_t size,
    void *arg)
{
	dbuf_remap_impl_callback_arg_t *drica = arg;
	objset_t *os = drica->drica_os;
	spa_t *spa = dmu_objset_spa(os);
	dmu_tx_t *tx = drica->drica_tx;

	ASSERT(dsl_pool_sync_context(spa_get_dsl(spa)));

	if (os == spa_meta_objset(spa)) {
		spa_vdev_indirect_mark_obsolete(spa, vdev, offset, size, tx);
	} else {
		dsl_dataset_block_remapped(dmu_objset_ds(os), vdev, offset,
		    size, drica->drica_blk_birth, tx);
	}
}