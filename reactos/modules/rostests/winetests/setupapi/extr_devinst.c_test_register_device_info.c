#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device ;
struct TYPE_7__ {int cbSize; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SP_DEVINFO_DATA ;
typedef  int /*<<< orphan*/ * HDEVINFO ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int SetupDiCreateDeviceInfoA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * SetupDiCreateDeviceInfoList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SetupDiDeleteDeviceInfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  SetupDiDestroyDeviceInfoList (int /*<<< orphan*/ *) ; 
 scalar_t__ SetupDiEnumDeviceInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * SetupDiGetClassDevsA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SetupDiRegisterDeviceInfo (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SetupDiRemoveDevice (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  check_device_info (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  guid ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_register_device_info(void)
{
    SP_DEVINFO_DATA device = {0};
    BOOL ret;
    HDEVINFO set;
    int i = 0;

    SetLastError(0xdeadbeef);
    ret = SetupDiRegisterDeviceInfo(NULL, NULL, 0, NULL, NULL, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_HANDLE, "Got unexpected error %#x.\n", GetLastError());

    set = SetupDiCreateDeviceInfoList(&guid, NULL);
    ok(set != INVALID_HANDLE_VALUE, "Failed to create device list, error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiRegisterDeviceInfo(set, NULL, 0, NULL, NULL, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Got unexpected error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiRegisterDeviceInfo(set, &device, 0, NULL, NULL, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Got unexpected error %#x.\n", GetLastError());

    device.cbSize = sizeof(device);
    SetLastError(0xdeadbeef);
    ret = SetupDiRegisterDeviceInfo(set, &device, 0, NULL, NULL, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Got unexpected error %#x.\n", GetLastError());

    ret = SetupDiCreateDeviceInfoA(set, "Root\\LEGACY_BOGUS\\0000", &guid, NULL, NULL, 0, &device);
    ok(ret, "Failed to create device, error %#x.\n", GetLastError());
    ret = SetupDiRegisterDeviceInfo(set, &device, 0, NULL, NULL, NULL);
    ok(ret, "Failed to register device, error %#x.\n", GetLastError());

    ret = SetupDiCreateDeviceInfoA(set, "Root\\LEGACY_BOGUS\\0001", &guid, NULL, NULL, 0, &device);
    ok(ret, "Failed to create device, error %#x.\n", GetLastError());
    ret = SetupDiRegisterDeviceInfo(set, &device, 0, NULL, NULL, NULL);
    ok(ret, "Failed to register device, error %#x.\n", GetLastError());
    ret = SetupDiRemoveDevice(set, &device);
    ok(ret, "Failed to remove device, error %#x.\n", GetLastError());

    ret = SetupDiCreateDeviceInfoA(set, "Root\\LEGACY_BOGUS\\0002", &guid, NULL, NULL, 0, &device);
    ok(ret, "Failed to create device, error %#x.\n", GetLastError());
    ret = SetupDiRegisterDeviceInfo(set, &device, 0, NULL, NULL, NULL);
    ok(ret, "Failed to register device, error %#x.\n", GetLastError());
    ret = SetupDiDeleteDeviceInfo(set, &device);
    ok(ret, "Failed to remove device, error %#x.\n", GetLastError());

    ret = SetupDiCreateDeviceInfoA(set, "Root\\LEGACY_BOGUS\\0003", &guid, NULL, NULL, 0, &device);
    ok(ret, "Failed to create device, error %#x.\n", GetLastError());

    SetupDiDestroyDeviceInfoList(set);

    set = SetupDiGetClassDevsA(&guid, NULL, NULL, 0);
    ok(set != INVALID_HANDLE_VALUE, "Failed to create device list, error %#x.\n", GetLastError());

    check_device_info(set, 0, &guid, "Root\\LEGACY_BOGUS\\0000");
    check_device_info(set, 1, &guid, "Root\\LEGACY_BOGUS\\0002");
    check_device_info(set, 2, &guid, NULL);

    while (SetupDiEnumDeviceInfo(set, i++, &device))
    {
        ret = SetupDiRemoveDevice(set, &device);
        ok(ret, "Failed to remove device, error %#x.\n", GetLastError());
    }

    SetupDiDestroyDeviceInfoList(set);
}