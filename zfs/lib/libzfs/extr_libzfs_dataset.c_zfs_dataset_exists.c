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
typedef  int zfs_type_t ;
struct TYPE_4__ {int zfs_type; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 TYPE_1__* make_dataset_handle (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  zfs_close (TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_validate_name (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 

boolean_t
zfs_dataset_exists(libzfs_handle_t *hdl, const char *path, zfs_type_t types)
{
	zfs_handle_t *zhp;

	if (!zfs_validate_name(hdl, path, types, B_FALSE))
		return (B_FALSE);

	/*
	 * Try to get stats for the dataset, which will tell us if it exists.
	 */
	if ((zhp = make_dataset_handle(hdl, path)) != NULL) {
		int ds_type = zhp->zfs_type;

		zfs_close(zhp);
		if (types & ds_type)
			return (B_TRUE);
	}
	return (B_FALSE);
}