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
typedef  int /*<<< orphan*/  info ;
struct TYPE_3__ {int SizeOfImage; int /*<<< orphan*/ * lpBaseOfDll; } ;
typedef  TYPE_1__ MODULEINFO ;
typedef  int /*<<< orphan*/ * HMODULE ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/ * GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int GetModuleInformation (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/ * LoadLibraryA (char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * hBad ; 
 int /*<<< orphan*/ * hpQI ; 
 int /*<<< orphan*/ * hpQV ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  trace (char*,int) ; 

__attribute__((used)) static void test_GetModuleInformation(void)
{
    HMODULE hMod = GetModuleHandleA(NULL);
    DWORD *tmp, counter = 0;
    MODULEINFO info;
    DWORD ret;

    SetLastError(0xdeadbeef);
    GetModuleInformation(NULL, hMod, &info, sizeof(info));
    ok(GetLastError() == ERROR_INVALID_HANDLE, "expected error=ERROR_INVALID_HANDLE but got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    GetModuleInformation(hpQI, hMod, &info, sizeof(info));
    ok(GetLastError() == ERROR_ACCESS_DENIED, "expected error=ERROR_ACCESS_DENIED but got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    GetModuleInformation(hpQV, hBad, &info, sizeof(info));
    ok(GetLastError() == ERROR_INVALID_HANDLE, "expected error=ERROR_INVALID_HANDLE but got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    GetModuleInformation(hpQV, hMod, &info, sizeof(info)-1);
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "expected error=ERROR_INSUFFICIENT_BUFFER but got %d\n", GetLastError());

    ret = GetModuleInformation(hpQV, hMod, &info, sizeof(info));
    ok(ret == 1, "failed with %d\n", GetLastError());
    ok(info.lpBaseOfDll == hMod, "lpBaseOfDll=%p hMod=%p\n", info.lpBaseOfDll, hMod);

    hMod = LoadLibraryA("shell32.dll");
    ok(hMod != NULL, "Failed to load shell32.dll, error: %u\n", GetLastError());

    ret = GetModuleInformation(hpQV, hMod, &info, sizeof(info));
    ok(ret == 1, "failed with %d\n", GetLastError());
    info.SizeOfImage /= sizeof(DWORD);
    for (tmp = (DWORD *)hMod; info.SizeOfImage; info.SizeOfImage--)
        counter ^= *tmp++;
    trace("xor of shell32: %08x\n", counter);

    FreeLibrary(hMod);
}