#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
struct TYPE_31__ {TYPE_1__* vdev_aux; struct TYPE_31__* vdev_top; scalar_t__ vdev_isspare; int /*<<< orphan*/  vdev_guid; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int uint_t ;
struct TYPE_30__ {int sav_count; int /*<<< orphan*/ * sav_config; TYPE_2__** sav_vdevs; } ;
struct TYPE_32__ {TYPE_1__ spa_spares; } ;
typedef  TYPE_3__ spa_t ;
typedef  TYPE_2__ nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DATA_TYPE_NVLIST_ARRAY ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  RW_WRITER ; 
 scalar_t__ SCL_ALL ; 
 int /*<<< orphan*/  VDEV_ALLOC_SPARE ; 
 int /*<<< orphan*/  VDEV_CONFIG_SPARE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_SPARES ; 
 TYPE_2__** kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__**,int) ; 
 TYPE_2__** kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_add_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__**,int) ; 
 int /*<<< orphan*/  nvlist_free (TYPE_2__*) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__***,int*) ; 
 scalar_t__ nvlist_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_config_held (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_config_parse (TYPE_3__*,TYPE_2__**,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* spa_lookup_by_guid (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_spare_activate (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_spare_add (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_spare_remove (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_writeable (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_close (TYPE_2__*) ; 
 TYPE_2__* vdev_config_generate (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_free (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_is_dead (TYPE_2__*) ; 
 scalar_t__ vdev_open (TYPE_2__*) ; 
 scalar_t__ vdev_validate_aux (TYPE_2__*) ; 

void
spa_load_spares(spa_t *spa)
{
	nvlist_t **spares;
	uint_t nspares;
	int i;
	vdev_t *vd, *tvd;

#ifndef _KERNEL
	/*
	 * zdb opens both the current state of the pool and the
	 * checkpointed state (if present), with a different spa_t.
	 *
	 * As spare vdevs are shared among open pools, we skip loading
	 * them when we load the checkpointed state of the pool.
	 */
	if (!spa_writeable(spa))
		return;
#endif

	ASSERT(spa_config_held(spa, SCL_ALL, RW_WRITER) == SCL_ALL);

	/*
	 * First, close and free any existing spare vdevs.
	 */
	for (i = 0; i < spa->spa_spares.sav_count; i++) {
		vd = spa->spa_spares.sav_vdevs[i];

		/* Undo the call to spa_activate() below */
		if ((tvd = spa_lookup_by_guid(spa, vd->vdev_guid,
		    B_FALSE)) != NULL && tvd->vdev_isspare)
			spa_spare_remove(tvd);
		vdev_close(vd);
		vdev_free(vd);
	}

	if (spa->spa_spares.sav_vdevs)
		kmem_free(spa->spa_spares.sav_vdevs,
		    spa->spa_spares.sav_count * sizeof (void *));

	if (spa->spa_spares.sav_config == NULL)
		nspares = 0;
	else
		VERIFY(nvlist_lookup_nvlist_array(spa->spa_spares.sav_config,
		    ZPOOL_CONFIG_SPARES, &spares, &nspares) == 0);

	spa->spa_spares.sav_count = (int)nspares;
	spa->spa_spares.sav_vdevs = NULL;

	if (nspares == 0)
		return;

	/*
	 * Construct the array of vdevs, opening them to get status in the
	 * process.   For each spare, there is potentially two different vdev_t
	 * structures associated with it: one in the list of spares (used only
	 * for basic validation purposes) and one in the active vdev
	 * configuration (if it's spared in).  During this phase we open and
	 * validate each vdev on the spare list.  If the vdev also exists in the
	 * active configuration, then we also mark this vdev as an active spare.
	 */
	spa->spa_spares.sav_vdevs = kmem_zalloc(nspares * sizeof (void *),
	    KM_SLEEP);
	for (i = 0; i < spa->spa_spares.sav_count; i++) {
		VERIFY(spa_config_parse(spa, &vd, spares[i], NULL, 0,
		    VDEV_ALLOC_SPARE) == 0);
		ASSERT(vd != NULL);

		spa->spa_spares.sav_vdevs[i] = vd;

		if ((tvd = spa_lookup_by_guid(spa, vd->vdev_guid,
		    B_FALSE)) != NULL) {
			if (!tvd->vdev_isspare)
				spa_spare_add(tvd);

			/*
			 * We only mark the spare active if we were successfully
			 * able to load the vdev.  Otherwise, importing a pool
			 * with a bad active spare would result in strange
			 * behavior, because multiple pool would think the spare
			 * is actively in use.
			 *
			 * There is a vulnerability here to an equally bizarre
			 * circumstance, where a dead active spare is later
			 * brought back to life (onlined or otherwise).  Given
			 * the rarity of this scenario, and the extra complexity
			 * it adds, we ignore the possibility.
			 */
			if (!vdev_is_dead(tvd))
				spa_spare_activate(tvd);
		}

		vd->vdev_top = vd;
		vd->vdev_aux = &spa->spa_spares;

		if (vdev_open(vd) != 0)
			continue;

		if (vdev_validate_aux(vd) == 0)
			spa_spare_add(vd);
	}

	/*
	 * Recompute the stashed list of spares, with status information
	 * this time.
	 */
	VERIFY(nvlist_remove(spa->spa_spares.sav_config, ZPOOL_CONFIG_SPARES,
	    DATA_TYPE_NVLIST_ARRAY) == 0);

	spares = kmem_alloc(spa->spa_spares.sav_count * sizeof (void *),
	    KM_SLEEP);
	for (i = 0; i < spa->spa_spares.sav_count; i++)
		spares[i] = vdev_config_generate(spa,
		    spa->spa_spares.sav_vdevs[i], B_TRUE, VDEV_CONFIG_SPARE);
	VERIFY(nvlist_add_nvlist_array(spa->spa_spares.sav_config,
	    ZPOOL_CONFIG_SPARES, spares, spa->spa_spares.sav_count) == 0);
	for (i = 0; i < spa->spa_spares.sav_count; i++)
		nvlist_free(spares[i]);
	kmem_free(spares, spa->spa_spares.sav_count * sizeof (void *));
}