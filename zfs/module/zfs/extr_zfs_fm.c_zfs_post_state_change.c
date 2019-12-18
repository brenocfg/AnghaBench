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
struct TYPE_4__ {scalar_t__ vdev_enc_sysfs_path; scalar_t__ vdev_physpath; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_ENC_SYSFS_PATH ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_LASTSTATE ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_PHYSPATH ; 
 int /*<<< orphan*/  FM_NVA_FREE ; 
 int /*<<< orphan*/  FM_RESOURCE_STATECHANGE ; 
 int /*<<< orphan*/  FM_RSRC_CLASS ; 
 int /*<<< orphan*/ * fm_nvlist_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fm_nvlist_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_post_common (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
zfs_post_state_change(spa_t *spa, vdev_t *vd, uint64_t laststate)
{
#ifdef _KERNEL
	nvlist_t *aux;

	/*
	 * Add optional supplemental keys to payload
	 */
	aux = fm_nvlist_create(NULL);
	if (vd && aux) {
		if (vd->vdev_physpath) {
			(void) nvlist_add_string(aux,
			    FM_EREPORT_PAYLOAD_ZFS_VDEV_PHYSPATH,
			    vd->vdev_physpath);
		}
		if (vd->vdev_enc_sysfs_path) {
			(void) nvlist_add_string(aux,
			    FM_EREPORT_PAYLOAD_ZFS_VDEV_ENC_SYSFS_PATH,
			    vd->vdev_enc_sysfs_path);
		}

		(void) nvlist_add_uint64(aux,
		    FM_EREPORT_PAYLOAD_ZFS_VDEV_LASTSTATE, laststate);
	}

	zfs_post_common(spa, vd, FM_RSRC_CLASS, FM_RESOURCE_STATECHANGE,
	    aux);

	if (aux)
		fm_nvlist_destroy(aux, FM_NVA_FREE);
#endif
}