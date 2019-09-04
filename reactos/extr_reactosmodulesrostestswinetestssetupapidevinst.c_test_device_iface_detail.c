#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  iface ;
typedef  int /*<<< orphan*/  device ;
struct TYPE_16__ {int member_0; } ;
struct TYPE_15__ {int cbSize; int DevicePath; } ;
struct TYPE_14__ {int member_0; int cbSize; int /*<<< orphan*/  ClassGuid; } ;
typedef  TYPE_1__ SP_DEVINFO_DATA ;
typedef  TYPE_2__ SP_DEVICE_INTERFACE_DETAIL_DATA_A ;
typedef  TYPE_3__ SP_DEVICE_INTERFACE_DATA ;
typedef  int /*<<< orphan*/ * HDEVINFO ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * DevicePath ; 
 int ERROR_INSUFFICIENT_BUFFER ; 
 int ERROR_INVALID_HANDLE ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_INVALID_USER_BUFFER ; 
 int FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetLastError () ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SP_DEVICE_INTERFACE_DETAIL_DATA_W ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int SetupDiCreateDeviceInfoA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * SetupDiCreateDeviceInfoList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SetupDiCreateDeviceInterfaceA (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  SetupDiDestroyDeviceInfoList (int /*<<< orphan*/ *) ; 
 int SetupDiGetDeviceInterfaceDetailA (int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*,int,int*,int /*<<< orphan*/ *) ; 
 int SetupDiGetDeviceInterfaceDetailW (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  guid ; 
 TYPE_2__* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcasecmp (char const*,int) ; 
 int strlen (char const*) ; 
 int wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_device_iface_detail(void)
{
    static const char path[] = "\\\\?\\root#legacy_bogus#0000#{6a55b5a4-3f65-11db-b704-0011955c2bdb}";
    SP_DEVICE_INTERFACE_DETAIL_DATA_A *detail;
    SP_DEVICE_INTERFACE_DATA iface = {sizeof(iface)};
    SP_DEVINFO_DATA device = {sizeof(device)};
    DWORD size = 0, expectedsize;
    HDEVINFO set;
    BOOL ret;

    SetLastError(0xdeadbeef);
    ret = SetupDiGetDeviceInterfaceDetailA(NULL, NULL, NULL, 0, NULL, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_HANDLE, "Got unexpected error %#x.\n", GetLastError());

    set = SetupDiCreateDeviceInfoList(&guid, NULL);
    ok(set != INVALID_HANDLE_VALUE, "Failed to create device list, error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiGetDeviceInterfaceDetailA(set, NULL, NULL, 0, NULL, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Got unexpected error %#x.\n", GetLastError());

    ret = SetupDiCreateDeviceInfoA(set, "ROOT\\LEGACY_BOGUS\\0000", &guid, NULL, NULL, 0, &device);
    ok(ret, "Failed to create device, error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiCreateDeviceInterfaceA(set, &device, &guid, NULL, 0, &iface);
    ok(ret, "Failed to create interface, error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiGetDeviceInterfaceDetailA(set, &iface, NULL, 0, NULL, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Got unexpected error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiGetDeviceInterfaceDetailA(set, &iface, NULL, 100, NULL, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_USER_BUFFER, "Got unexpected error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiGetDeviceInterfaceDetailA(set, &iface, NULL, 0, &size, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Got unexpected error %#x.\n", GetLastError());

    detail = heap_alloc(size);
    expectedsize = FIELD_OFFSET(SP_DEVICE_INTERFACE_DETAIL_DATA_W, DevicePath[strlen(path) + 1]);

    detail->cbSize = 0;
    SetLastError(0xdeadbeef);
    ret = SetupDiGetDeviceInterfaceDetailA(set, &iface, detail, size, &size, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_USER_BUFFER, "Got unexpected error %#x.\n", GetLastError());

    detail->cbSize = size;
    SetLastError(0xdeadbeef);
    ret = SetupDiGetDeviceInterfaceDetailA(set, &iface, detail, size, &size, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_USER_BUFFER, "Got unexpected error %#x.\n", GetLastError());

    detail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_A);
    SetLastError(0xdeadbeef);
    ret = SetupDiGetDeviceInterfaceDetailA(set, &iface, detail, size, &size, NULL);
    ok(ret, "Failed to get interface detail, error %#x.\n", GetLastError());
    ok(!strcasecmp(path, detail->DevicePath), "Got unexpected path %s.\n", detail->DevicePath);

    ret = SetupDiGetDeviceInterfaceDetailW(set, &iface, NULL, 0, &size, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Got unexpected error %#x.\n", GetLastError());
    ok(size == expectedsize, "Got unexpected size %d.\n", size);

    memset(&device, 0, sizeof(device));
    device.cbSize = sizeof(device);
    ret = SetupDiGetDeviceInterfaceDetailW(set, &iface, NULL, 0, &size, &device);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Got unexpected error %#x.\n", GetLastError());
    ok(IsEqualGUID(&device.ClassGuid, &guid), "Got unexpected class %s.\n", wine_dbgstr_guid(&device.ClassGuid));

    heap_free(detail);
    SetupDiDestroyDeviceInfoList(set);
}