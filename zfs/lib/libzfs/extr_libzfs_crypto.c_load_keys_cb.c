#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  cb_numfailed; int /*<<< orphan*/  cb_numattempted; } ;
typedef  TYPE_1__ loadkey_cbdata_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ ZFS_KEYSTATUS_AVAILABLE ; 
 int /*<<< orphan*/  ZFS_PROP_KEYSTATUS ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int zfs_crypto_get_encryption_root (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfs_crypto_load_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_iter_filesystems (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *,void*),TYPE_1__*) ; 
 scalar_t__ zfs_prop_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
load_keys_cb(zfs_handle_t *zhp, void *arg)
{
	int ret;
	boolean_t is_encroot;
	loadkey_cbdata_t *cb = arg;
	uint64_t keystatus = zfs_prop_get_int(zhp, ZFS_PROP_KEYSTATUS);

	/* only attempt to load keys for encryption roots */
	ret = zfs_crypto_get_encryption_root(zhp, &is_encroot, NULL);
	if (ret != 0 || !is_encroot)
		goto out;

	/* don't attempt to load already loaded keys */
	if (keystatus == ZFS_KEYSTATUS_AVAILABLE)
		goto out;

	/* Attempt to load the key. Record status in cb. */
	cb->cb_numattempted++;

	ret = zfs_crypto_load_key(zhp, B_FALSE, NULL);
	if (ret)
		cb->cb_numfailed++;

out:
	(void) zfs_iter_filesystems(zhp, load_keys_cb, cb);
	zfs_close(zhp);

	/* always return 0, since this function is best effort */
	return (0);
}