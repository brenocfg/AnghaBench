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
typedef  int /*<<< orphan*/  PSP_DEVINFO_DATA ;
typedef  int /*<<< orphan*/  PDWORD ;
typedef  scalar_t__ PBYTE ;
typedef  int /*<<< orphan*/  HDEVINFO ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 scalar_t__ SetupDiGetDeviceRegistryPropertyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wPropertyBuffer ; 
 int /*<<< orphan*/  walloc (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ wchar_to_utf8_no_alloc (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wfree (scalar_t__) ; 

__attribute__((used)) static __inline BOOL SetupDiGetDeviceRegistryPropertyU(HDEVINFO DeviceInfoSet, PSP_DEVINFO_DATA DeviceInfoData,
	DWORD Property, PDWORD PropertyRegDataType, PBYTE PropertyBuffer, DWORD PropertyBufferSize, PDWORD RequiredSize)
{
	BOOL ret = FALSE;
	DWORD err = ERROR_INVALID_DATA;
	// coverity[returned_null]
	walloc(PropertyBuffer, PropertyBufferSize);

	ret = SetupDiGetDeviceRegistryPropertyW(DeviceInfoSet, DeviceInfoData, Property,
		PropertyRegDataType, (PBYTE)wPropertyBuffer, PropertyBufferSize, RequiredSize);
	err = GetLastError();
	if ((ret != 0) && (wchar_to_utf8_no_alloc(wPropertyBuffer,
		(char*)(uintptr_t)PropertyBuffer, PropertyBufferSize) == 0)) {
		err = GetLastError();
		ret = FALSE;
	}
	wfree(PropertyBuffer);
	SetLastError(err);
	return ret;
}