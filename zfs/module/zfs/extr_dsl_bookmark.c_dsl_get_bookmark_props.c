#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ zfs_bookmark_phys_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  dsl_bookmark_fetch_props (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dsl_bookmark_lookup_impl (int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 
 int dsl_dataset_hold (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsl_pool_hold (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_pool_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
dsl_get_bookmark_props(const char *dsname, const char *bmname, nvlist_t *props)
{
	dsl_pool_t *dp;
	dsl_dataset_t *ds;
	zfs_bookmark_phys_t bmark_phys = { 0 };
	int err;

	err = dsl_pool_hold(dsname, FTAG, &dp);
	if (err != 0)
		return (err);
	err = dsl_dataset_hold(dp, dsname, FTAG, &ds);
	if (err != 0) {
		dsl_pool_rele(dp, FTAG);
		return (err);
	}

	err = dsl_bookmark_lookup_impl(ds, bmname, &bmark_phys);
	if (err != 0)
		goto out;

	dsl_bookmark_fetch_props(dp, &bmark_phys, NULL, props);
out:
	dsl_dataset_rele(ds, FTAG);
	dsl_pool_rele(dp, FTAG);
	return (err);
}