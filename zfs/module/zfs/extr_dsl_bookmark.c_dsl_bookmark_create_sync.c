#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvpair_t ;
struct TYPE_3__ {int /*<<< orphan*/  dbca_bmarks; } ;
typedef  TYPE_1__ dsl_bookmark_create_arg_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_4__ {int /*<<< orphan*/  dp_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_FEATURE_BOOKMARKS ; 
 TYPE_2__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_bookmark_create_sync_impl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvpair_value_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_is_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dsl_bookmark_create_sync(void *arg, dmu_tx_t *tx)
{
	dsl_bookmark_create_arg_t *dbca = arg;

	ASSERT(spa_feature_is_enabled(dmu_tx_pool(tx)->dp_spa,
	    SPA_FEATURE_BOOKMARKS));

	for (nvpair_t *pair = nvlist_next_nvpair(dbca->dbca_bmarks, NULL);
	    pair != NULL; pair = nvlist_next_nvpair(dbca->dbca_bmarks, pair)) {
		dsl_bookmark_create_sync_impl(nvpair_name(pair),
		    fnvpair_value_string(pair), tx, 0, NULL, NULL, NULL);
	}
}