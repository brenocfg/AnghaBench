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

/* Variables and functions */
 int /*<<< orphan*/  DETACH_VIRTUAL_DISK_FLAG_NONE ; 
 int /*<<< orphan*/  DetachVirtualDisk ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  PF_INIT_OR_OUT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VirtDisk ; 
 int /*<<< orphan*/ * mounted_handle ; 
 int /*<<< orphan*/  pfDetachVirtualDisk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* physical_path ; 
 int /*<<< orphan*/  safe_closehandle (int /*<<< orphan*/ *) ; 

void UnMountISO(void)
{
	PF_INIT_OR_OUT(DetachVirtualDisk, VirtDisk);

	if ((mounted_handle == NULL) || (mounted_handle == INVALID_HANDLE_VALUE))
		goto out;

	pfDetachVirtualDisk(mounted_handle, DETACH_VIRTUAL_DISK_FLAG_NONE, 0);
	safe_closehandle(mounted_handle);
out:
	physical_path[0] = 0;
}