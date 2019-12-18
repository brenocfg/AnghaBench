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
typedef  int /*<<< orphan*/  PBOOL ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateDriverForPlugAndPlayDevicesW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wFullInfPath ; 
 int /*<<< orphan*/  wHardwareId ; 
 int /*<<< orphan*/  wconvert (char const*) ; 
 int /*<<< orphan*/  wfree (char const*) ; 

__attribute__((used)) static __inline BOOL UpdateDriverForPlugAndPlayDevicesU(HWND hwndParent, const char* HardwareId, const char* FullInfPath,
														DWORD InstallFlags, PBOOL bRebootRequired)
{
	BOOL ret = FALSE;
	DWORD err = ERROR_INVALID_DATA;
	wconvert(HardwareId);
	wconvert(FullInfPath);
	ret = UpdateDriverForPlugAndPlayDevicesW(hwndParent, wHardwareId, wFullInfPath, InstallFlags, bRebootRequired);
	err = GetLastError();
	wfree(HardwareId);
	wfree(FullInfPath);
	SetLastError(err);
	return ret;
}