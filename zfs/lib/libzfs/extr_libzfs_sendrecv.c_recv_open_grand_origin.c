#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zprop_source_t ;
struct TYPE_9__ {int /*<<< orphan*/  zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  int /*<<< orphan*/  origin ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_PROP_ORIGIN ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  zfs_close (TYPE_1__*) ; 
 TYPE_1__* zfs_handle_dup (TYPE_1__*) ; 
 TYPE_1__* zfs_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get (TYPE_1__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zfs_handle_t *
recv_open_grand_origin(zfs_handle_t *zhp)
{
	char origin[ZFS_MAX_DATASET_NAME_LEN];
	zprop_source_t src;
	zfs_handle_t *ozhp = zfs_handle_dup(zhp);

	while (ozhp != NULL) {
		if (zfs_prop_get(ozhp, ZFS_PROP_ORIGIN, origin,
		    sizeof (origin), &src, NULL, 0, B_FALSE) != 0)
			break;

		(void) zfs_close(ozhp);
		ozhp = zfs_open(zhp->zfs_hdl, origin, ZFS_TYPE_FILESYSTEM);
	}

	return (ozhp);
}