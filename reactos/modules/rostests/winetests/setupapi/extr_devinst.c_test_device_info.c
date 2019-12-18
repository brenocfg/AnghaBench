#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ret_device ;
typedef  int /*<<< orphan*/  id ;
typedef  int /*<<< orphan*/  device ;
struct TYPE_15__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; } ;
struct TYPE_17__ {int member_0; int member_1; int member_2; TYPE_1__ member_3; } ;
struct TYPE_16__ {int member_0; int cbSize; int /*<<< orphan*/  DevInst; int /*<<< orphan*/  ClassGuid; } ;
typedef  TYPE_2__ SP_DEVINFO_DATA ;
typedef  int /*<<< orphan*/ * HDEVINFO ;
typedef  TYPE_3__ GUID ;
typedef  int BOOL ;

/* Variables and functions */
 char* ERROR_CLASS_MISMATCH ; 
 char* ERROR_DEVINST_ALREADY_EXISTS ; 
 char* ERROR_INVALID_DEVINST_NAME ; 
 char* ERROR_INVALID_HANDLE ; 
 char* ERROR_INVALID_PARAMETER ; 
 char* ERROR_INVALID_USER_BUFFER ; 
 char* ERROR_NO_SUCH_DEVINST ; 
 TYPE_3__ const GUID_NULL ; 
 char* GetLastError () ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int IsEqualGUID (int /*<<< orphan*/ *,TYPE_3__ const*) ; 
 int MAX_DEVICE_ID_LEN ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int SetupDiCreateDeviceInfoA (int /*<<< orphan*/ *,char*,TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * SetupDiCreateDeviceInfoList (TYPE_3__ const*,int /*<<< orphan*/ *) ; 
 int SetupDiDeleteDeviceInfo (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SetupDiDestroyDeviceInfoList (int /*<<< orphan*/ *) ; 
 int SetupDiEnumDeviceInfo (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int SetupDiGetDeviceInstanceIdA (int /*<<< orphan*/ *,TYPE_2__*,char*,int,int /*<<< orphan*/ *) ; 
 int SetupDiRemoveDevice (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  check_device_info (int /*<<< orphan*/ *,int,TYPE_3__ const*,char*) ; 
 TYPE_3__ const guid ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_device_info(void)
{
    static const GUID deadbeef = {0xdeadbeef,0xdead,0xbeef,{0xde,0xad,0xbe,0xef,0xde,0xad,0xbe,0xef}};
    SP_DEVINFO_DATA device = {0}, ret_device = {sizeof(ret_device)};
    char id[MAX_DEVICE_ID_LEN + 2];
    HDEVINFO set;
    BOOL ret;

    SetLastError(0xdeadbeef);
    ret = SetupDiCreateDeviceInfoA(NULL, NULL, NULL, NULL, NULL, 0, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_DEVINST_NAME, "Got unexpected error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiCreateDeviceInfoA(NULL, "Root\\LEGACY_BOGUS\\0000", NULL, NULL, NULL, 0, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_HANDLE, "Got unexpected error %#x.\n", GetLastError());

    set = SetupDiCreateDeviceInfoList(&guid, NULL);
    ok(set != INVALID_HANDLE_VALUE, "Failed to create device info, error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiCreateDeviceInfoA(set, "Root\\LEGACY_BOGUS\\0000", NULL, NULL, NULL, 0, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Got unexpected error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiCreateDeviceInfoA(set, "Root\\LEGACY_BOGUS\\0000", &deadbeef, NULL, NULL, 0, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_CLASS_MISMATCH, "Got unexpected error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiCreateDeviceInfoA(set, "Root\\LEGACY_BOGUS\\0000", &GUID_NULL, NULL, NULL, 0, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_CLASS_MISMATCH, "Got unexpected error %#x.\n", GetLastError());

    ret = SetupDiCreateDeviceInfoA(set, "Root\\LEGACY_BOGUS\\0000", &guid, NULL, NULL, 0, NULL);
    ok(ret, "Failed to create device, error %#x.\n", GetLastError());

    check_device_info(set, 0, &guid, "ROOT\\LEGACY_BOGUS\\0000");
    check_device_info(set, 1, &guid, NULL);

    SetLastError(0xdeadbeef);
    ret = SetupDiCreateDeviceInfoA(set, "Root\\LEGACY_BOGUS\\0000", &guid, NULL, NULL, 0, &device);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_DEVINST_ALREADY_EXISTS, "Got unexpected error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiCreateDeviceInfoA(set, "Root\\LEGACY_BOGUS\\0001", &guid, NULL, NULL, 0, &device);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_USER_BUFFER, "Got unexpected error %#x.\n", GetLastError());

    check_device_info(set, 0, &guid, "ROOT\\LEGACY_BOGUS\\0000");
    check_device_info(set, 1, &guid, "ROOT\\LEGACY_BOGUS\\0001");
    check_device_info(set, 2, &guid, NULL);

    device.cbSize = sizeof(device);
    ret = SetupDiCreateDeviceInfoA(set, "Root\\LEGACY_BOGUS\\0002", &guid, NULL, NULL, 0, &device);
    ok(ret, "Got unexpected error %#x.\n", GetLastError());
    ok(IsEqualGUID(&device.ClassGuid, &guid), "Got unexpected class %s.\n",
            wine_dbgstr_guid(&device.ClassGuid));
    ret = SetupDiGetDeviceInstanceIdA(set, &device, id, sizeof(id), NULL);
    ok(ret, "Got unexpected error %#x.\n", GetLastError());
    ok(!strcmp(id, "ROOT\\LEGACY_BOGUS\\0002"), "Got unexpected id %s.\n", id);

    check_device_info(set, 0, &guid, "ROOT\\LEGACY_BOGUS\\0000");
    check_device_info(set, 1, &guid, "ROOT\\LEGACY_BOGUS\\0001");
    check_device_info(set, 2, &guid, "ROOT\\LEGACY_BOGUS\\0002");
    check_device_info(set, 3, &guid, NULL);

    ret = SetupDiEnumDeviceInfo(set, 0, &ret_device);
    ok(ret, "Failed to enumerate devices, error %#x.\n", GetLastError());
    ret = SetupDiDeleteDeviceInfo(set, &ret_device);
    ok(ret, "Failed to delete device, error %#x.\n", GetLastError());

    check_device_info(set, 0, &guid, "ROOT\\LEGACY_BOGUS\\0001");
    check_device_info(set, 1, &guid, "ROOT\\LEGACY_BOGUS\\0002");
    check_device_info(set, 2, &guid, NULL);

    ret = SetupDiRemoveDevice(set, &device);
    ok(ret, "Got unexpected error %#x.\n", GetLastError());

    check_device_info(set, 0, &guid, "ROOT\\LEGACY_BOGUS\\0001");

    ret = SetupDiEnumDeviceInfo(set, 1, &ret_device);
    ok(ret, "Got unexpected error %#x.\n", GetLastError());
    ok(IsEqualGUID(&ret_device.ClassGuid, &guid), "Got unexpected class %s.\n",
            wine_dbgstr_guid(&ret_device.ClassGuid));
    ret = SetupDiGetDeviceInstanceIdA(set, &ret_device, id, sizeof(id), NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_NO_SUCH_DEVINST, "Got unexpected error %#x.\n", GetLastError());
    ok(ret_device.DevInst == device.DevInst, "Expected device node %#x, got %#x.\n",
            device.DevInst, ret_device.DevInst);

    check_device_info(set, 2, &guid, NULL);

    SetupDiDestroyDeviceInfoList(set);

    set = SetupDiCreateDeviceInfoList(NULL, NULL);
    ok(set != INVALID_HANDLE_VALUE, "Failed to create device info, error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiCreateDeviceInfoA(set, "Root\\LEGACY_BOGUS\\0000", NULL, NULL, NULL, 0, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Got unexpected error %#x.\n", GetLastError());

    ret = SetupDiCreateDeviceInfoA(set, "Root\\LEGACY_BOGUS\\deadbeef", &deadbeef, NULL, NULL, 0, NULL);
    ok(ret, "Failed to create device, error %#x.\n", GetLastError());

    ret = SetupDiCreateDeviceInfoA(set, "Root\\LEGACY_BOGUS\\null", &GUID_NULL, NULL, NULL, 0, NULL);
    ok(ret, "Failed to create device, error %#x.\n", GetLastError());

    ret = SetupDiCreateDeviceInfoA(set, "Root\\LEGACY_BOGUS\\testguid", &guid, NULL, NULL, 0, NULL);
    ok(ret, "Failed to create device, error %#x.\n", GetLastError());

    check_device_info(set, 0, &deadbeef, "ROOT\\LEGACY_BOGUS\\deadbeef");
    check_device_info(set, 1, &GUID_NULL, "ROOT\\LEGACY_BOGUS\\null");
    check_device_info(set, 2, &guid, "ROOT\\LEGACY_BOGUS\\testguid");
    check_device_info(set, 3, NULL, NULL);

    memset(id, 'x', sizeof(id));
    memcpy(id, "Root\\LEGACY_BOGUS\\", strlen("Root\\LEGACY_BOGUS\\"));
    id[MAX_DEVICE_ID_LEN + 1] = 0;
    SetLastError(0xdeadbeef);
    ret = SetupDiCreateDeviceInfoA(set, id, &guid, NULL, NULL, 0, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_DEVINST_NAME, "Got unexpected error %#x.\n", GetLastError());

    id[MAX_DEVICE_ID_LEN] = 0;
    SetLastError(0xdeadbeef);
    ret = SetupDiCreateDeviceInfoA(set, id, &guid, NULL, NULL, 0, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_DEVINST_NAME, "Got unexpected error %#x.\n", GetLastError());

    id[MAX_DEVICE_ID_LEN - 1] = 0;
    ret = SetupDiCreateDeviceInfoA(set, id, &guid, NULL, NULL, 0, NULL);
    ok(ret, "Failed to create device, error %#x.\n", GetLastError());

    SetupDiDestroyDeviceInfoList(set);
}