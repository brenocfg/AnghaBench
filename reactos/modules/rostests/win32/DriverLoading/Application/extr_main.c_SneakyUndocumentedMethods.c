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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ConvertPath (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* DRIVER_NAME ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ LoadVia_SystemExtendServiceTableInformation (int /*<<< orphan*/ *) ; 
 scalar_t__ LoadVia_SystemLoadGdiDriverInformation (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  NtStopDriver (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wprintf (char*,...) ; 

__attribute__((used)) static BOOL
SneakyUndocumentedMethods(LPCWSTR lpDriverPath)
{
    WCHAR szDevice[MAX_PATH];

    if (ConvertPath(lpDriverPath, szDevice))
    {
        wprintf(L"\nStarting %s.sys via NtSetSystemInformation with SystemLoadGdiDriverInformation\n", DRIVER_NAME);
        if (LoadVia_SystemLoadGdiDriverInformation(szDevice))
        {
            wprintf(L"\tStarted\n");

            NtStopDriver(DRIVER_NAME);
        }

        wprintf(L"\nStarting %s.sys via NtSetSystemInformation with SystemExtendServiceTableInformation\n", DRIVER_NAME);
        if (LoadVia_SystemExtendServiceTableInformation(szDevice))
        {
            wprintf(L"\tStarted\n");
            
            NtStopDriver(DRIVER_NAME);
        }

        return TRUE;
    }

    return FALSE;
}