#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zpool_status_t ;
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  int /*<<< orphan*/  zpool_errata_t ;
struct TYPE_2__ {int /*<<< orphan*/  vs_aux; int /*<<< orphan*/  vs_state; } ;
typedef  TYPE_1__ vdev_stat_t ;
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 scalar_t__ POOL_STATE_UNAVAIL ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_STATS ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 scalar_t__ ZPOOL_STATUS_IO_FAILURE_MMP ; 
 scalar_t__ ZPOOL_STATUS_IO_FAILURE_WAIT ; 
 char* gettext (char*) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_uint64_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/  zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_get_state (int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_get_status (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* zpool_state_to_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *
zpool_get_state_str(zpool_handle_t *zhp)
{
	zpool_errata_t errata;
	zpool_status_t status;
	nvlist_t *nvroot;
	vdev_stat_t *vs;
	uint_t vsc;
	const char *str;

	status = zpool_get_status(zhp, NULL, &errata);

	if (zpool_get_state(zhp) == POOL_STATE_UNAVAIL) {
		str = gettext("FAULTED");
	} else if (status == ZPOOL_STATUS_IO_FAILURE_WAIT ||
	    status == ZPOOL_STATUS_IO_FAILURE_MMP) {
		str = gettext("SUSPENDED");
	} else {
		verify(nvlist_lookup_nvlist(zpool_get_config(zhp, NULL),
		    ZPOOL_CONFIG_VDEV_TREE, &nvroot) == 0);
		verify(nvlist_lookup_uint64_array(nvroot,
		    ZPOOL_CONFIG_VDEV_STATS, (uint64_t **)&vs, &vsc)
		    == 0);
		str = zpool_state_to_name(vs->vs_state, vs->vs_aux);
	}
	return (str);
}