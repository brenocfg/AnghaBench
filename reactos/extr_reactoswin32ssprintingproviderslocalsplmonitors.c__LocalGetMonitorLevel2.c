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
struct TYPE_3__ {scalar_t__ pwszFileName; scalar_t__ pwszName; } ;
typedef  scalar_t__ PWSTR ;
typedef  scalar_t__ PMONITOR_INFO_2W ;
typedef  TYPE_1__* PLOCAL_PRINT_MONITOR ;
typedef  int /*<<< orphan*/ * PDWORD ;
typedef  scalar_t__ PCWSTR ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int /*<<< orphan*/  MONITOR_INFO_2W ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  PackStrings (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cbCurrentEnvironment ; 
 int /*<<< orphan*/  dwMonitorInfo2Offsets ; 
 int wcslen (scalar_t__) ; 
 scalar_t__ wszCurrentEnvironment ; 

__attribute__((used)) static void
_LocalGetMonitorLevel2(PLOCAL_PRINT_MONITOR pPrintMonitor, PMONITOR_INFO_2W* ppMonitorInfo, PBYTE* ppMonitorInfoEnd, PDWORD pcbNeeded)
{
    DWORD cbFileName;
    DWORD cbMonitorName;
    PCWSTR pwszStrings[3];

    // Calculate the string lengths.
    if (!ppMonitorInfo)
    {
        cbMonitorName = (wcslen(pPrintMonitor->pwszName) + 1) * sizeof(WCHAR);
        cbFileName = (wcslen(pPrintMonitor->pwszFileName) + 1) * sizeof(WCHAR);

        *pcbNeeded += sizeof(MONITOR_INFO_2W) + cbMonitorName + cbCurrentEnvironment + cbFileName;
        return;
    }

    // Set the pName field.
    pwszStrings[0] = pPrintMonitor->pwszName;

    // Set the pEnvironment field.
    pwszStrings[1] = (PWSTR)wszCurrentEnvironment;

    // Set the pDLLName field.
    pwszStrings[2] = pPrintMonitor->pwszFileName;

    // Copy the structure and advance to the next one in the output buffer.
    *ppMonitorInfoEnd = PackStrings(pwszStrings, (PBYTE)(*ppMonitorInfo), dwMonitorInfo2Offsets, *ppMonitorInfoEnd);
    (*ppMonitorInfo)++;
}