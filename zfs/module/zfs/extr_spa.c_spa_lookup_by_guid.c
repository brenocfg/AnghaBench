#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ vdev_guid; } ;
typedef  TYPE_3__ vdev_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_9__ {int sav_count; TYPE_3__** sav_vdevs; } ;
struct TYPE_8__ {int sav_count; TYPE_3__** sav_vdevs; } ;
struct TYPE_11__ {TYPE_2__ spa_spares; TYPE_1__ spa_l2cache; int /*<<< orphan*/  spa_root_vdev; } ;
typedef  TYPE_4__ spa_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 TYPE_3__* vdev_lookup_by_guid (int /*<<< orphan*/ ,scalar_t__) ; 

vdev_t *
spa_lookup_by_guid(spa_t *spa, uint64_t guid, boolean_t aux)
{
	vdev_t *vd;
	int i;

	if ((vd = vdev_lookup_by_guid(spa->spa_root_vdev, guid)) != NULL)
		return (vd);

	if (aux) {
		for (i = 0; i < spa->spa_l2cache.sav_count; i++) {
			vd = spa->spa_l2cache.sav_vdevs[i];
			if (vd->vdev_guid == guid)
				return (vd);
		}

		for (i = 0; i < spa->spa_spares.sav_count; i++) {
			vd = spa->spa_spares.sav_vdevs[i];
			if (vd->vdev_guid == guid)
				return (vd);
		}
	}

	return (NULL);
}