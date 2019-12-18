#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int zfs_prop_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_9__ {int /*<<< orphan*/  dd_lock; } ;
typedef  TYPE_1__ dsl_dir_t ;
struct TYPE_10__ {TYPE_1__* ds_dir; } ;
typedef  TYPE_2__ dsl_dataset_t ;

/* Variables and functions */
 int ENOENT ; 
#define  ZFS_PROP_LOGICALUSED 132 
#define  ZFS_PROP_USEDCHILD 131 
#define  ZFS_PROP_USEDDS 130 
#define  ZFS_PROP_USEDREFRESERV 129 
#define  ZFS_PROP_USEDSNAP 128 
 int /*<<< orphan*/  dsl_dir_get_logicalused (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dir_get_usedchild (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dir_get_usedds (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dir_get_usedrefreserv (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dir_get_usedsnap (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_dsl_dir_prop(dsl_dataset_t *ds, zfs_prop_t zfs_prop,
    uint64_t *val)
{
	dsl_dir_t *dd = ds->ds_dir;
	mutex_enter(&dd->dd_lock);
	switch (zfs_prop) {
	case ZFS_PROP_USEDSNAP:
		*val = dsl_dir_get_usedsnap(dd);
		break;
	case ZFS_PROP_USEDCHILD:
		*val = dsl_dir_get_usedchild(dd);
		break;
	case ZFS_PROP_USEDDS:
		*val = dsl_dir_get_usedds(dd);
		break;
	case ZFS_PROP_USEDREFRESERV:
		*val = dsl_dir_get_usedrefreserv(dd);
		break;
	case ZFS_PROP_LOGICALUSED:
		*val = dsl_dir_get_logicalused(dd);
		break;
	default:
		mutex_exit(&dd->dd_lock);
		return (ENOENT);
	}
	mutex_exit(&dd->dd_lock);
	return (0);
}