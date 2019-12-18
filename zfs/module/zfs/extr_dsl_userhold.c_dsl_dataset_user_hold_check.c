#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_5__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_6__ {scalar_t__ dduha_minor; int /*<<< orphan*/  dduha_errlist; int /*<<< orphan*/ * dduha_chkholds; int /*<<< orphan*/ * dduha_holds; } ;
typedef  TYPE_2__ dsl_dataset_user_hold_arg_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ SPA_VERSION_USERREFS ; 
 int /*<<< orphan*/  dmu_tx_is_syncing (int /*<<< orphan*/ *) ; 
 TYPE_1__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int dsl_dataset_hold (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsl_dataset_user_hold_check_one (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_int32 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 size_t fnvlist_num_pairs (int /*<<< orphan*/ *) ; 
 char* fnvpair_value_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (char*,size_t) ; 
 char* kmem_zalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int nvpair_value_string (int /*<<< orphan*/ *,char**) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int
dsl_dataset_user_hold_check(void *arg, dmu_tx_t *tx)
{
	dsl_dataset_user_hold_arg_t *dduha = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	nvlist_t *tmp_holds;

	if (spa_version(dp->dp_spa) < SPA_VERSION_USERREFS)
		return (SET_ERROR(ENOTSUP));

	if (!dmu_tx_is_syncing(tx))
		return (0);

	/*
	 * Ensure the list has no duplicates by copying name/values from
	 * non-unique dduha_holds to unique tmp_holds, and comparing counts.
	 */
	tmp_holds = fnvlist_alloc();
	for (nvpair_t *pair = nvlist_next_nvpair(dduha->dduha_holds, NULL);
	    pair != NULL; pair = nvlist_next_nvpair(dduha->dduha_holds, pair)) {
		size_t len = strlen(nvpair_name(pair)) +
		    strlen(fnvpair_value_string(pair));
		char *nameval = kmem_zalloc(len + 2, KM_SLEEP);
		(void) strcpy(nameval, nvpair_name(pair));
		(void) strcat(nameval, "@");
		(void) strcat(nameval, fnvpair_value_string(pair));
		fnvlist_add_string(tmp_holds, nameval, "");
		kmem_free(nameval, len + 2);
	}
	size_t tmp_count = fnvlist_num_pairs(tmp_holds);
	fnvlist_free(tmp_holds);
	if (tmp_count != fnvlist_num_pairs(dduha->dduha_holds))
		return (SET_ERROR(EEXIST));
	for (nvpair_t *pair = nvlist_next_nvpair(dduha->dduha_holds, NULL);
	    pair != NULL; pair = nvlist_next_nvpair(dduha->dduha_holds, pair)) {
		dsl_dataset_t *ds;
		int error = 0;
		char *htag, *name;

		/* must be a snapshot */
		name = nvpair_name(pair);
		if (strchr(name, '@') == NULL)
			error = SET_ERROR(EINVAL);

		if (error == 0)
			error = nvpair_value_string(pair, &htag);

		if (error == 0)
			error = dsl_dataset_hold(dp, name, FTAG, &ds);

		if (error == 0) {
			error = dsl_dataset_user_hold_check_one(ds, htag,
			    dduha->dduha_minor != 0, tx);
			dsl_dataset_rele(ds, FTAG);
		}

		if (error == 0) {
			fnvlist_add_string(dduha->dduha_chkholds, name, htag);
		} else {
			/*
			 * We register ENOENT errors so they can be correctly
			 * reported if needed, such as when all holds fail.
			 */
			fnvlist_add_int32(dduha->dduha_errlist, name, error);
			if (error != ENOENT)
				return (error);
		}
	}

	return (0);
}