#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  spa_dsl_pool; } ;
typedef  TYPE_1__ spa_t ;
struct TYPE_13__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_2__ dsl_pool_t ;
struct TYPE_14__ {int /*<<< orphan*/  dd_object; } ;
typedef  TYPE_3__ dsl_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  ENOTSUP ; 
 scalar_t__ FREAD ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_FEATURE_ENCRYPTION ; 
 int dsl_dir_hold (TYPE_2__*,char const*,int /*<<< orphan*/ ,TYPE_3__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_rele (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int dsl_pool_hold (char const*,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  dsl_pool_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_is_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spa_keystore_unload_wkey_impl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_mode (TYPE_1__*) ; 
 int spa_open (char const*,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_remove_minors (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int
spa_keystore_unload_wkey(const char *dsname)
{
	int ret = 0;
	dsl_dir_t *dd = NULL;
	dsl_pool_t *dp = NULL;
	spa_t *spa = NULL;

	ret = spa_open(dsname, &spa, FTAG);
	if (ret != 0)
		return (ret);

	/*
	 * Wait for any outstanding txg IO to complete, releasing any
	 * remaining references on the wkey.
	 */
	if (spa_mode(spa) != FREAD)
		txg_wait_synced(spa->spa_dsl_pool, 0);

	spa_close(spa, FTAG);

	/* hold the dsl dir */
	ret = dsl_pool_hold(dsname, FTAG, &dp);
	if (ret != 0)
		goto error;

	if (!spa_feature_is_enabled(dp->dp_spa, SPA_FEATURE_ENCRYPTION)) {
		ret = (SET_ERROR(ENOTSUP));
		goto error;
	}

	ret = dsl_dir_hold(dp, dsname, FTAG, &dd, NULL);
	if (ret != 0) {
		dd = NULL;
		goto error;
	}

	/* unload the wkey */
	ret = spa_keystore_unload_wkey_impl(dp->dp_spa, dd->dd_object);
	if (ret != 0)
		goto error;

	dsl_dir_rele(dd, FTAG);
	dsl_pool_rele(dp, FTAG);

	/* remove any zvols under this ds */
	zvol_remove_minors(dp->dp_spa, dsname, B_TRUE);

	return (0);

error:
	if (dd != NULL)
		dsl_dir_rele(dd, FTAG);
	if (dp != NULL)
		dsl_pool_rele(dp, FTAG);

	return (ret);
}