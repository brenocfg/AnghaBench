#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v2 ;
typedef  int /*<<< orphan*/  v1 ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_9__ {scalar_t__ dwMajorVersion; scalar_t__ dwMinorVersion; scalar_t__ dwBuildNumber; scalar_t__ dwPlatformId; scalar_t__ wServicePackMajor; int wFlags; scalar_t__ wServicePackMinor; } ;
typedef  TYPE_1__ VersionLieInfo ;
struct TYPE_11__ {int member_0; int dwOSVersionInfoSize; scalar_t__ dwMajorVersion; scalar_t__ dwMinorVersion; scalar_t__ dwBuildNumber; scalar_t__ dwPlatformId; scalar_t__ wServicePackMajor; scalar_t__ wServicePackMinor; scalar_t__ wSuiteMask; scalar_t__ wProductType; scalar_t__ wReserved; int /*<<< orphan*/ * szCSDVersion; int /*<<< orphan*/  member_1; } ;
struct TYPE_10__ {scalar_t__ (* OriginalFunction ) (int /*<<< orphan*/ ) ;scalar_t__ ReplacementFunction; } ;
typedef  TYPE_2__* PHOOKAPI ;
typedef  int /*<<< orphan*/  PCSTR ;
typedef  int /*<<< orphan*/  OSVERSIONINFOW ;
typedef  TYPE_3__ OSVERSIONINFOEXW ;
typedef  int /*<<< orphan*/  LPOSVERSIONINFOW ;
typedef  scalar_t__ (* GETVERSIONEXWPROC ) (TYPE_3__*) ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int FLAG_BUGGY_ServicePackMajorMinor ; 
 scalar_t__ GetVersionExW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StringCchPrintfW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_3__*,int) ; 
 int /*<<< orphan*/  _countof (int /*<<< orphan*/ *) ; 
 scalar_t__ lstrcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char*,int,...) ; 
 scalar_t__ stub1 (TYPE_3__*) ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  winetest_ok (int,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void verify_shimw_imp(PHOOKAPI hook, const VersionLieInfo* info, PCSTR shim, int same, int first_might_be_broken)
{
    OSVERSIONINFOEXW v1 = { sizeof(v1), 0 }, v2 = { sizeof(v2), 0 };
    BOOL ok1, ok2, first = TRUE;

    if (!same)
    {
        skip("Skipping implementation tests for %s\n", shim);
        return;
    }

    while (v1.dwOSVersionInfoSize)
    {
        ok1 = GetVersionExW((LPOSVERSIONINFOW)&v1);
        hook->OriginalFunction = GetVersionExW;

        ok2 = ((GETVERSIONEXWPROC)hook->ReplacementFunction)(&v2);

        if (first_might_be_broken && first && ok1 == TRUE && ok2 == FALSE)
        {
            skip("Skipping first check because 0x%x is (falsely) not accepted by the shim %s\n", sizeof(v1), shim);
        }
        else
        {
            winetest_ok(ok1 == ok2, "Expected ok1 to equal ok2, was: %i, %i for %s(first:%d)\n", ok1, ok2, shim, first);
        }
        if (ok1 && ok2)
        {
            WCHAR szCSDVersion[128] = { 0 };
            winetest_ok(v1.dwOSVersionInfoSize == v2.dwOSVersionInfoSize, "Expected dwOSVersionInfoSize to be equal, was: %u, %u for %s\n", v1.dwOSVersionInfoSize, v2.dwOSVersionInfoSize, shim);
            winetest_ok(info->dwMajorVersion == v2.dwMajorVersion, "Expected dwMajorVersion to be equal, was: %u, %u for %s\n", info->dwMajorVersion, v2.dwMajorVersion, shim);
            winetest_ok(info->dwMinorVersion == v2.dwMinorVersion, "Expected dwMinorVersion to be equal, was: %u, %u for %s\n", info->dwMinorVersion, v2.dwMinorVersion, shim);
            winetest_ok(info->dwBuildNumber == v2.dwBuildNumber, "Expected dwBuildNumber to be equal, was: %u, %u for %s\n", info->dwBuildNumber, v2.dwBuildNumber, shim);
            winetest_ok(info->dwPlatformId == v2.dwPlatformId, "Expected dwPlatformId to be equal, was: %u, %u for %s\n", info->dwPlatformId, v2.dwPlatformId, shim);

            if (info->wServicePackMajor)
                StringCchPrintfW(szCSDVersion, _countof(szCSDVersion), L"Service Pack %u", info->wServicePackMajor);
            winetest_ok(lstrcmpW(szCSDVersion, v2.szCSDVersion) == 0, "Expected szCSDVersion to be equal, was: %s, %s for %s\n", wine_dbgstr_w(szCSDVersion), wine_dbgstr_w(v2.szCSDVersion), shim);

            if (v1.dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXW))
            {
                if (!(info->wFlags & FLAG_BUGGY_ServicePackMajorMinor))
                {
                    winetest_ok(info->wServicePackMajor == v2.wServicePackMajor, "Expected wServicePackMajor to be equal, was: %i, %i for %s\n", info->wServicePackMajor, v2.wServicePackMajor, shim);
                    winetest_ok(info->wServicePackMinor == v2.wServicePackMinor, "Expected wServicePackMinor to be equal, was: %i, %i for %s\n", info->wServicePackMinor, v2.wServicePackMinor, shim);
                }
                else
                {
                    winetest_ok(v1.wServicePackMajor == v2.wServicePackMajor, "Expected wServicePackMajor to be equal, was: %i, %i for %s\n", v1.wServicePackMajor, v2.wServicePackMajor, shim);
                    winetest_ok(v1.wServicePackMinor == v2.wServicePackMinor, "Expected wServicePackMinor to be equal, was: %i, %i for %s\n", v1.wServicePackMinor, v2.wServicePackMinor, shim);
                }
                winetest_ok(v1.wSuiteMask == v2.wSuiteMask, "Expected wSuiteMask to be equal, was: %i, %i for %s\n", v1.wSuiteMask, v2.wSuiteMask, shim);
                winetest_ok(v1.wProductType == v2.wProductType, "Expected wProductType to be equal, was: %i, %i for %s\n", v1.wProductType, v2.wProductType, shim);
                winetest_ok(v1.wReserved == v2.wReserved, "Expected wReserved to be equal, was: %i, %i for %s\n", v1.wReserved, v2.wReserved, shim);
            }
            else
            {
                winetest_ok(v1.wServicePackMajor == 0 && v2.wServicePackMajor == 0, "Expected wServicePackMajor to be 0, was: %i, %i for %s\n", v1.wServicePackMajor, v2.wServicePackMajor, shim);
                winetest_ok(v1.wServicePackMinor == 0 && v2.wServicePackMinor == 0, "Expected wServicePackMinor to be 0, was: %i, %i for %s\n", v1.wServicePackMinor, v2.wServicePackMinor, shim);
                winetest_ok(v1.wSuiteMask == 0 && v2.wSuiteMask == 0, "Expected wSuiteMask to be 0, was: %i, %i for %s\n", v1.wSuiteMask, v2.wSuiteMask, shim);
                winetest_ok(v1.wProductType == 0 && v2.wProductType == 0, "Expected wProductType to be 0, was: %i, %i for %s\n", v1.wProductType, v2.wProductType, shim);
                winetest_ok(v1.wReserved == 0 && v2.wReserved == 0, "Expected wReserved to be 0, was: %i, %i for %s\n", v1.wReserved, v2.wReserved, shim);
            }
        }

        ZeroMemory(&v1, sizeof(v1));
        ZeroMemory(&v2, sizeof(v2));
        if (v1.dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXW))
            v1.dwOSVersionInfoSize = v2.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);
        first = FALSE;
    }
}