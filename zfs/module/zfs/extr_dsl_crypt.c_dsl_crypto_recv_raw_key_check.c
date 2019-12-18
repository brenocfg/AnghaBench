#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_11__ {TYPE_2__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
struct TYPE_12__ {TYPE_1__* tx_pool; } ;
typedef  TYPE_4__ dmu_tx_t ;
typedef  int boolean_t ;
struct TYPE_13__ {int ds_flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  dd_crypto_obj; } ;
struct TYPE_9__ {int /*<<< orphan*/ * dp_meta_objset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int B_FALSE ; 
 int /*<<< orphan*/  DSL_CRYPTO_KEY_CRYPTO_SUITE ; 
 int /*<<< orphan*/  DSL_CRYPTO_KEY_GUID ; 
 int /*<<< orphan*/  DSL_CRYPTO_KEY_HMAC_KEY ; 
 int /*<<< orphan*/  DSL_CRYPTO_KEY_IV ; 
 int /*<<< orphan*/  DSL_CRYPTO_KEY_MAC ; 
 int /*<<< orphan*/  DSL_CRYPTO_KEY_MASTER_KEY ; 
 int /*<<< orphan*/  DSL_CRYPTO_KEY_VERSION ; 
 int DS_FLAG_INCONSISTENT ; 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTSUP ; 
 scalar_t__ MASTER_KEY_MAX_LEN ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ SHA512_HMAC_KEYLEN ; 
 scalar_t__ WRAPPING_IV_LEN ; 
 scalar_t__ WRAPPING_MAC_LEN ; 
 scalar_t__ ZFS_KEYFORMAT_FORMATS ; 
 scalar_t__ ZFS_KEYFORMAT_NONE ; 
 scalar_t__ ZFS_KEYFORMAT_PASSPHRASE ; 
 int /*<<< orphan*/  ZFS_PROP_KEYFORMAT ; 
 int /*<<< orphan*/  ZFS_PROP_PBKDF2_ITERS ; 
 int /*<<< orphan*/  ZFS_PROP_PBKDF2_SALT ; 
 scalar_t__ ZIO_CRYPT_FUNCTIONS ; 
 scalar_t__ ZIO_CRYPT_KEY_CURRENT_VERSION ; 
 scalar_t__ ZIO_CRYPT_OFF ; 
 TYPE_5__* dsl_dataset_phys (TYPE_3__*) ; 
 int nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int nvlist_lookup_uint8_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,scalar_t__*) ; 
 int zap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 

int
dsl_crypto_recv_raw_key_check(dsl_dataset_t *ds, nvlist_t *nvl, dmu_tx_t *tx)
{
	int ret;
	objset_t *mos = tx->tx_pool->dp_meta_objset;
	uint8_t *buf = NULL;
	uint_t len;
	uint64_t intval, key_guid, version;
	boolean_t is_passphrase = B_FALSE;

	ASSERT(dsl_dataset_phys(ds)->ds_flags & DS_FLAG_INCONSISTENT);

	/*
	 * Read and check all the encryption values from the nvlist. We need
	 * all of the fields of a DSL Crypto Key, as well as a fully specified
	 * wrapping key.
	 */
	ret = nvlist_lookup_uint64(nvl, DSL_CRYPTO_KEY_CRYPTO_SUITE, &intval);
	if (ret != 0 || intval >= ZIO_CRYPT_FUNCTIONS ||
	    intval <= ZIO_CRYPT_OFF)
		return (SET_ERROR(EINVAL));

	ret = nvlist_lookup_uint64(nvl, DSL_CRYPTO_KEY_GUID, &intval);
	if (ret != 0)
		return (SET_ERROR(EINVAL));

	/*
	 * If this is an incremental receive make sure the given key guid
	 * matches the one we already have.
	 */
	if (ds->ds_dir->dd_crypto_obj != 0) {
		ret = zap_lookup(mos, ds->ds_dir->dd_crypto_obj,
		    DSL_CRYPTO_KEY_GUID, 8, 1, &key_guid);
		if (ret != 0)
			return (ret);
		if (intval != key_guid)
			return (SET_ERROR(EACCES));
	}

	ret = nvlist_lookup_uint8_array(nvl, DSL_CRYPTO_KEY_MASTER_KEY,
	    &buf, &len);
	if (ret != 0 || len != MASTER_KEY_MAX_LEN)
		return (SET_ERROR(EINVAL));

	ret = nvlist_lookup_uint8_array(nvl, DSL_CRYPTO_KEY_HMAC_KEY,
	    &buf, &len);
	if (ret != 0 || len != SHA512_HMAC_KEYLEN)
		return (SET_ERROR(EINVAL));

	ret = nvlist_lookup_uint8_array(nvl, DSL_CRYPTO_KEY_IV, &buf, &len);
	if (ret != 0 || len != WRAPPING_IV_LEN)
		return (SET_ERROR(EINVAL));

	ret = nvlist_lookup_uint8_array(nvl, DSL_CRYPTO_KEY_MAC, &buf, &len);
	if (ret != 0 || len != WRAPPING_MAC_LEN)
		return (SET_ERROR(EINVAL));

	/*
	 * We don't support receiving old on-disk formats. The version 0
	 * implementation protected several fields in an objset that were
	 * not always portable during a raw receive. As a result, we call
	 * the old version an on-disk errata #3.
	 */
	ret = nvlist_lookup_uint64(nvl, DSL_CRYPTO_KEY_VERSION, &version);
	if (ret != 0 || version != ZIO_CRYPT_KEY_CURRENT_VERSION)
		return (SET_ERROR(ENOTSUP));

	ret = nvlist_lookup_uint64(nvl, zfs_prop_to_name(ZFS_PROP_KEYFORMAT),
	    &intval);
	if (ret != 0 || intval >= ZFS_KEYFORMAT_FORMATS ||
	    intval == ZFS_KEYFORMAT_NONE)
		return (SET_ERROR(EINVAL));

	is_passphrase = (intval == ZFS_KEYFORMAT_PASSPHRASE);

	/*
	 * for raw receives we allow any number of pbkdf2iters since there
	 * won't be a chance for the user to change it.
	 */
	ret = nvlist_lookup_uint64(nvl, zfs_prop_to_name(ZFS_PROP_PBKDF2_ITERS),
	    &intval);
	if (ret != 0 || (is_passphrase == (intval == 0)))
		return (SET_ERROR(EINVAL));

	ret = nvlist_lookup_uint64(nvl, zfs_prop_to_name(ZFS_PROP_PBKDF2_SALT),
	    &intval);
	if (ret != 0 || (is_passphrase == (intval == 0)))
		return (SET_ERROR(EINVAL));

	return (0);
}