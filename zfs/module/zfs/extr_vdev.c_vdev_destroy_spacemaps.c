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
struct TYPE_6__ {int vdev_asize; int vdev_ms_shift; int /*<<< orphan*/  vdev_ms_array; TYPE_1__* vdev_spa; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_5__ {int /*<<< orphan*/ * spa_meta_objset; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_object_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int*,int /*<<< orphan*/ ) ; 
 int* kmem_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int*,size_t) ; 
 int /*<<< orphan*/  space_map_free_obj (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_destroy_ms_flush_data (TYPE_2__*,int /*<<< orphan*/ *) ; 

void
vdev_destroy_spacemaps(vdev_t *vd, dmu_tx_t *tx)
{
	if (vd->vdev_ms_array == 0)
		return;

	objset_t *mos = vd->vdev_spa->spa_meta_objset;
	uint64_t array_count = vd->vdev_asize >> vd->vdev_ms_shift;
	size_t array_bytes = array_count * sizeof (uint64_t);
	uint64_t *smobj_array = kmem_alloc(array_bytes, KM_SLEEP);
	VERIFY0(dmu_read(mos, vd->vdev_ms_array, 0,
	    array_bytes, smobj_array, 0));

	for (uint64_t i = 0; i < array_count; i++) {
		uint64_t smobj = smobj_array[i];
		if (smobj == 0)
			continue;

		space_map_free_obj(mos, smobj, tx);
	}

	kmem_free(smobj_array, array_bytes);
	VERIFY0(dmu_object_free(mos, vd->vdev_ms_array, tx));
	vdev_destroy_ms_flush_data(vd, tx);
	vd->vdev_ms_array = 0;
}