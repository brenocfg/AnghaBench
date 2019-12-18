#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zfs_prop_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  cb_received; int /*<<< orphan*/  cb_propname; } ;
typedef  TYPE_1__ inherit_cbdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ ZPROP_INVAL ; 
 int /*<<< orphan*/  zfs_get_type (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_name_to_prop (int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_inherit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_prop_valid_for_type (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
inherit_recurse_cb(zfs_handle_t *zhp, void *data)
{
	inherit_cbdata_t *cb = data;
	zfs_prop_t prop = zfs_name_to_prop(cb->cb_propname);

	/*
	 * If we're doing it recursively, then ignore properties that
	 * are not valid for this type of dataset.
	 */
	if (prop != ZPROP_INVAL &&
	    !zfs_prop_valid_for_type(prop, zfs_get_type(zhp), B_FALSE))
		return (0);

	return (zfs_prop_inherit(zhp, cb->cb_propname, cb->cb_received) != 0);
}