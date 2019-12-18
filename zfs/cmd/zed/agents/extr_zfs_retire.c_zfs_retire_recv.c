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
struct TYPE_4__ {int /*<<< orphan*/ * zrd_hdl; } ;
typedef  TYPE_1__ zfs_retire_data_t ;
typedef  int /*<<< orphan*/  vdev_aux_t ;
typedef  size_t uint_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;
typedef  int /*<<< orphan*/  fmd_event_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_POOL_GUID ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_GUID ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_STATE ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_TYPE ; 
 int /*<<< orphan*/  FM_FAULT_RESOURCE ; 
 int /*<<< orphan*/  FM_FMRI_SCHEME ; 
 char* FM_FMRI_SCHEME_ZFS ; 
 int /*<<< orphan*/  FM_FMRI_ZFS_POOL ; 
 int /*<<< orphan*/  FM_FMRI_ZFS_VDEV ; 
 char* FM_LIST_REPAIRED_CLASS ; 
 char* FM_LIST_RESOLVED_CLASS ; 
 int /*<<< orphan*/  FM_SUSPECT_FAULT_LIST ; 
 int /*<<< orphan*/  FM_SUSPECT_RETIRE ; 
 int /*<<< orphan*/  FM_SUSPECT_UUID ; 
 int /*<<< orphan*/  VDEV_AUX_ERR_EXCEEDED ; 
 scalar_t__ VDEV_STATE_HEALTHY ; 
 char* VDEV_TYPE_L2CACHE ; 
 int /*<<< orphan*/ * find_by_guid (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  fmd_case_uuresolved (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fmd_hdl_debug (int /*<<< orphan*/ *,char*,char const*,...) ; 
 TYPE_1__* fmd_hdl_getspecific (int /*<<< orphan*/ *) ; 
 scalar_t__ fmd_nvl_class_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fmd_prop_get_int32 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ nvlist_lookup_boolean_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,size_t*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ replace_with_spare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  zfs_retire_clear_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_vdev_repair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_vdev_clear (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  zpool_vdev_degrade (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_vdev_fault (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 char* zpool_vdev_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  zpool_vdev_offline (int /*<<< orphan*/ *,char*,scalar_t__) ; 

__attribute__((used)) static void
zfs_retire_recv(fmd_hdl_t *hdl, fmd_event_t *ep, nvlist_t *nvl,
    const char *class)
{
	uint64_t pool_guid, vdev_guid;
	zpool_handle_t *zhp;
	nvlist_t *resource, *fault;
	nvlist_t **faults;
	uint_t f, nfaults;
	zfs_retire_data_t *zdp = fmd_hdl_getspecific(hdl);
	libzfs_handle_t *zhdl = zdp->zrd_hdl;
	boolean_t fault_device, degrade_device;
	boolean_t is_repair;
	char *scheme;
	nvlist_t *vdev = NULL;
	char *uuid;
	int repair_done = 0;
	boolean_t retire;
	boolean_t is_disk;
	vdev_aux_t aux;
	uint64_t state = 0;

	fmd_hdl_debug(hdl, "zfs_retire_recv: '%s'", class);

	/*
	 * If this is a resource notifying us of device removal then simply
	 * check for an available spare and continue unless the device is a
	 * l2arc vdev, in which case we just offline it.
	 */
	if (strcmp(class, "resource.fs.zfs.removed") == 0) {
		char *devtype;
		char *devname;

		if (nvlist_lookup_uint64(nvl, FM_EREPORT_PAYLOAD_ZFS_POOL_GUID,
		    &pool_guid) != 0 ||
		    nvlist_lookup_uint64(nvl, FM_EREPORT_PAYLOAD_ZFS_VDEV_GUID,
		    &vdev_guid) != 0)
			return;

		if ((zhp = find_by_guid(zhdl, pool_guid, vdev_guid,
		    &vdev)) == NULL)
			return;

		devname = zpool_vdev_name(NULL, zhp, vdev, B_FALSE);

		/* Can't replace l2arc with a spare: offline the device */
		if (nvlist_lookup_string(nvl, FM_EREPORT_PAYLOAD_ZFS_VDEV_TYPE,
		    &devtype) == 0 && strcmp(devtype, VDEV_TYPE_L2CACHE) == 0) {
			fmd_hdl_debug(hdl, "zpool_vdev_offline '%s'", devname);
			zpool_vdev_offline(zhp, devname, B_TRUE);
		} else if (!fmd_prop_get_int32(hdl, "spare_on_remove") ||
		    replace_with_spare(hdl, zhp, vdev) == B_FALSE) {
			/* Could not handle with spare: offline the device */
			fmd_hdl_debug(hdl, "zpool_vdev_offline '%s'", devname);
			zpool_vdev_offline(zhp, devname, B_TRUE);
		}

		free(devname);
		zpool_close(zhp);
		return;
	}

	if (strcmp(class, FM_LIST_RESOLVED_CLASS) == 0)
		return;

	/*
	 * Note: on zfsonlinux statechange events are more than just
	 * healthy ones so we need to confirm the actual state value.
	 */
	if (strcmp(class, "resource.fs.zfs.statechange") == 0 &&
	    nvlist_lookup_uint64(nvl, FM_EREPORT_PAYLOAD_ZFS_VDEV_STATE,
	    &state) == 0 && state == VDEV_STATE_HEALTHY) {
		zfs_vdev_repair(hdl, nvl);
		return;
	}
	if (strcmp(class, "sysevent.fs.zfs.vdev_remove") == 0) {
		zfs_vdev_repair(hdl, nvl);
		return;
	}

	zfs_retire_clear_data(hdl, zdp);

	if (strcmp(class, FM_LIST_REPAIRED_CLASS) == 0)
		is_repair = B_TRUE;
	else
		is_repair = B_FALSE;

	/*
	 * We subscribe to zfs faults as well as all repair events.
	 */
	if (nvlist_lookup_nvlist_array(nvl, FM_SUSPECT_FAULT_LIST,
	    &faults, &nfaults) != 0)
		return;

	for (f = 0; f < nfaults; f++) {
		fault = faults[f];

		fault_device = B_FALSE;
		degrade_device = B_FALSE;
		is_disk = B_FALSE;

		if (nvlist_lookup_boolean_value(fault, FM_SUSPECT_RETIRE,
		    &retire) == 0 && retire == 0)
			continue;

		/*
		 * While we subscribe to fault.fs.zfs.*, we only take action
		 * for faults targeting a specific vdev (open failure or SERD
		 * failure).  We also subscribe to fault.io.* events, so that
		 * faulty disks will be faulted in the ZFS configuration.
		 */
		if (fmd_nvl_class_match(hdl, fault, "fault.fs.zfs.vdev.io")) {
			fault_device = B_TRUE;
		} else if (fmd_nvl_class_match(hdl, fault,
		    "fault.fs.zfs.vdev.checksum")) {
			degrade_device = B_TRUE;
		} else if (fmd_nvl_class_match(hdl, fault,
		    "fault.fs.zfs.device")) {
			fault_device = B_FALSE;
		} else if (fmd_nvl_class_match(hdl, fault, "fault.io.*")) {
			is_disk = B_TRUE;
			fault_device = B_TRUE;
		} else {
			continue;
		}

		if (is_disk) {
			continue;
		} else {
			/*
			 * This is a ZFS fault.  Lookup the resource, and
			 * attempt to find the matching vdev.
			 */
			if (nvlist_lookup_nvlist(fault, FM_FAULT_RESOURCE,
			    &resource) != 0 ||
			    nvlist_lookup_string(resource, FM_FMRI_SCHEME,
			    &scheme) != 0)
				continue;

			if (strcmp(scheme, FM_FMRI_SCHEME_ZFS) != 0)
				continue;

			if (nvlist_lookup_uint64(resource, FM_FMRI_ZFS_POOL,
			    &pool_guid) != 0)
				continue;

			if (nvlist_lookup_uint64(resource, FM_FMRI_ZFS_VDEV,
			    &vdev_guid) != 0) {
				if (is_repair)
					vdev_guid = 0;
				else
					continue;
			}

			if ((zhp = find_by_guid(zhdl, pool_guid, vdev_guid,
			    &vdev)) == NULL)
				continue;

			aux = VDEV_AUX_ERR_EXCEEDED;
		}

		if (vdev_guid == 0) {
			/*
			 * For pool-level repair events, clear the entire pool.
			 */
			fmd_hdl_debug(hdl, "zpool_clear of pool '%s'",
			    zpool_get_name(zhp));
			(void) zpool_clear(zhp, NULL, NULL);
			zpool_close(zhp);
			continue;
		}

		/*
		 * If this is a repair event, then mark the vdev as repaired and
		 * continue.
		 */
		if (is_repair) {
			repair_done = 1;
			fmd_hdl_debug(hdl, "zpool_clear of pool '%s' vdev %llu",
			    zpool_get_name(zhp), vdev_guid);
			(void) zpool_vdev_clear(zhp, vdev_guid);
			zpool_close(zhp);
			continue;
		}

		/*
		 * Actively fault the device if needed.
		 */
		if (fault_device)
			(void) zpool_vdev_fault(zhp, vdev_guid, aux);
		if (degrade_device)
			(void) zpool_vdev_degrade(zhp, vdev_guid, aux);

		if (fault_device || degrade_device)
			fmd_hdl_debug(hdl, "zpool_vdev_%s: vdev %llu on '%s'",
			    fault_device ? "fault" : "degrade", vdev_guid,
			    zpool_get_name(zhp));

		/*
		 * Attempt to substitute a hot spare.
		 */
		(void) replace_with_spare(hdl, zhp, vdev);
		zpool_close(zhp);
	}

	if (strcmp(class, FM_LIST_REPAIRED_CLASS) == 0 && repair_done &&
	    nvlist_lookup_string(nvl, FM_SUSPECT_UUID, &uuid) == 0)
		fmd_case_uuresolved(hdl, uuid);
}