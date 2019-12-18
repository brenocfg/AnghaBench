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
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  cb_received; int /*<<< orphan*/  cb_propname; } ;
typedef  TYPE_1__ inherit_cbdata_t ;

/* Variables and functions */
 scalar_t__ zfs_prop_inherit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
inherit_cb(zfs_handle_t *zhp, void *data)
{
	inherit_cbdata_t *cb = data;

	return (zfs_prop_inherit(zhp, cb->cb_propname, cb->cb_received) != 0);
}