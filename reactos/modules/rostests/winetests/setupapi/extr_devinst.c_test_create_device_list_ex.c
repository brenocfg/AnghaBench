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
typedef  char WCHAR ;
typedef  scalar_t__ HDEVINFO ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ ERROR_INVALID_MACHINENAME ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_MACHINE_UNAVAILABLE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ SetupDiCreateDeviceInfoListExW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char*) ; 
 int SetupDiDestroyDeviceInfoList (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_create_device_list_ex(void)
{
    static const WCHAR machine[] = { 'd','u','m','m','y',0 };
    static const WCHAR empty[] = { 0 };
    static char notnull[] = "NotNull";
    HDEVINFO set;
    BOOL ret;

    SetLastError(0xdeadbeef);
    set = SetupDiCreateDeviceInfoListExW(NULL, NULL, NULL, notnull);
    ok(set == INVALID_HANDLE_VALUE, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Got unexpected error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    set = SetupDiCreateDeviceInfoListExW(NULL, NULL, machine, NULL);
    ok(set == INVALID_HANDLE_VALUE, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_MACHINENAME
            || GetLastError() == ERROR_MACHINE_UNAVAILABLE
            || GetLastError() == ERROR_CALL_NOT_IMPLEMENTED,
            "Got unexpected error %#x.\n", GetLastError());

    set = SetupDiCreateDeviceInfoListExW(NULL, NULL, NULL, NULL);
    ok(set != INVALID_HANDLE_VALUE, "Failed to create device list, error %#x.", GetLastError());

    ret = SetupDiDestroyDeviceInfoList(set);
    ok(ret, "Failed to destroy device list, error %#x.\n", GetLastError());

    set = SetupDiCreateDeviceInfoListExW(NULL, NULL, empty, NULL);
    ok(set != INVALID_HANDLE_VALUE, "Failed to create device list, error %#x.", GetLastError());

    ret = SetupDiDestroyDeviceInfoList(set);
    ok(ret, "Failed to destroy device list, error %#x.\n", GetLastError());
}