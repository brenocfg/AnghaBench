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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  pwszName; } ;
typedef  scalar_t__ PMONITOR_INFO_1W ;
typedef  TYPE_1__* PLOCAL_PRINT_MONITOR ;
typedef  int* PDWORD ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int /*<<< orphan*/  MONITOR_INFO_1W ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  PackStrings (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwMonitorInfo1Offsets ; 
 int wcslen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_LocalGetMonitorLevel1(PLOCAL_PRINT_MONITOR pPrintMonitor, PMONITOR_INFO_1W* ppMonitorInfo, PBYTE* ppMonitorInfoEnd, PDWORD pcbNeeded)
{
    DWORD cbMonitorName;
    PCWSTR pwszStrings[1];

    // Calculate the string lengths.
    if (!ppMonitorInfo)
    {
        cbMonitorName = (wcslen(pPrintMonitor->pwszName) + 1) * sizeof(WCHAR);

        *pcbNeeded += sizeof(MONITOR_INFO_1W) + cbMonitorName;
        return;
    }

    // Set the pName field.
    pwszStrings[0] = pPrintMonitor->pwszName;

    // Copy the structure and advance to the next one in the output buffer.
    *ppMonitorInfoEnd = PackStrings(pwszStrings, (PBYTE)(*ppMonitorInfo), dwMonitorInfo1Offsets, *ppMonitorInfoEnd);
    (*ppMonitorInfo)++;
}