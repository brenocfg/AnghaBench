#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_15__ {int os_flags; } ;
typedef  TYPE_2__ objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  from_ivset_guid ;
struct TYPE_16__ {int /*<<< orphan*/  ds_object; int /*<<< orphan*/  ds_bp_rwlock; } ;
typedef  TYPE_3__ dsl_dataset_t ;
struct TYPE_17__ {scalar_t__ dn_nlevels; scalar_t__ dn_datablksz; scalar_t__ dn_indblkshift; scalar_t__ dn_nblkptr; } ;
typedef  TYPE_4__ dnode_t ;
struct TYPE_18__ {TYPE_1__* tx_pool; } ;
typedef  TYPE_5__ dmu_tx_t ;
typedef  scalar_t__ dmu_objset_type_t ;
struct TYPE_14__ {int /*<<< orphan*/  dp_meta_objset; int /*<<< orphan*/  dp_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int) ; 
 int /*<<< orphan*/  BP_IS_HOLE (int /*<<< orphan*/ ) ; 
 TYPE_4__* DMU_META_DNODE (TYPE_2__*) ; 
 scalar_t__ DMU_OST_ZFS ; 
 scalar_t__ DMU_OST_ZVOL ; 
 scalar_t__ DN_MAX_INDBLKSHIFT ; 
 scalar_t__ DN_MAX_LEVELS ; 
 scalar_t__ DN_MAX_NBLKPTR ; 
 scalar_t__ DN_MIN_INDBLKSHIFT ; 
 int /*<<< orphan*/  DS_FIELD_IVSET_GUID ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  FTAG ; 
 int OBJSET_FLAG_USERACCOUNTING_COMPLETE ; 
 int OBJSET_FLAG_USEROBJACCOUNTING_COMPLETE ; 
 int /*<<< orphan*/  RW_READER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ SPA_MINBLOCKSIZE ; 
 int /*<<< orphan*/  ZFS_ERR_FROM_IVSET_GUID_MISMATCH ; 
 int /*<<< orphan*/  ZFS_ERR_FROM_IVSET_GUID_MISSING ; 
 scalar_t__ ZIO_CHECKSUM_LEGACY_FUNCTIONS ; 
 scalar_t__ ZIO_COMPRESS_LEGACY_FUNCTIONS ; 
 scalar_t__ ZIO_OBJSET_MAC_LEN ; 
 int dmu_objset_from_ds (TYPE_3__*,TYPE_2__**) ; 
 int /*<<< orphan*/  dsl_dataset_get_blkptr (TYPE_3__*) ; 
 int nvlist_lookup_uint64 (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int nvlist_lookup_uint8_array (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  rrw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrw_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_maxblocksize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  zfs_disable_ivset_guid_check ; 

__attribute__((used)) static int
dsl_crypto_recv_raw_objset_check(dsl_dataset_t *ds, dsl_dataset_t *fromds,
    dmu_objset_type_t ostype, nvlist_t *nvl, dmu_tx_t *tx)
{
	int ret;
	objset_t *os;
	dnode_t *mdn;
	uint8_t *buf = NULL;
	uint_t len;
	uint64_t intval, nlevels, blksz, ibs;
	uint64_t nblkptr, maxblkid;

	if (ostype != DMU_OST_ZFS && ostype != DMU_OST_ZVOL)
		return (SET_ERROR(EINVAL));

	/* raw receives also need info about the structure of the metadnode */
	ret = nvlist_lookup_uint64(nvl, "mdn_compress", &intval);
	if (ret != 0 || intval >= ZIO_COMPRESS_LEGACY_FUNCTIONS)
		return (SET_ERROR(EINVAL));

	ret = nvlist_lookup_uint64(nvl, "mdn_checksum", &intval);
	if (ret != 0 || intval >= ZIO_CHECKSUM_LEGACY_FUNCTIONS)
		return (SET_ERROR(EINVAL));

	ret = nvlist_lookup_uint64(nvl, "mdn_nlevels", &nlevels);
	if (ret != 0 || nlevels > DN_MAX_LEVELS)
		return (SET_ERROR(EINVAL));

	ret = nvlist_lookup_uint64(nvl, "mdn_blksz", &blksz);
	if (ret != 0 || blksz < SPA_MINBLOCKSIZE)
		return (SET_ERROR(EINVAL));
	else if (blksz > spa_maxblocksize(tx->tx_pool->dp_spa))
		return (SET_ERROR(ENOTSUP));

	ret = nvlist_lookup_uint64(nvl, "mdn_indblkshift", &ibs);
	if (ret != 0 || ibs < DN_MIN_INDBLKSHIFT || ibs > DN_MAX_INDBLKSHIFT)
		return (SET_ERROR(ENOTSUP));

	ret = nvlist_lookup_uint64(nvl, "mdn_nblkptr", &nblkptr);
	if (ret != 0 || nblkptr != DN_MAX_NBLKPTR)
		return (SET_ERROR(ENOTSUP));

	ret = nvlist_lookup_uint64(nvl, "mdn_maxblkid", &maxblkid);
	if (ret != 0)
		return (SET_ERROR(EINVAL));

	ret = nvlist_lookup_uint8_array(nvl, "portable_mac", &buf, &len);
	if (ret != 0 || len != ZIO_OBJSET_MAC_LEN)
		return (SET_ERROR(EINVAL));

	ret = dmu_objset_from_ds(ds, &os);
	if (ret != 0)
		return (ret);

	/*
	 * Useraccounting is not portable and must be done with the keys loaded.
	 * Therefore, whenever we do any kind of receive the useraccounting
	 * must not be present.
	 */
	ASSERT0(os->os_flags & OBJSET_FLAG_USERACCOUNTING_COMPLETE);
	ASSERT0(os->os_flags & OBJSET_FLAG_USEROBJACCOUNTING_COMPLETE);

	mdn = DMU_META_DNODE(os);

	/*
	 * If we already created the objset, make sure its unchangeable
	 * properties match the ones received in the nvlist.
	 */
	rrw_enter(&ds->ds_bp_rwlock, RW_READER, FTAG);
	if (!BP_IS_HOLE(dsl_dataset_get_blkptr(ds)) &&
	    (mdn->dn_nlevels != nlevels || mdn->dn_datablksz != blksz ||
	    mdn->dn_indblkshift != ibs || mdn->dn_nblkptr != nblkptr)) {
		rrw_exit(&ds->ds_bp_rwlock, FTAG);
		return (SET_ERROR(EINVAL));
	}
	rrw_exit(&ds->ds_bp_rwlock, FTAG);

	/*
	 * Check that the ivset guid of the fromds matches the one from the
	 * send stream. Older versions of the encryption code did not have
	 * an ivset guid on the from dataset and did not send one in the
	 * stream. For these streams we provide the
	 * zfs_disable_ivset_guid_check tunable to allow these datasets to
	 * be received with a generated ivset guid.
	 */
	if (fromds != NULL && !zfs_disable_ivset_guid_check) {
		uint64_t from_ivset_guid = 0;
		intval = 0;

		(void) nvlist_lookup_uint64(nvl, "from_ivset_guid", &intval);
		(void) zap_lookup(tx->tx_pool->dp_meta_objset,
		    fromds->ds_object, DS_FIELD_IVSET_GUID,
		    sizeof (from_ivset_guid), 1, &from_ivset_guid);

		if (intval == 0 || from_ivset_guid == 0)
			return (SET_ERROR(ZFS_ERR_FROM_IVSET_GUID_MISSING));

		if (intval != from_ivset_guid)
			return (SET_ERROR(ZFS_ERR_FROM_IVSET_GUID_MISMATCH));
	}

	return (0);
}