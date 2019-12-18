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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  redaction_list_phys_t ;
struct TYPE_5__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_1__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
struct TYPE_6__ {int dbcra_numsnaps; int /*<<< orphan*/  dbcra_bmark; int /*<<< orphan*/  dbcra_snap; } ;
typedef  TYPE_2__ dsl_bookmark_create_redacted_arg_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  E2BIG ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_FEATURE_REDACTION_BOOKMARKS ; 
 int dmu_bonus_max () ; 
 TYPE_1__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int dsl_bookmark_create_check_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dsl_dataset_hold (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_is_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dsl_bookmark_create_redacted_check(void *arg, dmu_tx_t *tx)
{
	dsl_bookmark_create_redacted_arg_t *dbcra = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_dataset_t *snapds;
	int rv = 0;

	if (!spa_feature_is_enabled(dp->dp_spa,
	    SPA_FEATURE_REDACTION_BOOKMARKS))
		return (SET_ERROR(ENOTSUP));
	/*
	 * If the list of redact snaps will not fit in the bonus buffer with
	 * the furthest reached object and offset, fail.
	 */
	if (dbcra->dbcra_numsnaps > (dmu_bonus_max() -
	    sizeof (redaction_list_phys_t)) / sizeof (uint64_t))
		return (SET_ERROR(E2BIG));

	rv = dsl_dataset_hold(dp, dbcra->dbcra_snap,
	    FTAG, &snapds);
	if (rv == 0) {
		rv = dsl_bookmark_create_check_impl(snapds, dbcra->dbcra_bmark,
		    tx);
		dsl_dataset_rele(snapds, FTAG);
	}
	return (rv);
}