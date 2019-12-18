#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int vdev_labeltype_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int B_FALSE ; 
 int B_TRUE ; 
 scalar_t__ FREAD ; 
 scalar_t__ POOL_STATE_ACTIVE ; 
 scalar_t__ POOL_STATE_L2CACHE ; 
 scalar_t__ POOL_STATE_SPARE ; 
#define  VDEV_LABEL_CREATE 131 
#define  VDEV_LABEL_L2CACHE 130 
#define  VDEV_LABEL_REPLACE 129 
#define  VDEV_LABEL_SPARE 128 
 int /*<<< orphan*/  ZPOOL_CONFIG_CREATE_TXG ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_STATE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_TXG ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/ * spa_by_guid (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spa_guid_exists (scalar_t__,scalar_t__) ; 
 int spa_has_spare (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ spa_l2cache_exists (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ spa_mode (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_spare_exists (scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vdev_label_read_config (TYPE_1__*,unsigned long long) ; 

__attribute__((used)) static boolean_t
vdev_inuse(vdev_t *vd, uint64_t crtxg, vdev_labeltype_t reason,
    uint64_t *spare_guid, uint64_t *l2cache_guid)
{
	spa_t *spa = vd->vdev_spa;
	uint64_t state, pool_guid, device_guid, txg, spare_pool;
	uint64_t vdtxg = 0;
	nvlist_t *label;

	if (spare_guid)
		*spare_guid = 0ULL;
	if (l2cache_guid)
		*l2cache_guid = 0ULL;

	/*
	 * Read the label, if any, and perform some basic sanity checks.
	 */
	if ((label = vdev_label_read_config(vd, -1ULL)) == NULL)
		return (B_FALSE);

	(void) nvlist_lookup_uint64(label, ZPOOL_CONFIG_CREATE_TXG,
	    &vdtxg);

	if (nvlist_lookup_uint64(label, ZPOOL_CONFIG_POOL_STATE,
	    &state) != 0 ||
	    nvlist_lookup_uint64(label, ZPOOL_CONFIG_GUID,
	    &device_guid) != 0) {
		nvlist_free(label);
		return (B_FALSE);
	}

	if (state != POOL_STATE_SPARE && state != POOL_STATE_L2CACHE &&
	    (nvlist_lookup_uint64(label, ZPOOL_CONFIG_POOL_GUID,
	    &pool_guid) != 0 ||
	    nvlist_lookup_uint64(label, ZPOOL_CONFIG_POOL_TXG,
	    &txg) != 0)) {
		nvlist_free(label);
		return (B_FALSE);
	}

	nvlist_free(label);

	/*
	 * Check to see if this device indeed belongs to the pool it claims to
	 * be a part of.  The only way this is allowed is if the device is a hot
	 * spare (which we check for later on).
	 */
	if (state != POOL_STATE_SPARE && state != POOL_STATE_L2CACHE &&
	    !spa_guid_exists(pool_guid, device_guid) &&
	    !spa_spare_exists(device_guid, NULL, NULL) &&
	    !spa_l2cache_exists(device_guid, NULL))
		return (B_FALSE);

	/*
	 * If the transaction group is zero, then this an initialized (but
	 * unused) label.  This is only an error if the create transaction
	 * on-disk is the same as the one we're using now, in which case the
	 * user has attempted to add the same vdev multiple times in the same
	 * transaction.
	 */
	if (state != POOL_STATE_SPARE && state != POOL_STATE_L2CACHE &&
	    txg == 0 && vdtxg == crtxg)
		return (B_TRUE);

	/*
	 * Check to see if this is a spare device.  We do an explicit check for
	 * spa_has_spare() here because it may be on our pending list of spares
	 * to add.  We also check if it is an l2cache device.
	 */
	if (spa_spare_exists(device_guid, &spare_pool, NULL) ||
	    spa_has_spare(spa, device_guid)) {
		if (spare_guid)
			*spare_guid = device_guid;

		switch (reason) {
		case VDEV_LABEL_CREATE:
		case VDEV_LABEL_L2CACHE:
			return (B_TRUE);

		case VDEV_LABEL_REPLACE:
			return (!spa_has_spare(spa, device_guid) ||
			    spare_pool != 0ULL);

		case VDEV_LABEL_SPARE:
			return (spa_has_spare(spa, device_guid));
		default:
			break;
		}
	}

	/*
	 * Check to see if this is an l2cache device.
	 */
	if (spa_l2cache_exists(device_guid, NULL))
		return (B_TRUE);

	/*
	 * We can't rely on a pool's state if it's been imported
	 * read-only.  Instead we look to see if the pools is marked
	 * read-only in the namespace and set the state to active.
	 */
	if (state != POOL_STATE_SPARE && state != POOL_STATE_L2CACHE &&
	    (spa = spa_by_guid(pool_guid, device_guid)) != NULL &&
	    spa_mode(spa) == FREAD)
		state = POOL_STATE_ACTIVE;

	/*
	 * If the device is marked ACTIVE, then this device is in use by another
	 * pool on the system.
	 */
	return (state == POOL_STATE_ACTIVE);
}