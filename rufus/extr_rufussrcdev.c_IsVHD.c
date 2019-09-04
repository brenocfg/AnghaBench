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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ARRAYSIZE (char const**) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ enable_vmdk ; 
 int /*<<< orphan*/ * safe_strstr (char const*,char const*) ; 

__attribute__((used)) static __inline BOOL IsVHD(const char* buffer)
{
	int i;
	// List of the Hardware IDs of the VHD devices we know
	const char* vhd_name[] = {
		"Arsenal_________Virtual_",
		"KernSafeVirtual_________",
		"Msft____Virtual_Disk____",
		"VMware__VMware_Virtual_S"	// Enabled through a cheat mode, as this lists primary disks on VMWare instances
	};

	for (i = 0; i < (int)(ARRAYSIZE(vhd_name)-(enable_vmdk?0:1)); i++)
		if (safe_strstr(buffer, vhd_name[i]) != NULL)
			return TRUE;
	return FALSE;
}