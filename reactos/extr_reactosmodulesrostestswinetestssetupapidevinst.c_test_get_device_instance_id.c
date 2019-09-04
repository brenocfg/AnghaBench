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
typedef  int /*<<< orphan*/  id ;
typedef  int /*<<< orphan*/  device ;
struct TYPE_4__ {int cbSize; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SP_DEVINFO_DATA ;
typedef  int /*<<< orphan*/ * HDEVINFO ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DICD_GENERATE_ID ; 
 char* ERROR_INSUFFICIENT_BUFFER ; 
 char* ERROR_INVALID_HANDLE ; 
 char* ERROR_INVALID_PARAMETER ; 
 char* GetLastError () ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int SetupDiCreateDeviceInfoA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * SetupDiCreateDeviceInfoList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupDiDestroyDeviceInfoList (int /*<<< orphan*/ *) ; 
 int SetupDiGetDeviceInstanceIdA (int /*<<< orphan*/ *,TYPE_1__*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  guid ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void test_get_device_instance_id(void)
{
    BOOL ret;
    HDEVINFO set;
    SP_DEVINFO_DATA device = {0};
    char id[200];
    DWORD size;

    SetLastError(0xdeadbeef);
    ret = SetupDiGetDeviceInstanceIdA(NULL, NULL, NULL, 0, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_HANDLE, "Got unexpected error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiGetDeviceInstanceIdA(NULL, &device, NULL, 0, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_HANDLE, "Got unexpected error %#x.\n", GetLastError());

    set = SetupDiCreateDeviceInfoList(&guid, NULL);
    ok(set != INVALID_HANDLE_VALUE, "Failed to create device list, error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiGetDeviceInstanceIdA(set, NULL, NULL, 0, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Got unexpected error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiGetDeviceInstanceIdA(set, &device, NULL, 0, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Got unexpected error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiGetDeviceInstanceIdA(set, &device, NULL, 0, &size);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Got unexpected error %#x.\n", GetLastError());

    device.cbSize = sizeof(device);
    SetLastError(0xdeadbeef);
    ret = SetupDiGetDeviceInstanceIdA(set, &device, NULL, 0, &size);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Got unexpected error %#x.\n", GetLastError());

    ret = SetupDiCreateDeviceInfoA(set, "Root\\LEGACY_BOGUS\\0000", &guid, NULL, NULL, 0, &device);
    ok(ret, "Failed to create device, error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiGetDeviceInstanceIdA(set, &device, NULL, 0, &size);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Got unexpected error %#x.\n", GetLastError());

    ret = SetupDiGetDeviceInstanceIdA(set, &device, id, sizeof(id), NULL);
    ok(ret, "Failed to get device id, error %#x.\n", GetLastError());
    ok(!strcmp(id, "ROOT\\LEGACY_BOGUS\\0000"), "Got unexpected id %s.\n", id);

    ret = SetupDiCreateDeviceInfoA(set, "LEGACY_BOGUS", &guid, NULL, NULL, DICD_GENERATE_ID, &device);
    ok(ret, "SetupDiCreateDeviceInfoA failed: %08x\n", GetLastError());

    ret = SetupDiGetDeviceInstanceIdA(set, &device, id, sizeof(id), NULL);
    ok(ret, "Failed to get device id, error %#x.\n", GetLastError());
    ok(!strcmp(id, "ROOT\\LEGACY_BOGUS\\0001"), "Got unexpected id %s.\n", id);

    SetupDiDestroyDeviceInfoList(set);
}