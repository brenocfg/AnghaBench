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
struct TYPE_3__ {char* vdev_path; char* vdev_devid; char* vdev_fru; char* vdev_enc_sysfs_path; int /*<<< orphan*/  vdev_state; int /*<<< orphan*/  vdev_guid; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  class ;

/* Variables and functions */
 int /*<<< orphan*/  FM_CLASS ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_POOL ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_POOL_CONTEXT ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_POOL_GUID ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_POOL_STATE ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_DEVID ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_ENC_SYSFS_PATH ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_FRU ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_GUID ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_PATH ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_STATE ; 
 int /*<<< orphan*/  FM_RSRC_VERSION ; 
 int /*<<< orphan*/  FM_VERSION ; 
 scalar_t__ SPA_LOAD_TRYIMPORT ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 char* ZFS_ERROR_CLASS ; 
 int /*<<< orphan*/ * fm_nvlist_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_add_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nvlist_add_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_uint8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*,char const*) ; 
 int /*<<< orphan*/  spa_guid (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_load_state (int /*<<< orphan*/ *) ; 
 char* spa_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_state (int /*<<< orphan*/ *) ; 

nvlist_t *
zfs_event_create(spa_t *spa, vdev_t *vd, const char *type, const char *name,
    nvlist_t *aux)
{
	nvlist_t *resource = NULL;
#ifdef _KERNEL
	char class[64];

	if (spa_load_state(spa) == SPA_LOAD_TRYIMPORT)
		return (NULL);

	if ((resource = fm_nvlist_create(NULL)) == NULL)
		return (NULL);

	(void) snprintf(class, sizeof (class), "%s.%s.%s", type,
	    ZFS_ERROR_CLASS, name);
	VERIFY0(nvlist_add_uint8(resource, FM_VERSION, FM_RSRC_VERSION));
	VERIFY0(nvlist_add_string(resource, FM_CLASS, class));
	VERIFY0(nvlist_add_string(resource,
	    FM_EREPORT_PAYLOAD_ZFS_POOL, spa_name(spa)));
	VERIFY0(nvlist_add_uint64(resource,
	    FM_EREPORT_PAYLOAD_ZFS_POOL_GUID, spa_guid(spa)));
	VERIFY0(nvlist_add_uint64(resource,
	    FM_EREPORT_PAYLOAD_ZFS_POOL_STATE, spa_state(spa)));
	VERIFY0(nvlist_add_int32(resource,
	    FM_EREPORT_PAYLOAD_ZFS_POOL_CONTEXT, spa_load_state(spa)));

	if (vd) {
		VERIFY0(nvlist_add_uint64(resource,
		    FM_EREPORT_PAYLOAD_ZFS_VDEV_GUID, vd->vdev_guid));
		VERIFY0(nvlist_add_uint64(resource,
		    FM_EREPORT_PAYLOAD_ZFS_VDEV_STATE, vd->vdev_state));
		if (vd->vdev_path != NULL)
			VERIFY0(nvlist_add_string(resource,
			    FM_EREPORT_PAYLOAD_ZFS_VDEV_PATH, vd->vdev_path));
		if (vd->vdev_devid != NULL)
			VERIFY0(nvlist_add_string(resource,
			    FM_EREPORT_PAYLOAD_ZFS_VDEV_DEVID, vd->vdev_devid));
		if (vd->vdev_fru != NULL)
			VERIFY0(nvlist_add_string(resource,
			    FM_EREPORT_PAYLOAD_ZFS_VDEV_FRU, vd->vdev_fru));
		if (vd->vdev_enc_sysfs_path != NULL)
			VERIFY0(nvlist_add_string(resource,
			    FM_EREPORT_PAYLOAD_ZFS_VDEV_ENC_SYSFS_PATH,
			    vd->vdev_enc_sysfs_path));
	}

	/* also copy any optional payload data */
	if (aux) {
		nvpair_t *elem = NULL;

		while ((elem = nvlist_next_nvpair(aux, elem)) != NULL)
			(void) nvlist_add_nvpair(resource, elem);
	}

#endif
	return (resource);
}