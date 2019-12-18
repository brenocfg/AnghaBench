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
typedef  int uint_t ;
typedef  int uint64_t ;
struct zed_conf {int /*<<< orphan*/  zevent_fd; int /*<<< orphan*/  zfs_hdl; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  ZEVENT_NONBLOCK ; 
 int /*<<< orphan*/  ZEVENT_SEEK_START ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_int64_array (int /*<<< orphan*/ *,char*,scalar_t__**,int*) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,char*,int*) ; 
 int strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,...) ; 
 int zpool_events_next (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zpool_events_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
zed_event_seek(struct zed_conf *zcp, uint64_t saved_eid, int64_t saved_etime[])
{
	uint64_t eid;
	int found;
	nvlist_t *nvl;
	int n_dropped;
	int64_t *etime;
	uint_t nelem;
	int rv;

	if (!zcp) {
		errno = EINVAL;
		zed_log_msg(LOG_ERR, "Failed to seek zevent: %s",
		    strerror(errno));
		return (-1);
	}
	eid = 0;
	found = 0;
	while ((eid < saved_eid) && !found) {
		rv = zpool_events_next(zcp->zfs_hdl, &nvl, &n_dropped,
		    ZEVENT_NONBLOCK, zcp->zevent_fd);

		if ((rv != 0) || !nvl)
			break;

		if (n_dropped > 0) {
			zed_log_msg(LOG_WARNING, "Missed %d events", n_dropped);
			/*
			 * FIXME: Increase max size of event nvlist in
			 *   /sys/module/zfs/parameters/zfs_zevent_len_max ?
			 */
		}
		if (nvlist_lookup_uint64(nvl, "eid", &eid) != 0) {
			zed_log_msg(LOG_WARNING, "Failed to lookup zevent eid");
		} else if (nvlist_lookup_int64_array(nvl, "time",
		    &etime, &nelem) != 0) {
			zed_log_msg(LOG_WARNING,
			    "Failed to lookup zevent time (eid=%llu)", eid);
		} else if (nelem != 2) {
			zed_log_msg(LOG_WARNING,
			    "Failed to lookup zevent time (eid=%llu, nelem=%u)",
			    eid, nelem);
		} else if ((eid != saved_eid) ||
		    (etime[0] != saved_etime[0]) ||
		    (etime[1] != saved_etime[1])) {
			/* no-op */
		} else {
			found = 1;
		}
		free(nvl);
	}
	if (!found && (saved_eid > 0)) {
		if (zpool_events_seek(zcp->zfs_hdl, ZEVENT_SEEK_START,
		    zcp->zevent_fd) < 0)
			zed_log_msg(LOG_WARNING, "Failed to seek to eid=0");
		else
			eid = 0;
	}
	zed_log_msg(LOG_NOTICE, "Processing events since eid=%llu", eid);
	return (found ? 0 : -1);
}