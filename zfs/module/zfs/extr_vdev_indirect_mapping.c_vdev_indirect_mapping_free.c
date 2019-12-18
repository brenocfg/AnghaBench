#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* vim_phys; scalar_t__ vim_havecounts; } ;
typedef  TYPE_2__ vdev_indirect_mapping_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_11__ {int /*<<< orphan*/  os_spa; } ;
typedef  TYPE_3__ objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_9__ {int /*<<< orphan*/  vimp_counts_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPA_FEATURE_OBSOLETE_COUNTS ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_object_free (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_decr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_indirect_mapping_close (TYPE_2__*) ; 
 TYPE_2__* vdev_indirect_mapping_open (TYPE_3__*,int /*<<< orphan*/ ) ; 

void
vdev_indirect_mapping_free(objset_t *os, uint64_t object, dmu_tx_t *tx)
{
	vdev_indirect_mapping_t *vim = vdev_indirect_mapping_open(os, object);
	if (vim->vim_havecounts) {
		VERIFY0(dmu_object_free(os, vim->vim_phys->vimp_counts_object,
		    tx));
		spa_feature_decr(os->os_spa, SPA_FEATURE_OBSOLETE_COUNTS, tx);
	}
	vdev_indirect_mapping_close(vim);

	VERIFY0(dmu_object_free(os, object, tx));
}