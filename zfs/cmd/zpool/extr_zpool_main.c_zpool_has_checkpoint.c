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
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {scalar_t__ pcs_state; } ;
typedef  TYPE_1__ pool_checkpoint_stat_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ CS_CHECKPOINT_DISCARDING ; 
 scalar_t__ CS_CHECKPOINT_EXISTS ; 
 scalar_t__ CS_NONE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHECKPOINT_STATS ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * fnvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static boolean_t
zpool_has_checkpoint(zpool_handle_t *zhp)
{
	nvlist_t *config, *nvroot;

	config = zpool_get_config(zhp, NULL);

	if (config != NULL) {
		pool_checkpoint_stat_t *pcs = NULL;
		uint_t c;

		nvroot = fnvlist_lookup_nvlist(config, ZPOOL_CONFIG_VDEV_TREE);
		(void) nvlist_lookup_uint64_array(nvroot,
		    ZPOOL_CONFIG_CHECKPOINT_STATS, (uint64_t **)&pcs, &c);

		if (pcs == NULL || pcs->pcs_state == CS_NONE)
			return (B_FALSE);

		assert(pcs->pcs_state == CS_CHECKPOINT_EXISTS ||
		    pcs->pcs_state == CS_CHECKPOINT_DISCARDING);
		return (B_TRUE);
	}

	return (B_FALSE);
}