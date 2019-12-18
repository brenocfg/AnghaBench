#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_18__ {int /*<<< orphan*/ * dp_meta_objset; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_19__ {scalar_t__ dd_crypto_obj; int dd_object; int /*<<< orphan*/  dd_dbuf; } ;
typedef  TYPE_2__ dsl_dir_t ;
struct TYPE_20__ {void** ds_feature; int /*<<< orphan*/  ds_object; TYPE_2__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
struct TYPE_21__ {TYPE_1__* tx_pool; } ;
typedef  TYPE_4__ dmu_tx_t ;

/* Variables and functions */
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  DD_FIELD_CRYPTO_KEY_OBJ ; 
 int /*<<< orphan*/  DMU_OTN_ZAP_METADATA ; 
 int /*<<< orphan*/  DMU_OT_NONE ; 
 int /*<<< orphan*/  DSL_CRYPTO_KEY_CRYPTO_SUITE ; 
 int /*<<< orphan*/  DSL_CRYPTO_KEY_GUID ; 
 int /*<<< orphan*/  DSL_CRYPTO_KEY_HMAC_KEY ; 
 int /*<<< orphan*/  DSL_CRYPTO_KEY_IV ; 
 int /*<<< orphan*/  DSL_CRYPTO_KEY_MAC ; 
 int /*<<< orphan*/  DSL_CRYPTO_KEY_MASTER_KEY ; 
 int /*<<< orphan*/  DSL_CRYPTO_KEY_REFCOUNT ; 
 int /*<<< orphan*/  DSL_CRYPTO_KEY_VERSION ; 
 size_t SPA_FEATURE_ENCRYPTION ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_PROP_KEYFORMAT ; 
 int /*<<< orphan*/  ZFS_PROP_KEYLOCATION ; 
 int /*<<< orphan*/  ZFS_PROP_PBKDF2_ITERS ; 
 int /*<<< orphan*/  ZFS_PROP_PBKDF2_SALT ; 
 int ZIO_CRYPT_KEY_CURRENT_VERSION ; 
 int /*<<< orphan*/  ZPROP_SRC_LOCAL ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  dsl_crypto_key_sync_impl (int /*<<< orphan*/ *,scalar_t__,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,TYPE_4__*) ; 
 int /*<<< orphan*/  dsl_dataset_activate_feature (int /*<<< orphan*/ ,size_t,void*,TYPE_4__*) ; 
 int /*<<< orphan*/  dsl_dir_get_encryption_root_ddobj (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  dsl_dir_zapify (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  dsl_prop_set_sync_impl (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,char*,TYPE_4__*) ; 
 int fnvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_lookup_uint8_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  zap_add (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,scalar_t__*,TYPE_4__*) ; 
 scalar_t__ zap_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  zap_update (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int,int,int*,TYPE_4__*) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 

void
dsl_crypto_recv_raw_key_sync(dsl_dataset_t *ds, nvlist_t *nvl, dmu_tx_t *tx)
{
	dsl_pool_t *dp = tx->tx_pool;
	objset_t *mos = dp->dp_meta_objset;
	dsl_dir_t *dd = ds->ds_dir;
	uint_t len;
	uint64_t rddobj, one = 1;
	uint8_t *keydata, *hmac_keydata, *iv, *mac;
	uint64_t crypt, key_guid, keyformat, iters, salt;
	uint64_t version = ZIO_CRYPT_KEY_CURRENT_VERSION;
	char *keylocation = "prompt";

	/* lookup the values we need to create the DSL Crypto Key */
	crypt = fnvlist_lookup_uint64(nvl, DSL_CRYPTO_KEY_CRYPTO_SUITE);
	key_guid = fnvlist_lookup_uint64(nvl, DSL_CRYPTO_KEY_GUID);
	keyformat = fnvlist_lookup_uint64(nvl,
	    zfs_prop_to_name(ZFS_PROP_KEYFORMAT));
	iters = fnvlist_lookup_uint64(nvl,
	    zfs_prop_to_name(ZFS_PROP_PBKDF2_ITERS));
	salt = fnvlist_lookup_uint64(nvl,
	    zfs_prop_to_name(ZFS_PROP_PBKDF2_SALT));
	VERIFY0(nvlist_lookup_uint8_array(nvl, DSL_CRYPTO_KEY_MASTER_KEY,
	    &keydata, &len));
	VERIFY0(nvlist_lookup_uint8_array(nvl, DSL_CRYPTO_KEY_HMAC_KEY,
	    &hmac_keydata, &len));
	VERIFY0(nvlist_lookup_uint8_array(nvl, DSL_CRYPTO_KEY_IV, &iv, &len));
	VERIFY0(nvlist_lookup_uint8_array(nvl, DSL_CRYPTO_KEY_MAC, &mac, &len));

	/* if this is a new dataset setup the DSL Crypto Key. */
	if (dd->dd_crypto_obj == 0) {
		/* zapify the dsl dir so we can add the key object to it */
		dmu_buf_will_dirty(dd->dd_dbuf, tx);
		dsl_dir_zapify(dd, tx);

		/* create the DSL Crypto Key on disk and activate the feature */
		dd->dd_crypto_obj = zap_create(mos,
		    DMU_OTN_ZAP_METADATA, DMU_OT_NONE, 0, tx);
		VERIFY0(zap_update(tx->tx_pool->dp_meta_objset,
		    dd->dd_crypto_obj, DSL_CRYPTO_KEY_REFCOUNT,
		    sizeof (uint64_t), 1, &one, tx));
		VERIFY0(zap_update(tx->tx_pool->dp_meta_objset,
		    dd->dd_crypto_obj, DSL_CRYPTO_KEY_VERSION,
		    sizeof (uint64_t), 1, &version, tx));

		dsl_dataset_activate_feature(ds->ds_object,
		    SPA_FEATURE_ENCRYPTION, (void *)B_TRUE, tx);
		ds->ds_feature[SPA_FEATURE_ENCRYPTION] = (void *)B_TRUE;

		/* save the dd_crypto_obj on disk */
		VERIFY0(zap_add(mos, dd->dd_object, DD_FIELD_CRYPTO_KEY_OBJ,
		    sizeof (uint64_t), 1, &dd->dd_crypto_obj, tx));

		/*
		 * Set the keylocation to prompt by default. If keylocation
		 * has been provided via the properties, this will be overridden
		 * later.
		 */
		dsl_prop_set_sync_impl(ds,
		    zfs_prop_to_name(ZFS_PROP_KEYLOCATION),
		    ZPROP_SRC_LOCAL, 1, strlen(keylocation) + 1,
		    keylocation, tx);

		rddobj = dd->dd_object;
	} else {
		VERIFY0(dsl_dir_get_encryption_root_ddobj(dd, &rddobj));
	}

	/* sync the key data to the ZAP object on disk */
	dsl_crypto_key_sync_impl(mos, dd->dd_crypto_obj, crypt,
	    rddobj, key_guid, iv, mac, keydata, hmac_keydata, keyformat, salt,
	    iters, tx);
}