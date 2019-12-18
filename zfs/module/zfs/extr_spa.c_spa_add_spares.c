#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  vs_aux; int /*<<< orphan*/  vs_state; } ;
typedef  TYPE_2__ vdev_stat_t ;
typedef  scalar_t__ uint_t ;
typedef  unsigned long long uint64_t ;
struct TYPE_6__ {scalar_t__ sav_count; int /*<<< orphan*/ * sav_config; } ;
struct TYPE_8__ {TYPE_1__ spa_spares; } ;
typedef  TYPE_3__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_CONFIG ; 
 int /*<<< orphan*/  VDEV_AUX_SPARED ; 
 int /*<<< orphan*/  VDEV_STATE_CANT_OPEN ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_SPARES ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_STATS ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 scalar_t__ nvlist_add_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,scalar_t__) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,scalar_t__*) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long long*) ; 
 scalar_t__ nvlist_lookup_uint64_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long long**,scalar_t__*) ; 
 int /*<<< orphan*/  spa_config_held (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_spare_exists (unsigned long long,unsigned long long*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spa_add_spares(spa_t *spa, nvlist_t *config)
{
	nvlist_t **spares;
	uint_t i, nspares;
	nvlist_t *nvroot;
	uint64_t guid;
	vdev_stat_t *vs;
	uint_t vsc;
	uint64_t pool;

	ASSERT(spa_config_held(spa, SCL_CONFIG, RW_READER));

	if (spa->spa_spares.sav_count == 0)
		return;

	VERIFY(nvlist_lookup_nvlist(config,
	    ZPOOL_CONFIG_VDEV_TREE, &nvroot) == 0);
	VERIFY(nvlist_lookup_nvlist_array(spa->spa_spares.sav_config,
	    ZPOOL_CONFIG_SPARES, &spares, &nspares) == 0);
	if (nspares != 0) {
		VERIFY(nvlist_add_nvlist_array(nvroot,
		    ZPOOL_CONFIG_SPARES, spares, nspares) == 0);
		VERIFY(nvlist_lookup_nvlist_array(nvroot,
		    ZPOOL_CONFIG_SPARES, &spares, &nspares) == 0);

		/*
		 * Go through and find any spares which have since been
		 * repurposed as an active spare.  If this is the case, update
		 * their status appropriately.
		 */
		for (i = 0; i < nspares; i++) {
			VERIFY(nvlist_lookup_uint64(spares[i],
			    ZPOOL_CONFIG_GUID, &guid) == 0);
			if (spa_spare_exists(guid, &pool, NULL) &&
			    pool != 0ULL) {
				VERIFY(nvlist_lookup_uint64_array(
				    spares[i], ZPOOL_CONFIG_VDEV_STATS,
				    (uint64_t **)&vs, &vsc) == 0);
				vs->vs_state = VDEV_STATE_CANT_OPEN;
				vs->vs_aux = VDEV_AUX_SPARED;
			}
		}
	}
}