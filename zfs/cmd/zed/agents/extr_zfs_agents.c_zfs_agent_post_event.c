#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_7__ {char const* gs_devid; int gs_vdev_type; scalar_t__ gs_vdev_expandtime; int /*<<< orphan*/  gs_vdev_guid; int /*<<< orphan*/  gs_pool_guid; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ guid_search_t ;
typedef  int device_type_t ;
struct TYPE_8__ {int /*<<< orphan*/  ae_subclass; int /*<<< orphan*/  ae_class; int /*<<< orphan*/ * ae_nvl; } ;
typedef  TYPE_2__ agent_event_t ;

/* Variables and functions */
#define  DEVICE_TYPE_L2ARC 130 
#define  DEVICE_TYPE_PRIMARY 129 
#define  DEVICE_TYPE_SPARE 128 
 int /*<<< orphan*/  DEV_IDENTIFIER ; 
 char* EC_DEV_REMOVE ; 
 char* EC_ZFS ; 
 char* ESC_DISK ; 
 char* ESC_ZFS_VDEV_CHECK ; 
 int /*<<< orphan*/  FM_CLASS ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_POOL_GUID ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_GUID ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_TYPE ; 
 int /*<<< orphan*/  FM_EREPORT_TIME ; 
 int /*<<< orphan*/  LOG_INFO ; 
 char const* VDEV_TYPE_DISK ; 
 char const* VDEV_TYPE_L2CACHE ; 
 char const* VDEV_TYPE_SPARE ; 
 int /*<<< orphan*/  ZFS_EV_POOL_GUID ; 
 int /*<<< orphan*/  ZFS_EV_VDEV_GUID ; 
 int /*<<< orphan*/  agent_cond ; 
 int /*<<< orphan*/  agent_events ; 
 int /*<<< orphan*/  agent_lock ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  g_zfs_hdl ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_insert_tail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  nvlist_add_int64_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  zfs_agent_iter_pool ; 
 int /*<<< orphan*/  zpool_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

void
zfs_agent_post_event(const char *class, const char *subclass, nvlist_t *nvl)
{
	agent_event_t *event;

	if (subclass == NULL)
		subclass = "";

	event = malloc(sizeof (agent_event_t));
	if (event == NULL || nvlist_dup(nvl, &event->ae_nvl, 0) != 0) {
		if (event)
			free(event);
		return;
	}

	if (strcmp(class, "sysevent.fs.zfs.vdev_check") == 0) {
		class = EC_ZFS;
		subclass = ESC_ZFS_VDEV_CHECK;
	}

	/*
	 * On ZFS on Linux, we don't get the expected FM_RESOURCE_REMOVED
	 * ereport from vdev_disk layer after a hot unplug. Fortunately we
	 * get a EC_DEV_REMOVE from our disk monitor and it is a suitable
	 * proxy so we remap it here for the benefit of the diagnosis engine.
	 */
	if ((strcmp(class, EC_DEV_REMOVE) == 0) &&
	    (strcmp(subclass, ESC_DISK) == 0) &&
	    (nvlist_exists(nvl, ZFS_EV_VDEV_GUID) ||
	    nvlist_exists(nvl, DEV_IDENTIFIER))) {
		nvlist_t *payload = event->ae_nvl;
		struct timeval tv;
		int64_t tod[2];
		uint64_t pool_guid = 0, vdev_guid = 0;
		guid_search_t search = { 0 };
		device_type_t devtype = DEVICE_TYPE_PRIMARY;

		class = "resource.fs.zfs.removed";
		subclass = "";

		(void) nvlist_add_string(payload, FM_CLASS, class);
		(void) nvlist_lookup_uint64(nvl, ZFS_EV_POOL_GUID, &pool_guid);
		(void) nvlist_lookup_uint64(nvl, ZFS_EV_VDEV_GUID, &vdev_guid);

		(void) gettimeofday(&tv, NULL);
		tod[0] = tv.tv_sec;
		tod[1] = tv.tv_usec;
		(void) nvlist_add_int64_array(payload, FM_EREPORT_TIME, tod, 2);

		/*
		 * For multipath, spare and l2arc devices ZFS_EV_VDEV_GUID or
		 * ZFS_EV_POOL_GUID may be missing so find them.
		 */
		(void) nvlist_lookup_string(nvl, DEV_IDENTIFIER,
		    &search.gs_devid);
		(void) zpool_iter(g_zfs_hdl, zfs_agent_iter_pool, &search);
		pool_guid = search.gs_pool_guid;
		vdev_guid = search.gs_vdev_guid;
		devtype = search.gs_vdev_type;

		/*
		 * We want to avoid reporting "remove" events coming from
		 * libudev for VDEVs which were expanded recently (10s) and
		 * avoid activating spares in response to partitions being
		 * deleted and created in rapid succession.
		 */
		if (search.gs_vdev_expandtime != 0 &&
		    search.gs_vdev_expandtime + 10 > tv.tv_sec) {
			zed_log_msg(LOG_INFO, "agent post event: ignoring '%s' "
			    "for recently expanded device '%s'", EC_DEV_REMOVE,
			    search.gs_devid);
			goto out;
		}

		(void) nvlist_add_uint64(payload,
		    FM_EREPORT_PAYLOAD_ZFS_POOL_GUID, pool_guid);
		(void) nvlist_add_uint64(payload,
		    FM_EREPORT_PAYLOAD_ZFS_VDEV_GUID, vdev_guid);
		switch (devtype) {
		case DEVICE_TYPE_L2ARC:
			(void) nvlist_add_string(payload,
			    FM_EREPORT_PAYLOAD_ZFS_VDEV_TYPE,
			    VDEV_TYPE_L2CACHE);
			break;
		case DEVICE_TYPE_SPARE:
			(void) nvlist_add_string(payload,
			    FM_EREPORT_PAYLOAD_ZFS_VDEV_TYPE, VDEV_TYPE_SPARE);
			break;
		case DEVICE_TYPE_PRIMARY:
			(void) nvlist_add_string(payload,
			    FM_EREPORT_PAYLOAD_ZFS_VDEV_TYPE, VDEV_TYPE_DISK);
			break;
		}

		zed_log_msg(LOG_INFO, "agent post event: mapping '%s' to '%s'",
		    EC_DEV_REMOVE, class);
	}

	(void) strlcpy(event->ae_class, class, sizeof (event->ae_class));
	(void) strlcpy(event->ae_subclass, subclass,
	    sizeof (event->ae_subclass));

	(void) pthread_mutex_lock(&agent_lock);
	list_insert_tail(&agent_events, event);
	(void) pthread_mutex_unlock(&agent_lock);

out:
	(void) pthread_cond_signal(&agent_cond);
}