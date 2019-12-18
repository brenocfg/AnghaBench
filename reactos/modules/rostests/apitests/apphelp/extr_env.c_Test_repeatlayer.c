#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ QuadPart; } ;
struct TYPE_5__ {scalar_t__ QuadPart; } ;
struct TYPE_7__ {scalar_t__ AppCompatInfo; scalar_t__ ShimDataSize; int /*<<< orphan*/ * pShimData; TYPE_2__ AppCompatFlagsUser; TYPE_1__ AppCompatFlags; } ;
typedef  TYPE_3__ test_RemoteShimInfo ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDB_MAX_LAYERS ; 
 int /*<<< orphan*/  SetEnvironmentVariableA (char*,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TerminateProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Validate_ShimData_Win10 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char const**) ; 
 int /*<<< orphan*/  Validate_ShimData_Win2k3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  Validate_ShimData_Win7 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**) ; 
 scalar_t__ WINVER_VISTA ; 
 scalar_t__ WINVER_WIN10 ; 
 int /*<<< orphan*/  create_proc (int /*<<< orphan*/ ) ; 
 scalar_t__ g_ShimDataSize ; 
 scalar_t__ g_WinVersion ; 
 scalar_t__ get_shiminfo (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (scalar_t__) ; 

__attribute__((used)) static void Test_repeatlayer(WCHAR szApphelp[256])
{
    static const char* layers[] = {
        "256Color", "256Color", "256Color", "256Color",
        "256Color", "256Color", "256Color", "256Color" };

    HANDLE proc;
    test_RemoteShimInfo info;
    BOOL res;

    SetEnvironmentVariableA("__COMPAT_LAYER", "256Color 256Color 256Color 256Color 256Color 256Color 256Color 256Color");


    proc = create_proc(TRUE);
    res = get_shiminfo(proc, &info);
    TerminateProcess(proc, 0);
    CloseHandle(proc);

    if (res)
    {
        ok(info.AppCompatFlags.QuadPart == 0, "Expected AppCompatFlags to be 0, was: %s\n", wine_dbgstr_longlong(info.AppCompatFlags.QuadPart));
        ok(info.AppCompatFlagsUser.QuadPart == 0, "Expected AppCompatFlagsUser to be 0, was: %s\n", wine_dbgstr_longlong(info.AppCompatFlagsUser.QuadPart));
        ok(info.AppCompatInfo == 0, "Expected AppCompatInfo to be 0, was: %p\n", info.AppCompatInfo);
        ok(info.pShimData != NULL, "Expected pShimData to be valid, was NULL\n");
        ok(info.ShimDataSize == g_ShimDataSize, "Expected ShimDataSize to be %u, was: %u\n", g_ShimDataSize, info.ShimDataSize);
        if (info.pShimData)
        {
            /* Win10 only 'loads' one layer */
            if (g_WinVersion < WINVER_VISTA)
                Validate_ShimData_Win2k3(info.pShimData, SDB_MAX_LAYERS, layers);
            else if (g_WinVersion < WINVER_WIN10)
                Validate_ShimData_Win7(info.pShimData, szApphelp, SDB_MAX_LAYERS, layers);
            else
                Validate_ShimData_Win10(info.pShimData, szApphelp, 1, layers);
        }
    }
    else
    {
        ok(0, "Unable to get process info!\n");
    }

}