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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  dsl_crypto_params_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DCP_CMD_NONE ; 
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 char* ZPOOL_HIDDEN_ARGS ; 
 int dsl_crypto_params_create_nvlist (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_crypto_params_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_lookup_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int spa_keystore_change_key (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 

__attribute__((used)) static int
zfs_ioc_change_key(const char *dsname, nvlist_t *innvl, nvlist_t *outnvl)
{
	int ret;
	uint64_t cmd = DCP_CMD_NONE;
	dsl_crypto_params_t *dcp = NULL;
	nvlist_t *args = NULL, *hidden_args = NULL;

	if (strchr(dsname, '@') != NULL || strchr(dsname, '%') != NULL) {
		ret = (SET_ERROR(EINVAL));
		goto error;
	}

	(void) nvlist_lookup_uint64(innvl, "crypt_cmd", &cmd);
	(void) nvlist_lookup_nvlist(innvl, "props", &args);
	(void) nvlist_lookup_nvlist(innvl, ZPOOL_HIDDEN_ARGS, &hidden_args);

	ret = dsl_crypto_params_create_nvlist(cmd, args, hidden_args, &dcp);
	if (ret != 0)
		goto error;

	ret = spa_keystore_change_key(dsname, dcp);
	if (ret != 0)
		goto error;

	dsl_crypto_params_free(dcp, B_FALSE);

	return (0);

error:
	dsl_crypto_params_free(dcp, B_TRUE);
	return (ret);
}