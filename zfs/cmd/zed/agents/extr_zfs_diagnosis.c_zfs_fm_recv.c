#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_41__   TYPE_9__ ;
typedef  struct TYPE_40__   TYPE_8__ ;
typedef  struct TYPE_39__   TYPE_7__ ;
typedef  struct TYPE_38__   TYPE_6__ ;
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_15__ ;
typedef  struct TYPE_31__   TYPE_14__ ;
typedef  struct TYPE_30__   TYPE_13__ ;
typedef  struct TYPE_29__   TYPE_12__ ;
typedef  struct TYPE_28__   TYPE_11__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
struct TYPE_39__ {scalar_t__ zc_pool_guid; scalar_t__ zc_vdev_guid; int zc_has_remove_timer; char* zc_serd_io; char* zc_serd_checksum; } ;
struct TYPE_31__ {int /*<<< orphan*/  ertv_nsec; int /*<<< orphan*/  ertv_sec; } ;
struct TYPE_29__ {TYPE_7__ zc_data; int /*<<< orphan*/  zc_remove_timer; int /*<<< orphan*/  zc_case; TYPE_14__ zc_when; } ;
typedef  TYPE_12__ zfs_case_t ;
struct TYPE_30__ {int zc_pool_state; scalar_t__ zc_vdev_guid; scalar_t__ zc_pool_guid; scalar_t__ zc_ena; int /*<<< orphan*/  zc_version; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_13__ zfs_case_data_t ;
typedef  scalar_t__ uint64_t ;
struct load_time_arg {scalar_t__ lt_found; TYPE_14__* lt_time; scalar_t__ lt_guid; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;
typedef  int /*<<< orphan*/  fmd_event_t ;
typedef  int /*<<< orphan*/  fmd_case_t ;
typedef  TYPE_14__ er_timeval_t ;
typedef  int /*<<< orphan*/  data ;
typedef  scalar_t__ boolean_t ;
struct TYPE_40__ {int /*<<< orphan*/  ui64; } ;
struct TYPE_41__ {TYPE_8__ fmds_value; } ;
struct TYPE_37__ {int /*<<< orphan*/  ui64; } ;
struct TYPE_38__ {TYPE_5__ fmds_value; } ;
struct TYPE_35__ {int /*<<< orphan*/  ui64; } ;
struct TYPE_36__ {TYPE_3__ fmds_value; } ;
struct TYPE_33__ {int /*<<< orphan*/  ui64; } ;
struct TYPE_34__ {TYPE_1__ fmds_value; } ;
struct TYPE_27__ {int /*<<< orphan*/  ui64; } ;
struct TYPE_28__ {TYPE_10__ fmds_value; } ;
struct TYPE_32__ {TYPE_9__ resource_drops; TYPE_6__ old_drops; TYPE_4__ vdev_drops; TYPE_2__ dev_drops; TYPE_11__ import_drops; } ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  CASE_DATA ; 
 int /*<<< orphan*/  CASE_DATA_VERSION_SERD ; 
 int /*<<< orphan*/  FM_EREPORT_DETECTOR ; 
 int /*<<< orphan*/  FM_EREPORT_ENA ; 
 int /*<<< orphan*/  FM_EREPORT_FAILMODE_CONTINUE ; 
 int /*<<< orphan*/  FM_EREPORT_FAILMODE_WAIT ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_POOL_CONTEXT ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_POOL_FAILMODE ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_POOL_GUID ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_GUID ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_STATE ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_TYPE ; 
 int /*<<< orphan*/  FM_EREPORT_ZFS_CHECKSUM ; 
 int /*<<< orphan*/  FM_EREPORT_ZFS_CONFIG_CACHE_WRITE ; 
 int /*<<< orphan*/  FM_EREPORT_ZFS_DATA ; 
 int /*<<< orphan*/  FM_EREPORT_ZFS_DELAY ; 
 int /*<<< orphan*/  FM_EREPORT_ZFS_IO ; 
 int /*<<< orphan*/  FM_EREPORT_ZFS_IO_FAILURE ; 
 int /*<<< orphan*/  FM_EREPORT_ZFS_LOG_REPLAY ; 
 int /*<<< orphan*/  FM_EREPORT_ZFS_POOL ; 
 int /*<<< orphan*/  FM_EREPORT_ZFS_PROBE_FAILURE ; 
 int /*<<< orphan*/  FM_RESOURCE_AUTOREPLACE ; 
 int /*<<< orphan*/  FM_RESOURCE_REMOVED ; 
 int /*<<< orphan*/  FM_RESOURCE_STATECHANGE ; 
 scalar_t__ SPA_LOAD_IMPORT ; 
 scalar_t__ SPA_LOAD_NONE ; 
 scalar_t__ SPA_LOAD_OPEN ; 
 scalar_t__ VDEV_STATE_HEALTHY ; 
 char* VDEV_TYPE_DISK ; 
 char* VDEV_TYPE_FILE ; 
 char* ZFS_MAKE_EREPORT (int /*<<< orphan*/ ) ; 
 char* ZFS_MAKE_RSRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmd_buf_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fmd_buf_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_13__*,int) ; 
 int /*<<< orphan*/  fmd_case_add_ereport (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmd_case_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fmd_case_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fmd_case_solved (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmd_hdl_debug (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * fmd_hdl_getspecific (int /*<<< orphan*/ *) ; 
 scalar_t__ fmd_nvl_class_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fmd_prop_get_int32 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fmd_prop_get_int64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fmd_serd_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fmd_serd_record (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmd_serd_reset (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fmd_timer_install (int /*<<< orphan*/ *,TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmd_timer_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_lookup_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char const* strrchr (char const*,char) ; 
 scalar_t__ timeval_earlier (TYPE_14__*,TYPE_14__*) ; 
 TYPE_12__* uu_list_first (int /*<<< orphan*/ ) ; 
 TYPE_12__* uu_list_next (int /*<<< orphan*/ ,TYPE_12__*) ; 
 int /*<<< orphan*/  zfs_case_serialize (int /*<<< orphan*/ *,TYPE_12__*) ; 
 int /*<<< orphan*/  zfs_case_solve (int /*<<< orphan*/ *,TYPE_12__*,char*,scalar_t__) ; 
 TYPE_12__* zfs_case_unserialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_cases ; 
 int /*<<< orphan*/  zfs_ereport_when (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_14__*) ; 
 int /*<<< orphan*/  zfs_purge_cases (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_remove_timeout ; 
 int /*<<< orphan*/  zfs_serd_name (char*,scalar_t__,scalar_t__,char*) ; 
 TYPE_15__ zfs_stats ; 
 int /*<<< orphan*/  zpool_find_load_time ; 
 scalar_t__ zpool_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct load_time_arg*) ; 

__attribute__((used)) static void
zfs_fm_recv(fmd_hdl_t *hdl, fmd_event_t *ep, nvlist_t *nvl, const char *class)
{
	zfs_case_t *zcp, *dcp;
	int32_t pool_state;
	uint64_t ena, pool_guid, vdev_guid;
	er_timeval_t pool_load;
	er_timeval_t er_when;
	nvlist_t *detector;
	boolean_t pool_found = B_FALSE;
	boolean_t isresource;
	char *type;

	/*
	 * We subscribe to notifications for vdev or pool removal.  In these
	 * cases, there may be cases that no longer apply.  Purge any cases
	 * that no longer apply.
	 */
	if (fmd_nvl_class_match(hdl, nvl, "sysevent.fs.zfs.*")) {
		fmd_hdl_debug(hdl, "purging orphaned cases from %s",
		    strrchr(class, '.') + 1);
		zfs_purge_cases(hdl);
		zfs_stats.resource_drops.fmds_value.ui64++;
		return;
	}

	isresource = fmd_nvl_class_match(hdl, nvl, "resource.fs.zfs.*");

	if (isresource) {
		/*
		 * For resources, we don't have a normal payload.
		 */
		if (nvlist_lookup_uint64(nvl, FM_EREPORT_PAYLOAD_ZFS_VDEV_GUID,
		    &vdev_guid) != 0)
			pool_state = SPA_LOAD_OPEN;
		else
			pool_state = SPA_LOAD_NONE;
		detector = NULL;
	} else {
		(void) nvlist_lookup_nvlist(nvl,
		    FM_EREPORT_DETECTOR, &detector);
		(void) nvlist_lookup_int32(nvl,
		    FM_EREPORT_PAYLOAD_ZFS_POOL_CONTEXT, &pool_state);
	}

	/*
	 * We also ignore all ereports generated during an import of a pool,
	 * since the only possible fault (.pool) would result in import failure,
	 * and hence no persistent fault.  Some day we may want to do something
	 * with these ereports, so we continue generating them internally.
	 */
	if (pool_state == SPA_LOAD_IMPORT) {
		zfs_stats.import_drops.fmds_value.ui64++;
		fmd_hdl_debug(hdl, "ignoring '%s' during import", class);
		return;
	}

	/*
	 * Device I/O errors are ignored during pool open.
	 */
	if (pool_state == SPA_LOAD_OPEN &&
	    (fmd_nvl_class_match(hdl, nvl,
	    ZFS_MAKE_EREPORT(FM_EREPORT_ZFS_CHECKSUM)) ||
	    fmd_nvl_class_match(hdl, nvl,
	    ZFS_MAKE_EREPORT(FM_EREPORT_ZFS_IO)) ||
	    fmd_nvl_class_match(hdl, nvl,
	    ZFS_MAKE_EREPORT(FM_EREPORT_ZFS_PROBE_FAILURE)))) {
		fmd_hdl_debug(hdl, "ignoring '%s' during pool open", class);
		zfs_stats.dev_drops.fmds_value.ui64++;
		return;
	}

	/*
	 * We ignore ereports for anything except disks and files.
	 */
	if (nvlist_lookup_string(nvl, FM_EREPORT_PAYLOAD_ZFS_VDEV_TYPE,
	    &type) == 0) {
		if (strcmp(type, VDEV_TYPE_DISK) != 0 &&
		    strcmp(type, VDEV_TYPE_FILE) != 0) {
			zfs_stats.vdev_drops.fmds_value.ui64++;
			return;
		}
	}

	/*
	 * Determine if this ereport corresponds to an open case.
	 * Each vdev or pool can have a single case.
	 */
	(void) nvlist_lookup_uint64(nvl,
	    FM_EREPORT_PAYLOAD_ZFS_POOL_GUID, &pool_guid);
	if (nvlist_lookup_uint64(nvl,
	    FM_EREPORT_PAYLOAD_ZFS_VDEV_GUID, &vdev_guid) != 0)
		vdev_guid = 0;
	if (nvlist_lookup_uint64(nvl, FM_EREPORT_ENA, &ena) != 0)
		ena = 0;

	zfs_ereport_when(hdl, nvl, &er_when);

	for (zcp = uu_list_first(zfs_cases); zcp != NULL;
	    zcp = uu_list_next(zfs_cases, zcp)) {
		if (zcp->zc_data.zc_pool_guid == pool_guid) {
			pool_found = B_TRUE;
			pool_load = zcp->zc_when;
		}
		if (zcp->zc_data.zc_vdev_guid == vdev_guid)
			break;
	}

	/*
	 * Avoid falsely accusing a pool of being faulty.  Do so by
	 * not replaying ereports that were generated prior to the
	 * current import.  If the failure that generated them was
	 * transient because the device was actually removed but we
	 * didn't receive the normal asynchronous notification, we
	 * don't want to mark it as faulted and potentially panic. If
	 * there is still a problem we'd expect not to be able to
	 * import the pool, or that new ereports will be generated
	 * once the pool is used.
	 */
	if (pool_found && timeval_earlier(&er_when, &pool_load)) {
		fmd_hdl_debug(hdl, "ignoring pool %llx, "
		    "ereport time %lld.%lld, pool load time = %lld.%lld",
		    pool_guid, er_when.ertv_sec, er_when.ertv_nsec,
		    pool_load.ertv_sec, pool_load.ertv_nsec);
		zfs_stats.old_drops.fmds_value.ui64++;
		return;
	}

	if (!pool_found) {
		/*
		 * Haven't yet seen this pool, but same situation
		 * may apply.
		 */
		libzfs_handle_t *zhdl = fmd_hdl_getspecific(hdl);
		struct load_time_arg la;

		la.lt_guid = pool_guid;
		la.lt_time = &pool_load;
		la.lt_found = B_FALSE;

		if (zhdl != NULL &&
		    zpool_iter(zhdl, zpool_find_load_time, &la) == 0 &&
		    la.lt_found == B_TRUE) {
			pool_found = B_TRUE;

			if (timeval_earlier(&er_when, &pool_load)) {
				fmd_hdl_debug(hdl, "ignoring pool %llx, "
				    "ereport time %lld.%lld, "
				    "pool load time = %lld.%lld",
				    pool_guid, er_when.ertv_sec,
				    er_when.ertv_nsec, pool_load.ertv_sec,
				    pool_load.ertv_nsec);
				zfs_stats.old_drops.fmds_value.ui64++;
				return;
			}
		}
	}

	if (zcp == NULL) {
		fmd_case_t *cs;
		zfs_case_data_t data = { 0 };

		/*
		 * If this is one of our 'fake' resource ereports, and there is
		 * no case open, simply discard it.
		 */
		if (isresource) {
			zfs_stats.resource_drops.fmds_value.ui64++;
			fmd_hdl_debug(hdl, "discarding '%s for vdev %llu",
			    class, vdev_guid);
			return;
		}

		/*
		 * Skip tracking some ereports
		 */
		if (strcmp(class,
		    ZFS_MAKE_EREPORT(FM_EREPORT_ZFS_DATA)) == 0 ||
		    strcmp(class,
		    ZFS_MAKE_EREPORT(FM_EREPORT_ZFS_CONFIG_CACHE_WRITE)) == 0 ||
		    strcmp(class,
		    ZFS_MAKE_EREPORT(FM_EREPORT_ZFS_DELAY)) == 0) {
			zfs_stats.resource_drops.fmds_value.ui64++;
			return;
		}

		/*
		 * Open a new case.
		 */
		cs = fmd_case_open(hdl, NULL);

		fmd_hdl_debug(hdl, "opening case for vdev %llu due to '%s'",
		    vdev_guid, class);

		/*
		 * Initialize the case buffer.  To commonize code, we actually
		 * create the buffer with existing data, and then call
		 * zfs_case_unserialize() to instantiate the in-core structure.
		 */
		fmd_buf_create(hdl, cs, CASE_DATA, sizeof (zfs_case_data_t));

		data.zc_version = CASE_DATA_VERSION_SERD;
		data.zc_ena = ena;
		data.zc_pool_guid = pool_guid;
		data.zc_vdev_guid = vdev_guid;
		data.zc_pool_state = (int)pool_state;

		fmd_buf_write(hdl, cs, CASE_DATA, &data, sizeof (data));

		zcp = zfs_case_unserialize(hdl, cs);
		assert(zcp != NULL);
		if (pool_found)
			zcp->zc_when = pool_load;
	}

	if (isresource) {
		fmd_hdl_debug(hdl, "resource event '%s'", class);

		if (fmd_nvl_class_match(hdl, nvl,
		    ZFS_MAKE_RSRC(FM_RESOURCE_AUTOREPLACE))) {
			/*
			 * The 'resource.fs.zfs.autoreplace' event indicates
			 * that the pool was loaded with the 'autoreplace'
			 * property set.  In this case, any pending device
			 * failures should be ignored, as the asynchronous
			 * autoreplace handling will take care of them.
			 */
			fmd_case_close(hdl, zcp->zc_case);
		} else if (fmd_nvl_class_match(hdl, nvl,
		    ZFS_MAKE_RSRC(FM_RESOURCE_REMOVED))) {
			/*
			 * The 'resource.fs.zfs.removed' event indicates that
			 * device removal was detected, and the device was
			 * closed asynchronously.  If this is the case, we
			 * assume that any recent I/O errors were due to the
			 * device removal, not any fault of the device itself.
			 * We reset the SERD engine, and cancel any pending
			 * timers.
			 */
			if (zcp->zc_data.zc_has_remove_timer) {
				fmd_timer_remove(hdl, zcp->zc_remove_timer);
				zcp->zc_data.zc_has_remove_timer = 0;
				zfs_case_serialize(hdl, zcp);
			}
			if (zcp->zc_data.zc_serd_io[0] != '\0')
				fmd_serd_reset(hdl, zcp->zc_data.zc_serd_io);
			if (zcp->zc_data.zc_serd_checksum[0] != '\0')
				fmd_serd_reset(hdl,
				    zcp->zc_data.zc_serd_checksum);
		} else if (fmd_nvl_class_match(hdl, nvl,
		    ZFS_MAKE_RSRC(FM_RESOURCE_STATECHANGE))) {
			uint64_t state = 0;

			if (zcp != NULL &&
			    nvlist_lookup_uint64(nvl,
			    FM_EREPORT_PAYLOAD_ZFS_VDEV_STATE, &state) == 0 &&
			    state == VDEV_STATE_HEALTHY) {
				fmd_hdl_debug(hdl, "closing case after a "
				    "device statechange to healthy");
				fmd_case_close(hdl, zcp->zc_case);
			}
		}
		zfs_stats.resource_drops.fmds_value.ui64++;
		return;
	}

	/*
	 * Associate the ereport with this case.
	 */
	fmd_case_add_ereport(hdl, zcp->zc_case, ep);

	/*
	 * Don't do anything else if this case is already solved.
	 */
	if (fmd_case_solved(hdl, zcp->zc_case))
		return;

	fmd_hdl_debug(hdl, "error event '%s'", class);

	/*
	 * Determine if we should solve the case and generate a fault.  We solve
	 * a case if:
	 *
	 * 	a. A pool failed to open (ereport.fs.zfs.pool)
	 * 	b. A device failed to open (ereport.fs.zfs.pool) while a pool
	 *	   was up and running.
	 *
	 * We may see a series of ereports associated with a pool open, all
	 * chained together by the same ENA.  If the pool open succeeds, then
	 * we'll see no further ereports.  To detect when a pool open has
	 * succeeded, we associate a timer with the event.  When it expires, we
	 * close the case.
	 */
	if (fmd_nvl_class_match(hdl, nvl,
	    ZFS_MAKE_EREPORT(FM_EREPORT_ZFS_POOL))) {
		/*
		 * Pool level fault.  Before solving the case, go through and
		 * close any open device cases that may be pending.
		 */
		for (dcp = uu_list_first(zfs_cases); dcp != NULL;
		    dcp = uu_list_next(zfs_cases, dcp)) {
			if (dcp->zc_data.zc_pool_guid ==
			    zcp->zc_data.zc_pool_guid &&
			    dcp->zc_data.zc_vdev_guid != 0)
				fmd_case_close(hdl, dcp->zc_case);
		}

		zfs_case_solve(hdl, zcp, "fault.fs.zfs.pool", B_TRUE);
	} else if (fmd_nvl_class_match(hdl, nvl,
	    ZFS_MAKE_EREPORT(FM_EREPORT_ZFS_LOG_REPLAY))) {
		/*
		 * Pool level fault for reading the intent logs.
		 */
		zfs_case_solve(hdl, zcp, "fault.fs.zfs.log_replay", B_TRUE);
	} else if (fmd_nvl_class_match(hdl, nvl, "ereport.fs.zfs.vdev.*")) {
		/*
		 * Device fault.
		 */
		zfs_case_solve(hdl, zcp, "fault.fs.zfs.device",  B_TRUE);
	} else if (fmd_nvl_class_match(hdl, nvl,
	    ZFS_MAKE_EREPORT(FM_EREPORT_ZFS_IO)) ||
	    fmd_nvl_class_match(hdl, nvl,
	    ZFS_MAKE_EREPORT(FM_EREPORT_ZFS_CHECKSUM)) ||
	    fmd_nvl_class_match(hdl, nvl,
	    ZFS_MAKE_EREPORT(FM_EREPORT_ZFS_IO_FAILURE)) ||
	    fmd_nvl_class_match(hdl, nvl,
	    ZFS_MAKE_EREPORT(FM_EREPORT_ZFS_PROBE_FAILURE))) {
		char *failmode = NULL;
		boolean_t checkremove = B_FALSE;

		/*
		 * If this is a checksum or I/O error, then toss it into the
		 * appropriate SERD engine and check to see if it has fired.
		 * Ideally, we want to do something more sophisticated,
		 * (persistent errors for a single data block, etc).  For now,
		 * a single SERD engine is sufficient.
		 */
		if (fmd_nvl_class_match(hdl, nvl,
		    ZFS_MAKE_EREPORT(FM_EREPORT_ZFS_IO))) {
			if (zcp->zc_data.zc_serd_io[0] == '\0') {
				zfs_serd_name(zcp->zc_data.zc_serd_io,
				    pool_guid, vdev_guid, "io");
				fmd_serd_create(hdl, zcp->zc_data.zc_serd_io,
				    fmd_prop_get_int32(hdl, "io_N"),
				    fmd_prop_get_int64(hdl, "io_T"));
				zfs_case_serialize(hdl, zcp);
			}
			if (fmd_serd_record(hdl, zcp->zc_data.zc_serd_io, ep))
				checkremove = B_TRUE;
		} else if (fmd_nvl_class_match(hdl, nvl,
		    ZFS_MAKE_EREPORT(FM_EREPORT_ZFS_CHECKSUM))) {
			if (zcp->zc_data.zc_serd_checksum[0] == '\0') {
				zfs_serd_name(zcp->zc_data.zc_serd_checksum,
				    pool_guid, vdev_guid, "checksum");
				fmd_serd_create(hdl,
				    zcp->zc_data.zc_serd_checksum,
				    fmd_prop_get_int32(hdl, "checksum_N"),
				    fmd_prop_get_int64(hdl, "checksum_T"));
				zfs_case_serialize(hdl, zcp);
			}
			if (fmd_serd_record(hdl,
			    zcp->zc_data.zc_serd_checksum, ep)) {
				zfs_case_solve(hdl, zcp,
				    "fault.fs.zfs.vdev.checksum", B_FALSE);
			}
		} else if (fmd_nvl_class_match(hdl, nvl,
		    ZFS_MAKE_EREPORT(FM_EREPORT_ZFS_IO_FAILURE)) &&
		    (nvlist_lookup_string(nvl,
		    FM_EREPORT_PAYLOAD_ZFS_POOL_FAILMODE, &failmode) == 0) &&
		    failmode != NULL) {
			if (strncmp(failmode, FM_EREPORT_FAILMODE_CONTINUE,
			    strlen(FM_EREPORT_FAILMODE_CONTINUE)) == 0) {
				zfs_case_solve(hdl, zcp,
				    "fault.fs.zfs.io_failure_continue",
				    B_FALSE);
			} else if (strncmp(failmode, FM_EREPORT_FAILMODE_WAIT,
			    strlen(FM_EREPORT_FAILMODE_WAIT)) == 0) {
				zfs_case_solve(hdl, zcp,
				    "fault.fs.zfs.io_failure_wait", B_FALSE);
			}
		} else if (fmd_nvl_class_match(hdl, nvl,
		    ZFS_MAKE_EREPORT(FM_EREPORT_ZFS_PROBE_FAILURE))) {
#ifndef __linux__
			/* This causes an unexpected fault diagnosis on linux */
			checkremove = B_TRUE;
#endif
		}

		/*
		 * Because I/O errors may be due to device removal, we postpone
		 * any diagnosis until we're sure that we aren't about to
		 * receive a 'resource.fs.zfs.removed' event.
		 */
		if (checkremove) {
			if (zcp->zc_data.zc_has_remove_timer)
				fmd_timer_remove(hdl, zcp->zc_remove_timer);
			zcp->zc_remove_timer = fmd_timer_install(hdl, zcp, NULL,
			    zfs_remove_timeout);
			if (!zcp->zc_data.zc_has_remove_timer) {
				zcp->zc_data.zc_has_remove_timer = 1;
				zfs_case_serialize(hdl, zcp);
			}
		}
	}
}