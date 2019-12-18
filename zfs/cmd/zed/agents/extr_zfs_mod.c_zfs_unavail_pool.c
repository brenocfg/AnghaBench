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
typedef  int /*<<< orphan*/  zpool_handle_t ;
struct TYPE_4__ {int /*<<< orphan*/ * uap_zhp; } ;
typedef  TYPE_1__ unavailpool_t ;
typedef  int /*<<< orphan*/  list_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 scalar_t__ VDEV_STATE_DEGRADED ; 
 int /*<<< orphan*/  list_insert_tail (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ zfs_toplevel_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_get_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_unavail_pool(zpool_handle_t *zhp, void *data)
{
	zed_log_msg(LOG_INFO, "zfs_unavail_pool: examining '%s' (state %d)",
	    zpool_get_name(zhp), (int)zfs_toplevel_state(zhp));

	if (zfs_toplevel_state(zhp) < VDEV_STATE_DEGRADED) {
		unavailpool_t *uap;
		uap = malloc(sizeof (unavailpool_t));
		uap->uap_zhp = zhp;
		list_insert_tail((list_t *)data, uap);
	} else {
		zpool_close(zhp);
	}
	return (0);
}