#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zfs_prop_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  scalar_t__ enforce_res_t ;
struct TYPE_8__ {struct TYPE_8__* dd_parent; int /*<<< orphan*/  dd_object; TYPE_3__* dd_pool; } ;
typedef  TYPE_1__ dsl_dir_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int /*<<< orphan*/  count ;
struct TYPE_9__ {int /*<<< orphan*/ * dp_meta_objset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 char* DD_FIELD_FILESYSTEM_COUNT ; 
 char* DD_FIELD_SNAPSHOT_COUNT ; 
 int /*<<< orphan*/  EDQUOT ; 
 scalar_t__ ENFORCE_ALWAYS ; 
 scalar_t__ ENFORCE_NEVER ; 
 scalar_t__ ENOENT ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ZFS_PROP_FILESYSTEM_LIMIT ; 
 scalar_t__ ZFS_PROP_SNAPSHOT_LIMIT ; 
 int /*<<< orphan*/  dsl_dir_is_zapified (TYPE_1__*) ; 
 scalar_t__ dsl_enforce_ds_ss_limits (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int dsl_pool_config_held (TYPE_3__*) ; 
 int dsl_prop_get_dd (TYPE_1__*,int /*<<< orphan*/ ,int,int,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  zfs_prop_to_name (scalar_t__) ; 

int
dsl_fs_ss_limit_check(dsl_dir_t *dd, uint64_t delta, zfs_prop_t prop,
    dsl_dir_t *ancestor, cred_t *cr)
{
	objset_t *os = dd->dd_pool->dp_meta_objset;
	uint64_t limit, count;
	char *count_prop;
	enforce_res_t enforce;
	int err = 0;

	ASSERT(dsl_pool_config_held(dd->dd_pool));
	ASSERT(prop == ZFS_PROP_FILESYSTEM_LIMIT ||
	    prop == ZFS_PROP_SNAPSHOT_LIMIT);

	/*
	 * If we're allowed to change the limit, don't enforce the limit
	 * e.g. this can happen if a snapshot is taken by an administrative
	 * user in the global zone (i.e. a recursive snapshot by root).
	 * However, we must handle the case of delegated permissions where we
	 * are allowed to change the limit on the current dataset, but there
	 * is another limit in the tree above.
	 */
	enforce = dsl_enforce_ds_ss_limits(dd, prop, cr);
	if (enforce == ENFORCE_NEVER)
		return (0);

	/*
	 * e.g. if renaming a dataset with no snapshots, count adjustment
	 * is 0.
	 */
	if (delta == 0)
		return (0);

	if (prop == ZFS_PROP_SNAPSHOT_LIMIT) {
		/*
		 * We don't enforce the limit for temporary snapshots. This is
		 * indicated by a NULL cred_t argument.
		 */
		if (cr == NULL)
			return (0);

		count_prop = DD_FIELD_SNAPSHOT_COUNT;
	} else {
		count_prop = DD_FIELD_FILESYSTEM_COUNT;
	}

	/*
	 * If an ancestor has been provided, stop checking the limit once we
	 * hit that dir. We need this during rename so that we don't overcount
	 * the check once we recurse up to the common ancestor.
	 */
	if (ancestor == dd)
		return (0);

	/*
	 * If we hit an uninitialized node while recursing up the tree, we can
	 * stop since we know there is no limit here (or above). The counts are
	 * not valid on this node and we know we won't touch this node's counts.
	 */
	if (!dsl_dir_is_zapified(dd) || zap_lookup(os, dd->dd_object,
	    count_prop, sizeof (count), 1, &count) == ENOENT)
		return (0);

	err = dsl_prop_get_dd(dd, zfs_prop_to_name(prop), 8, 1, &limit, NULL,
	    B_FALSE);
	if (err != 0)
		return (err);

	/* Is there a limit which we've hit? */
	if (enforce == ENFORCE_ALWAYS && (count + delta) > limit)
		return (SET_ERROR(EDQUOT));

	if (dd->dd_parent != NULL)
		err = dsl_fs_ss_limit_check(dd->dd_parent, delta, prop,
		    ancestor, cr);

	return (err);
}