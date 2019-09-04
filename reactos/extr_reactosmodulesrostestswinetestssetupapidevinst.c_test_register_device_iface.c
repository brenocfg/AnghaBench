#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ret_iface ;
typedef  int /*<<< orphan*/  iface ;
typedef  int /*<<< orphan*/  device ;
typedef  char WCHAR ;
struct TYPE_13__ {int member_0; } ;
struct TYPE_12__ {int member_0; } ;
typedef  TYPE_1__ SP_DEVINFO_DATA ;
typedef  TYPE_2__ SP_DEVICE_INTERFACE_DATA ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ HDEVINFO ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DIGCF_ALLCLASSES ; 
 int /*<<< orphan*/  DIGCF_DEVICEINTERFACE ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int SetupDiCreateDeviceInfoA (scalar_t__,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int SetupDiCreateDeviceInterfaceA (scalar_t__,TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int SetupDiDeleteDeviceInterfaceData (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  SetupDiDestroyDeviceInfoList (scalar_t__) ; 
 int SetupDiEnumDeviceInterfaces (scalar_t__,TYPE_1__*,int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 scalar_t__ SetupDiGetClassDevsA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SetupDiRegisterDeviceInfo (scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SetupDiRemoveDevice (scalar_t__,TYPE_1__*) ; 
 int SetupDiRemoveDeviceInterface (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  check_device_iface (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  guid ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_register_device_iface(void)
{
    static const WCHAR bogus[] = {'S','y','s','t','e','m','\\',
     'C','u','r','r','e','n','t','C','o','n','t','r','o','l','S','e','t','\\',
     'E','n','u','m','\\','R','o','o','t','\\',
     'L','E','G','A','C','Y','_','B','O','G','U','S',0};
    SP_DEVICE_INTERFACE_DATA iface = {sizeof(iface)}, ret_iface = {sizeof(ret_iface)};
    SP_DEVINFO_DATA device = {sizeof(device)};
    HDEVINFO set, set2;
    BOOL ret;
    HKEY key;
    LONG res;

    set = SetupDiGetClassDevsA(&guid, NULL, 0, DIGCF_ALLCLASSES);
    ok(set != INVALID_HANDLE_VALUE, "Failed to create device list, error %#x.\n", GetLastError());

    res = RegOpenKeyW(HKEY_LOCAL_MACHINE, bogus, &key);
    ok(res == ERROR_FILE_NOT_FOUND, "Key should not exist.\n");

    ret = SetupDiCreateDeviceInfoA(set, "Root\\LEGACY_BOGUS\\0000", &guid, NULL, NULL, 0, &device);
    ok(ret, "Failed to create device, error %#x.\n", GetLastError());
    ret = SetupDiCreateDeviceInterfaceA(set, &device, &guid, NULL, 0, &iface);
    ok(ret, "Failed to create interface, error %#x.\n", GetLastError());
    ret = SetupDiCreateDeviceInterfaceA(set, &device, &guid, "removed", 0, &iface);
    ok(ret, "Failed to create interface, error %#x.\n", GetLastError());
    ret = SetupDiCreateDeviceInterfaceA(set, &device, &guid, "deleted", 0, &iface);
    ok(ret, "Failed to create interface, error %#x.\n", GetLastError());
    ret = SetupDiRegisterDeviceInfo(set, &device, 0, NULL, NULL, NULL);
    ok(ret, "Failed to register device, error %#x.\n", GetLastError());

    ret = SetupDiEnumDeviceInterfaces(set, &device, &guid, 1, &iface);
    ok(ret, "Failed to enumerate interfaces, error %#x.\n", GetLastError());
    ret = SetupDiRemoveDeviceInterface(set, &iface);
    ok(ret, "Failed to delete interface, error %#x.\n", GetLastError());
    ret = SetupDiEnumDeviceInterfaces(set, &device, &guid, 2, &iface);
    ok(ret, "Failed to enumerate interfaces, error %#x.\n", GetLastError());
    ret = SetupDiDeleteDeviceInterfaceData(set, &iface);
    ok(ret, "Failed to delete interface, error %#x.\n", GetLastError());

    set2 = SetupDiGetClassDevsA(&guid, NULL, 0, DIGCF_DEVICEINTERFACE);
    ok(set2 != INVALID_HANDLE_VALUE, "Failed to create device list, error %#x.\n", GetLastError());

    check_device_iface(set2, NULL, &guid, 0, 0, "\\\\?\\root#legacy_bogus#0000#{6a55b5a4-3f65-11db-b704-0011955c2bdb}");
    check_device_iface(set2, NULL, &guid, 1, 0, "\\\\?\\root#legacy_bogus#0000#{6a55b5a4-3f65-11db-b704-0011955c2bdb}\\deleted");
    check_device_iface(set2, NULL, &guid, 2, 0, NULL);

    ret = SetupDiRemoveDevice(set, &device);
    ok(ret, "Failed to remove device, error %#x.\n", GetLastError());

    SetupDiDestroyDeviceInfoList(set);
    SetupDiDestroyDeviceInfoList(set2);
}