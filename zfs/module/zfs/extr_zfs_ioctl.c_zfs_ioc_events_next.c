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
typedef  int /*<<< orphan*/  zfs_zevent_t ;
struct TYPE_4__ {int zc_guid; int /*<<< orphan*/  zc_cleanup_fd; int /*<<< orphan*/  zc_cookie; int /*<<< orphan*/  zc_nvlist_dst_size; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  minor_t ;

/* Variables and functions */
 int ENOENT ; 
 int ZEVENT_NONBLOCK ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int put_nvlist (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int zfs_zevent_fd_hold (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zfs_zevent_fd_rele (int /*<<< orphan*/ ) ; 
 int zfs_zevent_next (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfs_zevent_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_ioc_events_next(zfs_cmd_t *zc)
{
	zfs_zevent_t *ze;
	nvlist_t *event = NULL;
	minor_t minor;
	uint64_t dropped = 0;
	int error;

	error = zfs_zevent_fd_hold(zc->zc_cleanup_fd, &minor, &ze);
	if (error != 0)
		return (error);

	do {
		error = zfs_zevent_next(ze, &event,
		    &zc->zc_nvlist_dst_size, &dropped);
		if (event != NULL) {
			zc->zc_cookie = dropped;
			error = put_nvlist(zc, event);
			nvlist_free(event);
		}

		if (zc->zc_guid & ZEVENT_NONBLOCK)
			break;

		if ((error == 0) || (error != ENOENT))
			break;

		error = zfs_zevent_wait(ze);
		if (error != 0)
			break;
	} while (1);

	zfs_zevent_fd_rele(zc->zc_cleanup_fd);

	return (error);
}