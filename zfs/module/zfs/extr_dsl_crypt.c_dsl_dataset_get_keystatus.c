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
typedef  int /*<<< orphan*/  zfs_keystatus_t ;
struct TYPE_4__ {scalar_t__ dd_crypto_obj; } ;
typedef  TYPE_1__ dsl_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_KEYSTATUS_AVAILABLE ; 
 int /*<<< orphan*/  ZFS_KEYSTATUS_NONE ; 
 int /*<<< orphan*/  ZFS_KEYSTATUS_UNAVAILABLE ; 
 scalar_t__ dmu_objset_check_wkey_loaded (TYPE_1__*) ; 

__attribute__((used)) static zfs_keystatus_t
dsl_dataset_get_keystatus(dsl_dir_t *dd)
{
	/* check if this dd has a has a dsl key */
	if (dd->dd_crypto_obj == 0)
		return (ZFS_KEYSTATUS_NONE);

	return (dmu_objset_check_wkey_loaded(dd) == 0 ?
	    ZFS_KEYSTATUS_AVAILABLE : ZFS_KEYSTATUS_UNAVAILABLE);
}