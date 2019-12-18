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
typedef  int /*<<< orphan*/  zio_t ;
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
typedef  int /*<<< orphan*/  vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_ereport_start (int /*<<< orphan*/ **,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_is_ratelimiting_event (char const*,int /*<<< orphan*/ *) ; 
 int zfs_zevent_post (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_zevent_post_cb ; 

int
zfs_ereport_post(const char *subclass, spa_t *spa, vdev_t *vd,
    const zbookmark_phys_t *zb, zio_t *zio, uint64_t stateoroffset,
    uint64_t size)
{
	int rc = 0;
#ifdef _KERNEL
	nvlist_t *ereport = NULL;
	nvlist_t *detector = NULL;

	if (zfs_is_ratelimiting_event(subclass, vd))
		return (SET_ERROR(EBUSY));

	if (!zfs_ereport_start(&ereport, &detector, subclass, spa, vd,
	    zb, zio, stateoroffset, size))
		return (SET_ERROR(EINVAL));	/* couldn't post event */

	if (ereport == NULL)
		return (SET_ERROR(EINVAL));

	/* Cleanup is handled by the callback function */
	rc = zfs_zevent_post(ereport, detector, zfs_zevent_post_cb);
#endif
	return (rc);
}