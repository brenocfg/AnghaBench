#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ zbm_redaction_obj; } ;
typedef  TYPE_1__ zfs_bookmark_phys_t ;
typedef  int /*<<< orphan*/  redaction_list_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
struct TYPE_12__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_2__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
struct TYPE_13__ {int /*<<< orphan*/  dbda_errors; int /*<<< orphan*/  dbda_success; int /*<<< orphan*/  dbda_bmarks; } ;
typedef  TYPE_3__ dsl_bookmark_destroy_arg_t ;
struct TYPE_14__ {int /*<<< orphan*/  tx_pool; } ;
typedef  TYPE_4__ dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EBUSY ; 
 int ENOENT ; 
 int ESRCH ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_FEATURE_BOOKMARKS ; 
 scalar_t__ dmu_tx_is_syncing (TYPE_4__*) ; 
 TYPE_2__* dmu_tx_pool (TYPE_4__*) ; 
 int dsl_bookmark_hold_ds (TYPE_2__*,char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,char**) ; 
 int dsl_bookmark_lookup_impl (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsl_redaction_list_hold_obj (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ dsl_redaction_list_long_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_redaction_list_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fnvlist_add_int32 (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  nvlist_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_is_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dsl_bookmark_destroy_check(void *arg, dmu_tx_t *tx)
{
	dsl_bookmark_destroy_arg_t *dbda = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	int rv = 0;

	ASSERT(nvlist_empty(dbda->dbda_success));
	ASSERT(nvlist_empty(dbda->dbda_errors));

	if (!spa_feature_is_enabled(dp->dp_spa, SPA_FEATURE_BOOKMARKS))
		return (0);

	for (nvpair_t *pair = nvlist_next_nvpair(dbda->dbda_bmarks, NULL);
	    pair != NULL; pair = nvlist_next_nvpair(dbda->dbda_bmarks, pair)) {
		const char *fullname = nvpair_name(pair);
		dsl_dataset_t *ds;
		zfs_bookmark_phys_t bm;
		int error;
		char *shortname;

		error = dsl_bookmark_hold_ds(dp, fullname, &ds,
		    FTAG, &shortname);
		if (error == ENOENT) {
			/* ignore it; the bookmark is "already destroyed" */
			continue;
		}
		if (error == 0) {
			error = dsl_bookmark_lookup_impl(ds, shortname, &bm);
			dsl_dataset_rele(ds, FTAG);
			if (error == ESRCH) {
				/*
				 * ignore it; the bookmark is
				 * "already destroyed"
				 */
				continue;
			}
			if (error == 0 && bm.zbm_redaction_obj != 0) {
				redaction_list_t *rl = NULL;
				error = dsl_redaction_list_hold_obj(tx->tx_pool,
				    bm.zbm_redaction_obj, FTAG, &rl);
				if (error == ENOENT) {
					error = 0;
				} else if (error == 0 &&
				    dsl_redaction_list_long_held(rl)) {
					error = SET_ERROR(EBUSY);
				}
				if (rl != NULL) {
					dsl_redaction_list_rele(rl, FTAG);
				}
			}
		}
		if (error == 0) {
			if (dmu_tx_is_syncing(tx)) {
				fnvlist_add_boolean(dbda->dbda_success,
				    fullname);
			}
		} else {
			fnvlist_add_int32(dbda->dbda_errors, fullname, error);
			rv = error;
		}
	}
	return (rv);
}