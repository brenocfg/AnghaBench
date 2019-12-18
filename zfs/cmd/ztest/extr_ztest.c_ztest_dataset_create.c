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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  dsl_crypto_params_t ;
struct TYPE_2__ {int zo_verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  DCP_CMD_NONE ; 
 int /*<<< orphan*/  DMU_OST_OTHER ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRAPPING_KEY_LEN ; 
 unsigned long long ZFS_KEYFORMAT_RAW ; 
 int /*<<< orphan*/  ZFS_PROP_ENCRYPTION ; 
 int /*<<< orphan*/  ZFS_PROP_KEYFORMAT ; 
 int /*<<< orphan*/  ZFS_PROP_KEYLOCATION ; 
 int /*<<< orphan*/  ZFS_PROP_PBKDF2_ITERS ; 
 int /*<<< orphan*/  ZFS_PROP_PBKDF2_SALT ; 
 int /*<<< orphan*/  ZFS_PROP_SYNC ; 
 int /*<<< orphan*/  ZFS_SYNC_ALWAYS ; 
 int ZIO_CRYPT_AES_128_CCM ; 
 int ZIO_CRYPT_FUNCTIONS ; 
 int ZIO_CRYPT_ON ; 
 int /*<<< orphan*/  aes_impl_set (char*) ; 
 int dmu_objset_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_crypto_params_create_nvlist (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_crypto_params_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  fnvlist_add_uint8_array (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcm_impl_set (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 
 int ztest_dsl_prop_set_uint64 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ztest_objset_create_cb ; 
 TYPE_1__ ztest_opts ; 
 int ztest_random (int) ; 
 scalar_t__ ztest_wkeydata ; 

__attribute__((used)) static int
ztest_dataset_create(char *dsname)
{
	int err;
	uint64_t rand;
	dsl_crypto_params_t *dcp = NULL;

	/*
	 * 50% of the time, we create encrypted datasets
	 * using a random cipher suite and a hard-coded
	 * wrapping key.
	 */
	rand = ztest_random(2);
	if (rand != 0) {
		nvlist_t *crypto_args = fnvlist_alloc();
		nvlist_t *props = fnvlist_alloc();

		/* slight bias towards the default cipher suite */
		rand = ztest_random(ZIO_CRYPT_FUNCTIONS);
		if (rand < ZIO_CRYPT_AES_128_CCM)
			rand = ZIO_CRYPT_ON;

		fnvlist_add_uint64(props,
		    zfs_prop_to_name(ZFS_PROP_ENCRYPTION), rand);
		fnvlist_add_uint8_array(crypto_args, "wkeydata",
		    (uint8_t *)ztest_wkeydata, WRAPPING_KEY_LEN);

		/*
		 * These parameters aren't really used by the kernel. They
		 * are simply stored so that userspace knows how to load
		 * the wrapping key.
		 */
		fnvlist_add_uint64(props,
		    zfs_prop_to_name(ZFS_PROP_KEYFORMAT), ZFS_KEYFORMAT_RAW);
		fnvlist_add_string(props,
		    zfs_prop_to_name(ZFS_PROP_KEYLOCATION), "prompt");
		fnvlist_add_uint64(props,
		    zfs_prop_to_name(ZFS_PROP_PBKDF2_SALT), 0ULL);
		fnvlist_add_uint64(props,
		    zfs_prop_to_name(ZFS_PROP_PBKDF2_ITERS), 0ULL);

		VERIFY0(dsl_crypto_params_create_nvlist(DCP_CMD_NONE, props,
		    crypto_args, &dcp));

		/*
		 * Cycle through all available encryption implementations
		 * to verify interoperability.
		 */
		VERIFY0(gcm_impl_set("cycle"));
		VERIFY0(aes_impl_set("cycle"));

		fnvlist_free(crypto_args);
		fnvlist_free(props);
	}

	err = dmu_objset_create(dsname, DMU_OST_OTHER, 0, dcp,
	    ztest_objset_create_cb, NULL);
	dsl_crypto_params_free(dcp, !!err);

	rand = ztest_random(100);
	if (err || rand < 80)
		return (err);

	if (ztest_opts.zo_verbose >= 5)
		(void) printf("Setting dataset %s to sync always\n", dsname);
	return (ztest_dsl_prop_set_uint64(dsname, ZFS_PROP_SYNC,
	    ZFS_SYNC_ALWAYS, B_FALSE));
}