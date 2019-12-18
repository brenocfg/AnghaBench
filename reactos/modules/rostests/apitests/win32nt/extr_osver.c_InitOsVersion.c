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
struct TYPE_2__ {int dwOSVersionInfoSize; int dwMajorVersion; int dwMinorVersion; } ;
typedef  int /*<<< orphan*/  OSVERSIONINFOW ;
typedef  int /*<<< orphan*/  LPOSVERSIONINFOW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetVersionExW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int g_OsIdx ; 
 TYPE_1__ g_OsVer ; 

BOOL InitOsVersion()
{
    g_OsVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);
    GetVersionExW((LPOSVERSIONINFOW)&g_OsVer);
    if (g_OsVer.dwMajorVersion == 4)
    {
        g_OsIdx = 0;
        return TRUE;
    }
    else if (g_OsVer.dwMajorVersion == 5)
    {
        if (g_OsVer.dwMinorVersion == 0)
        {
            g_OsIdx = 1;
            return TRUE;
        }
        else if (g_OsVer.dwMinorVersion == 1)
        {
            g_OsIdx = 2;
            return TRUE;
        }
        else if (g_OsVer.dwMinorVersion == 2)
        {
            g_OsIdx = 3;
            return TRUE;
        }
    }
    else if (g_OsVer.dwMajorVersion == 6)
    {
        g_OsIdx = 4;
        return TRUE;
    }
    return FALSE;
}