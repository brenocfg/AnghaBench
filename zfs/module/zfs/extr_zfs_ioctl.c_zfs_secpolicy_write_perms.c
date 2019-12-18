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
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 scalar_t__ INGLOBALZONE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curproc ; 
 int dsl_dataset_hold (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsl_pool_hold (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_pool_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ secpolicy_zfs (int /*<<< orphan*/ *) ; 
 int zfs_secpolicy_write_perms_ds (char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_secpolicy_write_perms(const char *name, const char *perm, cred_t *cr)
{
	int error;
	dsl_dataset_t *ds;
	dsl_pool_t *dp;

	/*
	 * First do a quick check for root in the global zone, which
	 * is allowed to do all write_perms.  This ensures that zfs_ioc_*
	 * will get to handle nonexistent datasets.
	 */
	if (INGLOBALZONE(curproc) && secpolicy_zfs(cr) == 0)
		return (0);

	error = dsl_pool_hold(name, FTAG, &dp);
	if (error != 0)
		return (error);

	error = dsl_dataset_hold(dp, name, FTAG, &ds);
	if (error != 0) {
		dsl_pool_rele(dp, FTAG);
		return (error);
	}

	error = zfs_secpolicy_write_perms_ds(name, ds, perm, cr);

	dsl_dataset_rele(ds, FTAG);
	dsl_pool_rele(dp, FTAG);
	return (error);
}