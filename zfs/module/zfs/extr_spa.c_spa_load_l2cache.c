#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
struct TYPE_31__ {scalar_t__ vdev_guid; int vdev_isl2cache; TYPE_3__* vdev_aux; struct TYPE_31__* vdev_top; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int uint_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_33__ {int sav_count; int /*<<< orphan*/ * sav_config; TYPE_1__** sav_vdevs; } ;
struct TYPE_32__ {TYPE_3__ spa_l2cache; } ;
typedef  TYPE_2__ spa_t ;
typedef  TYPE_3__ spa_aux_vdev_t ;
typedef  TYPE_1__ nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DATA_TYPE_NVLIST_ARRAY ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  RW_WRITER ; 
 scalar_t__ SCL_ALL ; 
 int /*<<< orphan*/  VDEV_ALLOC_L2CACHE ; 
 int /*<<< orphan*/  VDEV_CONFIG_L2CACHE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_L2CACHE ; 
 TYPE_1__** kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__**,int) ; 
 int /*<<< orphan*/  l2arc_add_vdev (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  l2arc_remove_vdev (TYPE_1__*) ; 
 scalar_t__ l2arc_vdev_present (TYPE_1__*) ; 
 scalar_t__ nvlist_add_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**,int) ; 
 int /*<<< orphan*/  nvlist_free (TYPE_1__*) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__***,int*) ; 
 scalar_t__ nvlist_lookup_uint64 (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ nvlist_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_config_held (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_config_parse (TYPE_2__*,TYPE_1__**,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_l2cache_activate (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_l2cache_add (TYPE_1__*) ; 
 scalar_t__ spa_l2cache_exists (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  spa_writeable (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_clear_stats (TYPE_1__*) ; 
 TYPE_1__* vdev_config_generate (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_is_dead (TYPE_1__*) ; 
 scalar_t__ vdev_open (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_validate_aux (TYPE_1__*) ; 

void
spa_load_l2cache(spa_t *spa)
{
	nvlist_t **l2cache = NULL;
	uint_t nl2cache;
	int i, j, oldnvdevs;
	uint64_t guid;
	vdev_t *vd, **oldvdevs, **newvdevs;
	spa_aux_vdev_t *sav = &spa->spa_l2cache;

#ifndef _KERNEL
	/*
	 * zdb opens both the current state of the pool and the
	 * checkpointed state (if present), with a different spa_t.
	 *
	 * As L2 caches are part of the ARC which is shared among open
	 * pools, we skip loading them when we load the checkpointed
	 * state of the pool.
	 */
	if (!spa_writeable(spa))
		return;
#endif

	ASSERT(spa_config_held(spa, SCL_ALL, RW_WRITER) == SCL_ALL);

	oldvdevs = sav->sav_vdevs;
	oldnvdevs = sav->sav_count;
	sav->sav_vdevs = NULL;
	sav->sav_count = 0;

	if (sav->sav_config == NULL) {
		nl2cache = 0;
		newvdevs = NULL;
		goto out;
	}

	VERIFY(nvlist_lookup_nvlist_array(sav->sav_config,
	    ZPOOL_CONFIG_L2CACHE, &l2cache, &nl2cache) == 0);
	newvdevs = kmem_alloc(nl2cache * sizeof (void *), KM_SLEEP);

	/*
	 * Process new nvlist of vdevs.
	 */
	for (i = 0; i < nl2cache; i++) {
		VERIFY(nvlist_lookup_uint64(l2cache[i], ZPOOL_CONFIG_GUID,
		    &guid) == 0);

		newvdevs[i] = NULL;
		for (j = 0; j < oldnvdevs; j++) {
			vd = oldvdevs[j];
			if (vd != NULL && guid == vd->vdev_guid) {
				/*
				 * Retain previous vdev for add/remove ops.
				 */
				newvdevs[i] = vd;
				oldvdevs[j] = NULL;
				break;
			}
		}

		if (newvdevs[i] == NULL) {
			/*
			 * Create new vdev
			 */
			VERIFY(spa_config_parse(spa, &vd, l2cache[i], NULL, 0,
			    VDEV_ALLOC_L2CACHE) == 0);
			ASSERT(vd != NULL);
			newvdevs[i] = vd;

			/*
			 * Commit this vdev as an l2cache device,
			 * even if it fails to open.
			 */
			spa_l2cache_add(vd);

			vd->vdev_top = vd;
			vd->vdev_aux = sav;

			spa_l2cache_activate(vd);

			if (vdev_open(vd) != 0)
				continue;

			(void) vdev_validate_aux(vd);

			if (!vdev_is_dead(vd))
				l2arc_add_vdev(spa, vd);
		}
	}

	sav->sav_vdevs = newvdevs;
	sav->sav_count = (int)nl2cache;

	/*
	 * Recompute the stashed list of l2cache devices, with status
	 * information this time.
	 */
	VERIFY(nvlist_remove(sav->sav_config, ZPOOL_CONFIG_L2CACHE,
	    DATA_TYPE_NVLIST_ARRAY) == 0);

	if (sav->sav_count > 0)
		l2cache = kmem_alloc(sav->sav_count * sizeof (void *),
		    KM_SLEEP);
	for (i = 0; i < sav->sav_count; i++)
		l2cache[i] = vdev_config_generate(spa,
		    sav->sav_vdevs[i], B_TRUE, VDEV_CONFIG_L2CACHE);
	VERIFY(nvlist_add_nvlist_array(sav->sav_config,
	    ZPOOL_CONFIG_L2CACHE, l2cache, sav->sav_count) == 0);

out:
	/*
	 * Purge vdevs that were dropped
	 */
	for (i = 0; i < oldnvdevs; i++) {
		uint64_t pool;

		vd = oldvdevs[i];
		if (vd != NULL) {
			ASSERT(vd->vdev_isl2cache);

			if (spa_l2cache_exists(vd->vdev_guid, &pool) &&
			    pool != 0ULL && l2arc_vdev_present(vd))
				l2arc_remove_vdev(vd);
			vdev_clear_stats(vd);
			vdev_free(vd);
		}
	}

	if (oldvdevs)
		kmem_free(oldvdevs, oldnvdevs * sizeof (void *));

	for (i = 0; i < sav->sav_count; i++)
		nvlist_free(l2cache[i]);
	if (sav->sav_count)
		kmem_free(l2cache, sav->sav_count * sizeof (void *));
}