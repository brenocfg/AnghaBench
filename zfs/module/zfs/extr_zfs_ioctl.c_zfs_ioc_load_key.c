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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  dsl_crypto_params_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DCP_CMD_NONE ; 
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPOOL_HIDDEN_ARGS ; 
 int dsl_crypto_params_create_nvlist (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_crypto_params_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/ *,char*) ; 
 int spa_keystore_load_wkey (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 

__attribute__((used)) static int
zfs_ioc_load_key(const char *dsname, nvlist_t *innvl, nvlist_t *outnvl)
{
	int ret;
	dsl_crypto_params_t *dcp = NULL;
	nvlist_t *hidden_args;
	boolean_t noop = nvlist_exists(innvl, "noop");

	if (strchr(dsname, '@') != NULL || strchr(dsname, '%') != NULL) {
		ret = SET_ERROR(EINVAL);
		goto error;
	}

	hidden_args = fnvlist_lookup_nvlist(innvl, ZPOOL_HIDDEN_ARGS);

	ret = dsl_crypto_params_create_nvlist(DCP_CMD_NONE, NULL,
	    hidden_args, &dcp);
	if (ret != 0)
		goto error;

	ret = spa_keystore_load_wkey(dsname, dcp, noop);
	if (ret != 0)
		goto error;

	dsl_crypto_params_free(dcp, noop);

	return (0);

error:
	dsl_crypto_params_free(dcp, B_TRUE);
	return (ret);
}