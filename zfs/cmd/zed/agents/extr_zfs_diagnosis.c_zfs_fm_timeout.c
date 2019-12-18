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
struct TYPE_3__ {scalar_t__ zc_remove_timer; } ;
typedef  TYPE_1__ zfs_case_t ;
typedef  scalar_t__ id_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  zfs_case_solve (int /*<<< orphan*/ *,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zfs_fm_timeout(fmd_hdl_t *hdl, id_t id, void *data)
{
	zfs_case_t *zcp = data;

	if (id == zcp->zc_remove_timer)
		zfs_case_solve(hdl, zcp, "fault.fs.zfs.vdev.io", B_FALSE);
}