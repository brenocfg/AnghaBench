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
typedef  char WCHAR ;
struct TYPE_3__ {int dwPageSize; } ;
typedef  TYPE_1__ SYSTEM_INFO ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int CSTR_LESS_THAN ; 
 int CompareStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetSystemInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  MEM_COMMIT ; 
 int /*<<< orphan*/  MEM_RELEASE ; 
 int /*<<< orphan*/  PAGE_NOACCESS ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 char* VirtualAlloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VirtualFree (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VirtualProtect (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_CompareStringW(void)
{
    WCHAR *str1, *str2;
    SYSTEM_INFO si;
    DWORD old_prot;
    BOOL success;
    char *buf;
    int ret;

    GetSystemInfo(&si);
    buf = VirtualAlloc(NULL, si.dwPageSize * 4, MEM_COMMIT, PAGE_READWRITE);
    ok(buf != NULL, "VirtualAlloc failed with %u\n", GetLastError());
    success = VirtualProtect(buf + si.dwPageSize, si.dwPageSize, PAGE_NOACCESS, &old_prot);
    ok(success, "VirtualProtect failed with %u\n", GetLastError());
    success = VirtualProtect(buf + 3 * si.dwPageSize, si.dwPageSize, PAGE_NOACCESS, &old_prot);
    ok(success, "VirtualProtect failed with %u\n", GetLastError());

    str1 = (WCHAR *)(buf + si.dwPageSize - sizeof(WCHAR));
    str2 = (WCHAR *)(buf + 3 * si.dwPageSize - sizeof(WCHAR));
    *str1 = 'A';
    *str2 = 'B';

    /* CompareStringW should abort on the first non-matching character */
    ret = CompareStringW(CP_ACP, 0, str1, 100, str2, 100);
    ok(ret == CSTR_LESS_THAN, "expected CSTR_LESS_THAN, got %d\n", ret);

    success = VirtualFree(buf, 0, MEM_RELEASE);
    ok(success, "VirtualFree failed with %u\n", GetLastError());
}