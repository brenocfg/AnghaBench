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
typedef  scalar_t__ zfs_prop_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  VERIFY (int) ; 
#define  ZFS_PROP_KEYLOCATION 129 
#define  ZFS_PROP_REFQUOTA 128 
 scalar_t__ nvlist_add_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_prev_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_remove_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_prop_to_name (scalar_t__ const) ; 

__attribute__((used)) static nvlist_t *
extract_delay_props(nvlist_t *props)
{
	nvlist_t *delayprops;
	nvpair_t *nvp, *tmp;
	static const zfs_prop_t delayable[] = {
		ZFS_PROP_REFQUOTA,
		ZFS_PROP_KEYLOCATION,
		0
	};
	int i;

	VERIFY(nvlist_alloc(&delayprops, NV_UNIQUE_NAME, KM_SLEEP) == 0);

	for (nvp = nvlist_next_nvpair(props, NULL); nvp != NULL;
	    nvp = nvlist_next_nvpair(props, nvp)) {
		/*
		 * strcmp() is safe because zfs_prop_to_name() always returns
		 * a bounded string.
		 */
		for (i = 0; delayable[i] != 0; i++) {
			if (strcmp(zfs_prop_to_name(delayable[i]),
			    nvpair_name(nvp)) == 0) {
				break;
			}
		}
		if (delayable[i] != 0) {
			tmp = nvlist_prev_nvpair(props, nvp);
			VERIFY(nvlist_add_nvpair(delayprops, nvp) == 0);
			VERIFY(nvlist_remove_nvpair(props, nvp) == 0);
			nvp = tmp;
		}
	}

	if (nvlist_empty(delayprops)) {
		nvlist_free(delayprops);
		delayprops = NULL;
	}
	return (delayprops);
}