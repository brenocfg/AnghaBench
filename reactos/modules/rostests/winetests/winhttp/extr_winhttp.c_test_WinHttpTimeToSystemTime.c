#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_5__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int /*<<< orphan*/  member_7; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_SUCCESS ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  WinHttpTimeToSystemTime (char const*,TYPE_1__*) ; 
 scalar_t__ broken (int) ; 
 scalar_t__ memcmp (TYPE_1__*,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_WinHttpTimeToSystemTime(void)
{
    BOOL ret;
    SYSTEMTIME time;
    static const SYSTEMTIME expected_time = {2008, 7, 1, 28, 10, 5, 52, 0};
    static const WCHAR time_string1[] =
        {'M','o','n',',',' ','2','8',' ','J','u','l',' ','2','0','0','8',' ',
         +          '1','0',':','0','5',':','5','2',' ','G','M','T','\n',0};
    static const WCHAR time_string2[] =
        {' ','m','o','n',' ','2','8',' ','j','u','l',' ','2','0','0','8',' ',
         '1','0',' ','0','5',' ','5','2','\n',0};
    DWORD err;

    SetLastError(0xdeadbeef);
    ret = WinHttpTimeToSystemTime(time_string1, NULL);
    err = GetLastError();
    ok(!ret, "WinHttpTimeToSystemTime succeeded\n");
    ok(err == ERROR_INVALID_PARAMETER, "got %u\n", err);

    SetLastError(0xdeadbeef);
    ret = WinHttpTimeToSystemTime(NULL, &time);
    err = GetLastError();
    ok(!ret, "WinHttpTimeToSystemTime succeeded\n");
    ok(err == ERROR_INVALID_PARAMETER, "got %u\n", err);

    SetLastError(0xdeadbeef);
    ret = WinHttpTimeToSystemTime(time_string1, &time);
    err = GetLastError();
    ok(ret, "WinHttpTimeToSystemTime failed: %u\n", err);
    ok(err == ERROR_SUCCESS || broken(err == 0xdeadbeef) /* < win7 */, "got %u\n", err);
    ok(memcmp(&time, &expected_time, sizeof(SYSTEMTIME)) == 0,
        "Returned SYSTEMTIME structure did not match expected SYSTEMTIME structure.\n");

    SetLastError(0xdeadbeef);
    ret = WinHttpTimeToSystemTime(time_string2, &time);
    err = GetLastError();
    ok(ret, "WinHttpTimeToSystemTime failed: %u\n", err);
    ok(err == ERROR_SUCCESS || broken(err == 0xdeadbeef) /* < win7 */, "got %u\n", err);
    ok(memcmp(&time, &expected_time, sizeof(SYSTEMTIME)) == 0,
        "Returned SYSTEMTIME structure did not match expected SYSTEMTIME structure.\n");
}