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
typedef  int /*<<< orphan*/  wcx ;
struct TYPE_3__ {int cbSize; int /*<<< orphan*/ * lpfnWndProc; } ;
typedef  TYPE_1__ WNDCLASSEXA ;
typedef  int /*<<< orphan*/  WNDCLASSA ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ERROR_CALL_NOT_IMPLEMENTED ; 
 int ERROR_NOACCESS ; 
 int /*<<< orphan*/  GetClassInfoA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetClassInfoExA (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  GetClassInfoExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetClassInfoW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_GetClassInfo(void)
{
    static const WCHAR staticW[] = {'s','t','a','t','i','c',0};
    WNDCLASSA wc;
    WNDCLASSEXA wcx;
    BOOL ret;

    SetLastError(0xdeadbeef);
    ret = GetClassInfoA(0, "static", &wc);
    ok(ret, "GetClassInfoA() error %d\n", GetLastError());

if (0) { /* crashes under XP */
    SetLastError(0xdeadbeef);
    ret = GetClassInfoA(0, "static", NULL);
    ok(ret, "GetClassInfoA() error %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = GetClassInfoW(0, staticW, NULL);
    ok(ret, "GetClassInfoW() error %d\n", GetLastError());
}

    wcx.cbSize = sizeof(wcx);
    SetLastError(0xdeadbeef);
    ret = GetClassInfoExA(0, "static", &wcx);
    ok(ret, "GetClassInfoExA() error %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = GetClassInfoExA(0, "static", NULL);
    ok(!ret, "GetClassInfoExA() should fail\n");
    ok(GetLastError() == ERROR_NOACCESS ||
       broken(GetLastError() == 0xdeadbeef), /* win9x */
       "expected ERROR_NOACCESS, got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = GetClassInfoExW(0, staticW, NULL);
    ok(!ret, "GetClassInfoExW() should fail\n");
    ok(GetLastError() == ERROR_NOACCESS ||
       broken(GetLastError() == 0xdeadbeef) /* NT4 */ ||
       broken(GetLastError() == ERROR_CALL_NOT_IMPLEMENTED), /* win9x */
       "expected ERROR_NOACCESS, got %d\n", GetLastError());

    wcx.cbSize = 0;
    wcx.lpfnWndProc = NULL;
    SetLastError(0xdeadbeef);
    ret = GetClassInfoExA(0, "static", &wcx);
    ok(ret, "GetClassInfoExA() error %d\n", GetLastError());
    ok(wcx.cbSize == 0, "expected 0, got %u\n", wcx.cbSize);
    ok(wcx.lpfnWndProc != NULL, "got null proc\n");

    wcx.cbSize = sizeof(wcx) - 1;
    wcx.lpfnWndProc = NULL;
    SetLastError(0xdeadbeef);
    ret = GetClassInfoExA(0, "static", &wcx);
    ok(ret, "GetClassInfoExA() error %d\n", GetLastError());
    ok(wcx.cbSize == sizeof(wcx) - 1, "expected sizeof(wcx)-1, got %u\n", wcx.cbSize);
    ok(wcx.lpfnWndProc != NULL, "got null proc\n");

    wcx.cbSize = sizeof(wcx) + 1;
    wcx.lpfnWndProc = NULL;
    SetLastError(0xdeadbeef);
    ret = GetClassInfoExA(0, "static", &wcx);
    ok(ret, "GetClassInfoExA() error %d\n", GetLastError());
    ok(wcx.cbSize == sizeof(wcx) + 1, "expected sizeof(wcx)+1, got %u\n", wcx.cbSize);
    ok(wcx.lpfnWndProc != NULL, "got null proc\n");
}