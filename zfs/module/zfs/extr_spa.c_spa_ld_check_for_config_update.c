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
struct TYPE_7__ {int vdev_children; TYPE_1__** vdev_child; } ;
typedef  TYPE_2__ vdev_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_8__ {scalar_t__ spa_config_txg; scalar_t__ spa_load_state; int spa_import_flags; TYPE_2__* spa_root_vdev; } ;
typedef  TYPE_3__ spa_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {scalar_t__ vdev_ms_array; } ;

/* Variables and functions */
 int B_FALSE ; 
 int B_TRUE ; 
 int /*<<< orphan*/  SPA_ASYNC_CONFIG_UPDATE ; 
 scalar_t__ SPA_LOAD_IMPORT ; 
 scalar_t__ SPA_LOAD_RECOVER ; 
 int ZFS_IMPORT_VERBATIM ; 
 int /*<<< orphan*/  spa_async_request (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spa_ld_check_for_config_update(spa_t *spa, uint64_t config_cache_txg,
    boolean_t update_config_cache)
{
	vdev_t *rvd = spa->spa_root_vdev;
	int need_update = B_FALSE;

	/*
	 * If the config cache is stale, or we have uninitialized
	 * metaslabs (see spa_vdev_add()), then update the config.
	 *
	 * If this is a verbatim import, trust the current
	 * in-core spa_config and update the disk labels.
	 */
	if (update_config_cache || config_cache_txg != spa->spa_config_txg ||
	    spa->spa_load_state == SPA_LOAD_IMPORT ||
	    spa->spa_load_state == SPA_LOAD_RECOVER ||
	    (spa->spa_import_flags & ZFS_IMPORT_VERBATIM))
		need_update = B_TRUE;

	for (int c = 0; c < rvd->vdev_children; c++)
		if (rvd->vdev_child[c]->vdev_ms_array == 0)
			need_update = B_TRUE;

	/*
	 * Update the config cache asynchronously in case we're the
	 * root pool, in which case the config cache isn't writable yet.
	 */
	if (need_update)
		spa_async_request(spa, SPA_ASYNC_CONFIG_UPDATE);
}