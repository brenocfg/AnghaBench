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
typedef  int /*<<< orphan*/  szModPath ;
typedef  int /*<<< orphan*/  szModBaseName ;
typedef  int /*<<< orphan*/ * HMODULE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetModuleBaseNameA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  GetModuleFileNameA (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * hBad ; 
 int /*<<< orphan*/ * hpQI ; 
 int /*<<< orphan*/ * hpQV ; 
 int /*<<< orphan*/  ok (int,char*,char*,...) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strrchr (char*,char) ; 

__attribute__((used)) static void test_GetModuleBaseName(void)
{
    HMODULE hMod = GetModuleHandleA(NULL);
    char szModPath[MAX_PATH], szModBaseName[MAX_PATH];
    DWORD ret;

    SetLastError(0xdeadbeef);
    GetModuleBaseNameA(NULL, hMod, szModBaseName, sizeof(szModBaseName));
    ok(GetLastError() == ERROR_INVALID_HANDLE, "expected error=ERROR_INVALID_HANDLE but got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    GetModuleBaseNameA(hpQI, hMod, szModBaseName, sizeof(szModBaseName));
    ok(GetLastError() == ERROR_ACCESS_DENIED, "expected error=ERROR_ACCESS_DENIED but got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    GetModuleBaseNameA(hpQV, hBad, szModBaseName, sizeof(szModBaseName));
    ok(GetLastError() == ERROR_INVALID_HANDLE, "expected error=ERROR_INVALID_HANDLE but got %d\n", GetLastError());

    ret = GetModuleBaseNameA(hpQV, NULL, szModBaseName, sizeof(szModBaseName));
    if(!ret)
        return;
    ok(ret == strlen(szModBaseName), "szModBaseName=\"%s\" ret=%d\n", szModBaseName, ret);
    GetModuleFileNameA(NULL, szModPath, sizeof(szModPath));
    ok(!strcmp(strrchr(szModPath, '\\') + 1, szModBaseName),
       "szModPath=\"%s\" szModBaseName=\"%s\"\n", szModPath, szModBaseName);
}