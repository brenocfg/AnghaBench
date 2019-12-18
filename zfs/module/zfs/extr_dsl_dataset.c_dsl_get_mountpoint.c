#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_2__ dsl_pool_t ;
struct TYPE_8__ {TYPE_1__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
struct TYPE_6__ {TYPE_2__* dd_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  ZAP_MAXVALUELEN ; 
 int /*<<< orphan*/  ZFS_PROP_MOUNTPOINT ; 
 char* ZPROP_SOURCE_VAL_RECVD ; 
 int dsl_prop_get_ds (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,char*) ; 
 char* kmem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,char*,...) ; 
 int /*<<< orphan*/  spa_altroot (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 

int
dsl_get_mountpoint(dsl_dataset_t *ds, const char *dsname, char *value,
    char *source)
{
	int error;
	dsl_pool_t *dp = ds->ds_dir->dd_pool;

	/* Retrieve the mountpoint value stored in the zap object */
	error = dsl_prop_get_ds(ds, zfs_prop_to_name(ZFS_PROP_MOUNTPOINT), 1,
	    ZAP_MAXVALUELEN, value, source);
	if (error != 0) {
		return (error);
	}

	/*
	 * Process the dsname and source to find the full mountpoint string.
	 * Can be skipped for 'legacy' or 'none'.
	 */
	if (value[0] == '/') {
		char *buf = kmem_alloc(ZAP_MAXVALUELEN, KM_SLEEP);
		char *root = buf;
		const char *relpath;

		/*
		 * If we inherit the mountpoint, even from a dataset
		 * with a received value, the source will be the path of
		 * the dataset we inherit from. If source is
		 * ZPROP_SOURCE_VAL_RECVD, the received value is not
		 * inherited.
		 */
		if (strcmp(source, ZPROP_SOURCE_VAL_RECVD) == 0) {
			relpath = "";
		} else {
			ASSERT0(strncmp(dsname, source, strlen(source)));
			relpath = dsname + strlen(source);
			if (relpath[0] == '/')
				relpath++;
		}

		spa_altroot(dp->dp_spa, root, ZAP_MAXVALUELEN);

		/*
		 * Special case an alternate root of '/'. This will
		 * avoid having multiple leading slashes in the
		 * mountpoint path.
		 */
		if (strcmp(root, "/") == 0)
			root++;

		/*
		 * If the mountpoint is '/' then skip over this
		 * if we are obtaining either an alternate root or
		 * an inherited mountpoint.
		 */
		char *mnt = value;
		if (value[1] == '\0' && (root[0] != '\0' ||
		    relpath[0] != '\0'))
			mnt = value + 1;

		if (relpath[0] == '\0') {
			(void) snprintf(value, ZAP_MAXVALUELEN, "%s%s",
			    root, mnt);
		} else {
			(void) snprintf(value, ZAP_MAXVALUELEN, "%s%s%s%s",
			    root, mnt, relpath[0] == '@' ? "" : "/",
			    relpath);
		}
		kmem_free(buf, ZAP_MAXVALUELEN);
	}

	return (0);
}