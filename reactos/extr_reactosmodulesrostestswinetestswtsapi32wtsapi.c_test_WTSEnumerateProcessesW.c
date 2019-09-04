#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  pProcessName; } ;
typedef  TYPE_1__* PWTS_PROCESS_INFOW ;
typedef  size_t DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 int FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetModuleFileNameW (int /*<<< orphan*/ *,char*,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int WTSEnumerateProcessesW (int /*<<< orphan*/ ,int,int,TYPE_1__**,size_t*) ; 
 int /*<<< orphan*/  WTSFreeMemory (TYPE_1__*) ; 
 int /*<<< orphan*/  WTS_CURRENT_SERVER_HANDLE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  lstrcmpW (char*,int /*<<< orphan*/ ) ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_WTSEnumerateProcessesW(void)
{
    BOOL found = FALSE, ret;
    DWORD count, i;
    PWTS_PROCESS_INFOW info;
    WCHAR *pname, nameW[MAX_PATH];

    GetModuleFileNameW(NULL, nameW, MAX_PATH);
    for (pname = nameW + lstrlenW(nameW); pname > nameW; pname--)
    {
        if(*pname == '/' || *pname == '\\')
        {
            pname++;
            break;
        }
    }

    info = NULL;
    SetLastError(0xdeadbeef);
    ret = WTSEnumerateProcessesW(WTS_CURRENT_SERVER_HANDLE, 1, 1, &info, &count);
    ok(!ret, "expected WTSEnumerateProcessesW to fail\n");
    ok(GetLastError()== ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER got: %d\n", GetLastError());
    if (info) WTSFreeMemory(info);

    info = NULL;
    SetLastError(0xdeadbeef);
    ret = WTSEnumerateProcessesW(WTS_CURRENT_SERVER_HANDLE, 0, 0, &info, &count);
    ok(!ret, "expected WTSEnumerateProcessesW to fail\n");
    ok(GetLastError()== ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER got: %d\n", GetLastError());
    if (info) WTSFreeMemory(info);

    info = NULL;
    SetLastError(0xdeadbeef);
    ret = WTSEnumerateProcessesW(WTS_CURRENT_SERVER_HANDLE, 0, 2, &info, &count);
    ok(!ret, "expected WTSEnumerateProcessesW to fail\n");
    ok(GetLastError()== ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER got: %d\n", GetLastError());
    if (info) WTSFreeMemory(info);

    SetLastError(0xdeadbeef);
    ret = WTSEnumerateProcessesW(WTS_CURRENT_SERVER_HANDLE, 0, 1, NULL, &count);
    ok(!ret, "expected WTSEnumerateProcessesW to fail\n");
    ok(GetLastError()== ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER got: %d\n", GetLastError());

    info = NULL;
    SetLastError(0xdeadbeef);
    ret = WTSEnumerateProcessesW(WTS_CURRENT_SERVER_HANDLE, 0, 1, &info, NULL);
    ok(!ret, "expected WTSEnumerateProcessesW to fail\n");
    ok(GetLastError()== ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER got: %d\n", GetLastError());
    if (info) WTSFreeMemory(info);

    count = 0;
    info = NULL;
    SetLastError(0xdeadbeef);
    ret = WTSEnumerateProcessesW(WTS_CURRENT_SERVER_HANDLE, 0, 1, &info, &count);
    ok(ret || broken(!ret), /* fails on Win2K with error ERROR_APP_WRONG_OS */
        "expected WTSEnumerateProcessesW to succeed; failed with %d\n", GetLastError());
    for(i = 0; ret && i < count; i++)
    {
        found = found || !lstrcmpW(pname, info[i].pProcessName);
    }
    ok(found || broken(!ret), "process name %s not found\n", wine_dbgstr_w(pname));
    if (info) WTSFreeMemory(info);
}