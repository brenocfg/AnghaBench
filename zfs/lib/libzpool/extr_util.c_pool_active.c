#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t zc_nvlist_src_size; scalar_t__ zc_nvlist_dst; scalar_t__ zc_nvlist_src; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 int /*<<< orphan*/  ZFS_DEV ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_SYNC ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fnvlist_add_boolean_value (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 char* fnvlist_pack (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  fnvlist_pack_free (char*,size_t) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  umem_free (TYPE_1__*,int) ; 
 TYPE_1__* umem_zalloc (int,int /*<<< orphan*/ ) ; 
 int zfs_ioctl_fd (int,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
pool_active(void *unused, const char *name, uint64_t guid,
    boolean_t *isactive)
{
	zfs_cmd_t *zcp;
	nvlist_t *innvl;
	char *packed = NULL;
	size_t size = 0;
	int fd, ret;

	/*
	 * Use ZFS_IOC_POOL_SYNC to confirm if a pool is active
	 */

	fd = open(ZFS_DEV, O_RDWR);
	if (fd < 0)
		return (-1);

	zcp = umem_zalloc(sizeof (zfs_cmd_t), UMEM_NOFAIL);

	innvl = fnvlist_alloc();
	fnvlist_add_boolean_value(innvl, "force", B_FALSE);

	(void) strlcpy(zcp->zc_name, name, sizeof (zcp->zc_name));
	packed = fnvlist_pack(innvl, &size);
	zcp->zc_nvlist_src = (uint64_t)(uintptr_t)packed;
	zcp->zc_nvlist_src_size = size;

	ret = zfs_ioctl_fd(fd, ZFS_IOC_POOL_SYNC, zcp);

	fnvlist_pack_free(packed, size);
	free((void *)(uintptr_t)zcp->zc_nvlist_dst);
	nvlist_free(innvl);
	umem_free(zcp, sizeof (zfs_cmd_t));

	(void) close(fd);

	*isactive = (ret == 0);

	return (0);
}