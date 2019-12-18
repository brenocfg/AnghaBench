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
typedef  int /*<<< orphan*/  zio_bad_cksum_t ;
typedef  int /*<<< orphan*/  zfs_ecksum_info_t ;
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
typedef  int /*<<< orphan*/  vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct zio {int dummy; } ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FM_EREPORT_ZFS_CHECKSUM ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * annotate_ecksum (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfs_ereport_start (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,struct zio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_is_ratelimiting_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zfs_zevent_post (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_zevent_post_cb ; 

int
zfs_ereport_post_checksum(spa_t *spa, vdev_t *vd, const zbookmark_phys_t *zb,
    struct zio *zio, uint64_t offset, uint64_t length,
    const abd_t *good_data, const abd_t *bad_data, zio_bad_cksum_t *zbc)
{
	int rc = 0;
#ifdef _KERNEL
	nvlist_t *ereport = NULL;
	nvlist_t *detector = NULL;
	zfs_ecksum_info_t *info;

	if (zfs_is_ratelimiting_event(FM_EREPORT_ZFS_CHECKSUM, vd))
		return (EBUSY);

	if (!zfs_ereport_start(&ereport, &detector, FM_EREPORT_ZFS_CHECKSUM,
	    spa, vd, zb, zio, offset, length) || (ereport == NULL)) {
		return (SET_ERROR(EINVAL));
	}

	info = annotate_ecksum(ereport, zbc, good_data, bad_data, length,
	    B_FALSE);

	if (info != NULL) {
		rc = zfs_zevent_post(ereport, detector, zfs_zevent_post_cb);
		kmem_free(info, sizeof (*info));
	}
#endif
	return (rc);
}