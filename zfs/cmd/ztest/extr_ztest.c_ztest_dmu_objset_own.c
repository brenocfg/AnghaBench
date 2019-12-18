#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  dsl_crypto_params_t ;
typedef  int /*<<< orphan*/  dmu_objset_type_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  DCP_CMD_NONE ; 
 int EACCES ; 
 int EINVAL ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRAPPING_KEY_LEN ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int dmu_objset_own (char const*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,void*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_crypto_params_create_nvlist (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_crypto_params_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_uint8_array (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int spa_keystore_load_wkey (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ ztest_wkeydata ; 

__attribute__((used)) static int
ztest_dmu_objset_own(const char *name, dmu_objset_type_t type,
    boolean_t readonly, boolean_t decrypt, void *tag, objset_t **osp)
{
	int err;
	char *cp = NULL;
	char ddname[ZFS_MAX_DATASET_NAME_LEN];

	strcpy(ddname, name);
	cp = strchr(ddname, '@');
	if (cp != NULL)
		*cp = '\0';

	err = dmu_objset_own(name, type, readonly, decrypt, tag, osp);
	while (decrypt && err == EACCES) {
		dsl_crypto_params_t *dcp;
		nvlist_t *crypto_args = fnvlist_alloc();

		fnvlist_add_uint8_array(crypto_args, "wkeydata",
		    (uint8_t *)ztest_wkeydata, WRAPPING_KEY_LEN);
		VERIFY0(dsl_crypto_params_create_nvlist(DCP_CMD_NONE, NULL,
		    crypto_args, &dcp));
		err = spa_keystore_load_wkey(ddname, dcp, B_FALSE);
		dsl_crypto_params_free(dcp, B_FALSE);
		fnvlist_free(crypto_args);

		if (err == EINVAL) {
			/*
			 * We couldn't load a key for this dataset so try
			 * the parent. This loop will eventually hit the
			 * encryption root since ztest only makes clones
			 * as children of their origin datasets.
			 */
			cp = strrchr(ddname, '/');
			if (cp == NULL)
				return (err);

			*cp = '\0';
			err = EACCES;
			continue;
		} else if (err != 0) {
			break;
		}

		err = dmu_objset_own(name, type, readonly, decrypt, tag, osp);
		break;
	}

	return (err);
}