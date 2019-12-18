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
struct TYPE_5__ {scalar_t__ vdev_alloc_bias; int /*<<< orphan*/  vdev_top_zap; TYPE_2__* vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
typedef  scalar_t__ vdev_alloc_bias_t ;
struct TYPE_6__ {int /*<<< orphan*/ * spa_meta_objset; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 char* VDEV_ALLOC_BIAS_DEDUP ; 
 char* VDEV_ALLOC_BIAS_LOG ; 
 char* VDEV_ALLOC_BIAS_SPECIAL ; 
 scalar_t__ VDEV_BIAS_DEDUP ; 
 scalar_t__ VDEV_BIAS_LOG ; 
 scalar_t__ VDEV_BIAS_NONE ; 
 scalar_t__ VDEV_BIAS_SPECIAL ; 
 int /*<<< orphan*/  VDEV_TOP_ZAP_ALLOCATION_BIAS ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_activate_allocation_classes (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  zap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vdev_zap_allocation_data(vdev_t *vd, dmu_tx_t *tx)
{
	spa_t *spa = vd->vdev_spa;
	objset_t *mos = spa->spa_meta_objset;
	vdev_alloc_bias_t alloc_bias = vd->vdev_alloc_bias;
	const char *string;

	ASSERT(alloc_bias != VDEV_BIAS_NONE);

	string =
	    (alloc_bias == VDEV_BIAS_LOG) ? VDEV_ALLOC_BIAS_LOG :
	    (alloc_bias == VDEV_BIAS_SPECIAL) ? VDEV_ALLOC_BIAS_SPECIAL :
	    (alloc_bias == VDEV_BIAS_DEDUP) ? VDEV_ALLOC_BIAS_DEDUP : NULL;

	ASSERT(string != NULL);
	VERIFY0(zap_add(mos, vd->vdev_top_zap, VDEV_TOP_ZAP_ALLOCATION_BIAS,
	    1, strlen(string) + 1, string, tx));

	if (alloc_bias == VDEV_BIAS_SPECIAL || alloc_bias == VDEV_BIAS_DEDUP) {
		spa_activate_allocation_classes(spa, tx);
	}
}