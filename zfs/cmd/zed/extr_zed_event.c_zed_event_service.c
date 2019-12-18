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
typedef  int /*<<< orphan*/  zed_strings_t ;
typedef  int uint_t ;
typedef  int uint64_t ;
struct zed_conf {char const* zedlet_dir; int /*<<< orphan*/  zevent_fd; int /*<<< orphan*/  zedlets; int /*<<< orphan*/  path; int /*<<< orphan*/  zfs_hdl; } ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  ZED_VAR_PREFIX ; 
 int /*<<< orphan*/  ZEVENT_NONE ; 
 int /*<<< orphan*/  ZEVENT_VAR_PREFIX ; 
 int /*<<< orphan*/  _zed_event_add_env_preserve (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zed_event_add_env_restrict (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _zed_event_add_nvpair (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zed_event_add_time_strings (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zed_event_add_var (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,...) ; 
 char* _zed_event_get_subclass (char*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_int64_array (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zed_conf_write_state (struct zed_conf*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zed_exec_process (int,char*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * zed_strings_create () ; 
 int /*<<< orphan*/  zed_strings_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_agent_post_event (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zpool_events_next (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
zed_event_service(struct zed_conf *zcp)
{
	nvlist_t *nvl;
	nvpair_t *nvp;
	int n_dropped;
	zed_strings_t *zsp;
	uint64_t eid;
	int64_t *etime;
	uint_t nelem;
	char *class;
	const char *subclass;
	int rv;

	if (!zcp) {
		errno = EINVAL;
		zed_log_msg(LOG_ERR, "Failed to service zevent: %s",
		    strerror(errno));
		return;
	}
	rv = zpool_events_next(zcp->zfs_hdl, &nvl, &n_dropped, ZEVENT_NONE,
	    zcp->zevent_fd);

	if ((rv != 0) || !nvl)
		return;

	if (n_dropped > 0) {
		zed_log_msg(LOG_WARNING, "Missed %d events", n_dropped);
		/*
		 * FIXME: Increase max size of event nvlist in
		 * /sys/module/zfs/parameters/zfs_zevent_len_max ?
		 */
	}
	if (nvlist_lookup_uint64(nvl, "eid", &eid) != 0) {
		zed_log_msg(LOG_WARNING, "Failed to lookup zevent eid");
	} else if (nvlist_lookup_int64_array(
	    nvl, "time", &etime, &nelem) != 0) {
		zed_log_msg(LOG_WARNING,
		    "Failed to lookup zevent time (eid=%llu)", eid);
	} else if (nelem != 2) {
		zed_log_msg(LOG_WARNING,
		    "Failed to lookup zevent time (eid=%llu, nelem=%u)",
		    eid, nelem);
	} else if (nvlist_lookup_string(nvl, "class", &class) != 0) {
		zed_log_msg(LOG_WARNING,
		    "Failed to lookup zevent class (eid=%llu)", eid);
	} else {
		/* let internal modules see this event first */
		zfs_agent_post_event(class, NULL, nvl);

		zsp = zed_strings_create();

		nvp = NULL;
		while ((nvp = nvlist_next_nvpair(nvl, nvp)))
			_zed_event_add_nvpair(eid, zsp, nvp);

		_zed_event_add_env_restrict(eid, zsp, zcp->path);
		_zed_event_add_env_preserve(eid, zsp);

		_zed_event_add_var(eid, zsp, ZED_VAR_PREFIX, "PID",
		    "%d", (int)getpid());
		_zed_event_add_var(eid, zsp, ZED_VAR_PREFIX, "ZEDLET_DIR",
		    "%s", zcp->zedlet_dir);
		subclass = _zed_event_get_subclass(class);
		_zed_event_add_var(eid, zsp, ZEVENT_VAR_PREFIX, "SUBCLASS",
		    "%s", (subclass ? subclass : class));

		_zed_event_add_time_strings(eid, zsp, etime);

		zed_exec_process(eid, class, subclass,
		    zcp->zedlet_dir, zcp->zedlets, zsp, zcp->zevent_fd);

		zed_conf_write_state(zcp, eid, etime);

		zed_strings_destroy(zsp);
	}
	nvlist_free(nvl);
}