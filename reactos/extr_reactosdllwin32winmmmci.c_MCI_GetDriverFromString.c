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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  wDeviceID; scalar_t__ lpstrAlias; scalar_t__ lpstrDeviceType; scalar_t__ lpstrElementName; struct TYPE_3__* lpNext; } ;
typedef  TYPE_1__* LPWINE_MCIDRIVER ;
typedef  scalar_t__ LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MCI_ALL_DEVICE_ID ; 
 TYPE_1__* MciDrivers ; 
 int /*<<< orphan*/  WINMM_cs ; 
 scalar_t__ strcmpW (scalar_t__,scalar_t__) ; 
 scalar_t__ strcmpiW (scalar_t__,scalar_t__) ; 
 scalar_t__ wszAll ; 

__attribute__((used)) static UINT MCI_GetDriverFromString(LPCWSTR lpstrName)
{
    LPWINE_MCIDRIVER	wmd;
    UINT		ret = 0;

    if (!lpstrName)
	return 0;

    if (!strcmpiW(lpstrName, wszAll))
	return MCI_ALL_DEVICE_ID;

    EnterCriticalSection(&WINMM_cs);
    for (wmd = MciDrivers; wmd; wmd = wmd->lpNext) {
	if (wmd->lpstrElementName && strcmpW(wmd->lpstrElementName, lpstrName) == 0) {
	    ret = wmd->wDeviceID;
	    break;
	}
	if (wmd->lpstrDeviceType && strcmpiW(wmd->lpstrDeviceType, lpstrName) == 0) {
	    ret = wmd->wDeviceID;
	    break;
	}
	if (wmd->lpstrAlias && strcmpiW(wmd->lpstrAlias, lpstrName) == 0) {
	    ret = wmd->wDeviceID;
	    break;
	}
    }
    LeaveCriticalSection(&WINMM_cs);

    return ret;
}