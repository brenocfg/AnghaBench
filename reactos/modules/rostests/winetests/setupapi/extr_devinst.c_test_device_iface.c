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
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_16__ {int member_0; scalar_t__ Flags; int /*<<< orphan*/  InterfaceClassGuid; } ;
struct TYPE_15__ {int cbSize; scalar_t__ DevicePath; } ;
struct TYPE_14__ {int cbSize; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SP_DEVINFO_DATA ;
typedef  TYPE_2__ SP_DEVICE_INTERFACE_DETAIL_DATA_A ;
typedef  TYPE_3__ SP_DEVICE_INTERFACE_DATA ;
typedef  int /*<<< orphan*/ * HDEVINFO ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_INVALID_USER_BUFFER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPINT_REMOVED ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int SetupDiCreateDeviceInfoA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * SetupDiCreateDeviceInfoList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SetupDiCreateDeviceInterfaceA (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int SetupDiDeleteDeviceInterfaceData (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int SetupDiDestroyDeviceInfoList (int /*<<< orphan*/ *) ; 
 int SetupDiEnumDeviceInterfaces (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int SetupDiGetDeviceInterfaceDetailA (int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SetupDiRemoveDeviceInterface (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  check_device_iface (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  guid ; 
 int /*<<< orphan*/  guid2 ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcasecmp (scalar_t__,char*) ; 
 scalar_t__ wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_device_iface(void)
{
    char buffer[200];
    SP_DEVICE_INTERFACE_DETAIL_DATA_A *detail = (SP_DEVICE_INTERFACE_DETAIL_DATA_A *)buffer;
    SP_DEVICE_INTERFACE_DATA iface = {sizeof(iface)};
    SP_DEVINFO_DATA device = {0};
    BOOL ret;
    HDEVINFO set;

    detail->cbSize = sizeof(*detail);

    SetLastError(0xdeadbeef);
    ret = SetupDiCreateDeviceInterfaceA(NULL, NULL, NULL, NULL, 0, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_HANDLE, "Got unexpected error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiCreateDeviceInterfaceA(NULL, NULL, &guid, NULL, 0, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_HANDLE, "Got unexpected error %#x.\n", GetLastError());

    set = SetupDiCreateDeviceInfoList(&guid, NULL);
    ok(set != INVALID_HANDLE_VALUE, "Failed to create device list, error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiCreateDeviceInterfaceA(set, NULL, NULL, NULL, 0, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Got unexpected error %#x.\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupDiCreateDeviceInterfaceA(set, &device, NULL, NULL, 0, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Got unexpected error %#x.\n", GetLastError());

    device.cbSize = sizeof(device);
    ret = SetupDiCreateDeviceInfoA(set, "ROOT\\LEGACY_BOGUS\\0000", &guid, NULL, NULL, 0, &device);
    ok(ret, "Failed to create device, error %#x.\n", GetLastError());

    check_device_iface(set, &device, &guid, 0, 0, NULL);

    SetLastError(0xdeadbeef);
    ret = SetupDiCreateDeviceInterfaceA(set, &device, NULL, NULL, 0, NULL);
    ok(!ret, "Expected failure.\n");
    ok(GetLastError() == ERROR_INVALID_USER_BUFFER, "Got unexpected error %#x.\n", GetLastError());

    ret = SetupDiCreateDeviceInterfaceA(set, &device, &guid, NULL, 0, NULL);
    ok(ret, "Failed to create interface, error %#x.\n", GetLastError());

    check_device_iface(set, &device, &guid, 0, 0, "\\\\?\\ROOT#LEGACY_BOGUS#0000#{6A55B5A4-3F65-11DB-B704-0011955C2BDB}");
    check_device_iface(set, &device, &guid, 1, 0, NULL);

    /* Creating the same interface a second time succeeds */
    ret = SetupDiCreateDeviceInterfaceA(set, &device, &guid, NULL, 0, NULL);
    ok(ret, "Failed to create interface, error %#x.\n", GetLastError());

    check_device_iface(set, &device, &guid, 0, 0, "\\\\?\\ROOT#LEGACY_BOGUS#0000#{6A55B5A4-3F65-11DB-B704-0011955C2BDB}");
    check_device_iface(set, &device, &guid, 1, 0, NULL);

    ret = SetupDiCreateDeviceInterfaceA(set, &device, &guid, "Oogah", 0, NULL);
    ok(ret, "Failed to create interface, error %#x.\n", GetLastError());

    check_device_iface(set, &device, &guid, 0, 0, "\\\\?\\ROOT#LEGACY_BOGUS#0000#{6A55B5A4-3F65-11DB-B704-0011955C2BDB}");
    check_device_iface(set, &device, &guid, 1, 0, "\\\\?\\ROOT#LEGACY_BOGUS#0000#{6A55B5A4-3F65-11DB-B704-0011955C2BDB}\\Oogah");
    check_device_iface(set, &device, &guid, 2, 0, NULL);

    ret = SetupDiCreateDeviceInterfaceA(set, &device, &guid, "test", 0, &iface);
    ok(ret, "Failed to create interface, error %#x.\n", GetLastError());
    ok(IsEqualGUID(&iface.InterfaceClassGuid, &guid), "Got unexpected class %s.\n",
            wine_dbgstr_guid(&iface.InterfaceClassGuid));
    ok(iface.Flags == 0, "Got unexpected flags %#x.\n", iface.Flags);
    ret = SetupDiGetDeviceInterfaceDetailA(set, &iface, detail, sizeof(buffer), NULL, NULL);
    ok(ret, "Failed to get interface detail, error %#x.\n", GetLastError());
    ok(!strcasecmp(detail->DevicePath, "\\\\?\\ROOT#LEGACY_BOGUS#0000#{6A55B5A4-3F65-11DB-B704-0011955C2BDB}\\test"),
            "Got unexpected path %s.\n", detail->DevicePath);

    check_device_iface(set, &device, &guid, 0, 0, "\\\\?\\ROOT#LEGACY_BOGUS#0000#{6A55B5A4-3F65-11DB-B704-0011955C2BDB}");
    check_device_iface(set, &device, &guid, 1, 0, "\\\\?\\ROOT#LEGACY_BOGUS#0000#{6A55B5A4-3F65-11DB-B704-0011955C2BDB}\\Oogah");
    check_device_iface(set, &device, &guid, 2, 0, "\\\\?\\ROOT#LEGACY_BOGUS#0000#{6A55B5A4-3F65-11DB-B704-0011955C2BDB}\\test");
    check_device_iface(set, &device, &guid, 3, 0, NULL);

    ret = SetupDiCreateDeviceInterfaceA(set, &device, &guid2, NULL, 0, NULL);
    ok(ret, "Failed to create interface, error %#x.\n", GetLastError());

    check_device_iface(set, &device, &guid2, 0, 0, "\\\\?\\ROOT#LEGACY_BOGUS#0000#{6A55B5A5-3F65-11DB-B704-0011955C2BDB}");
    check_device_iface(set, &device, &guid2, 1, 0, NULL);

    ret = SetupDiEnumDeviceInterfaces(set, &device, &guid2, 0, &iface);
    ok(ret, "Failed to enumerate interfaces, error %#x.\n", GetLastError());
    ret = SetupDiRemoveDeviceInterface(set, &iface);
    ok(ret, "Failed to remove interface, error %#x.\n", GetLastError());

    check_device_iface(set, &device, &guid2, 0, SPINT_REMOVED, "\\\\?\\ROOT#LEGACY_BOGUS#0000#{6A55B5A5-3F65-11DB-B704-0011955C2BDB}");
    check_device_iface(set, &device, &guid2, 1, 0, NULL);

    ret = SetupDiEnumDeviceInterfaces(set, &device, &guid, 0, &iface);
    ok(ret, "Failed to enumerate interfaces, error %#x.\n", GetLastError());
    ret = SetupDiDeleteDeviceInterfaceData(set, &iface);
    ok(ret, "Failed to delete interface, error %#x.\n", GetLastError());

    check_device_iface(set, &device, &guid, 0, 0, "\\\\?\\ROOT#LEGACY_BOGUS#0000#{6A55B5A4-3F65-11DB-B704-0011955C2BDB}\\Oogah");
    check_device_iface(set, &device, &guid, 1, 0, "\\\\?\\ROOT#LEGACY_BOGUS#0000#{6A55B5A4-3F65-11DB-B704-0011955C2BDB}\\test");
    check_device_iface(set, &device, &guid, 2, 0, NULL);

    ret = SetupDiDestroyDeviceInfoList(set);
    ok(ret, "Failed to destroy device list, error %#x.\n", GetLastError());
}