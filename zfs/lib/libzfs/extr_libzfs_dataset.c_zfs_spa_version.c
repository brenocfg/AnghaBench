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
typedef  int /*<<< orphan*/  zpool_handle_t ;
struct TYPE_3__ {int /*<<< orphan*/ * zpool_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZPOOL_PROP_VERSION ; 
 int zpool_get_prop_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
zfs_spa_version(zfs_handle_t *zhp, int *spa_version)
{
	zpool_handle_t *zpool_handle = zhp->zpool_hdl;

	if (zpool_handle == NULL)
		return (-1);

	*spa_version = zpool_get_prop_int(zpool_handle,
	    ZPOOL_PROP_VERSION, NULL);
	return (0);
}