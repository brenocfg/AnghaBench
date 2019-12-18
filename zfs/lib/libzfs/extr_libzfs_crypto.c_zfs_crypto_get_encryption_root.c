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
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  prop_encroot ;
typedef  int boolean_t ;

/* Variables and functions */
 int B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int MAXNAMELEN ; 
 int /*<<< orphan*/  ZFS_PROP_ENCRYPTION ; 
 int /*<<< orphan*/  ZFS_PROP_ENCRYPTION_ROOT ; 
 scalar_t__ ZIO_CRYPT_OFF ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  zfs_get_name (int /*<<< orphan*/ *) ; 
 int zfs_prop_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
zfs_crypto_get_encryption_root(zfs_handle_t *zhp, boolean_t *is_encroot,
    char *buf)
{
	int ret;
	char prop_encroot[MAXNAMELEN];

	/* if the dataset isn't encrypted, just return */
	if (zfs_prop_get_int(zhp, ZFS_PROP_ENCRYPTION) == ZIO_CRYPT_OFF) {
		*is_encroot = B_FALSE;
		if (buf != NULL)
			buf[0] = '\0';
		return (0);
	}

	ret = zfs_prop_get(zhp, ZFS_PROP_ENCRYPTION_ROOT, prop_encroot,
	    sizeof (prop_encroot), NULL, NULL, 0, B_TRUE);
	if (ret != 0) {
		*is_encroot = B_FALSE;
		if (buf != NULL)
			buf[0] = '\0';
		return (ret);
	}

	*is_encroot = strcmp(prop_encroot, zfs_get_name(zhp)) == 0;
	if (buf != NULL)
		strcpy(buf, prop_encroot);

	return (0);
}