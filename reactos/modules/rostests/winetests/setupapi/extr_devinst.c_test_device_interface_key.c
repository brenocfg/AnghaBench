#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  iface ;
typedef  int /*<<< orphan*/  devinfo ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_11__ {int member_0; } ;
struct TYPE_10__ {int member_0; } ;
typedef  TYPE_1__ SP_DEVINFO_DATA ;
typedef  TYPE_2__ SP_DEVICE_INTERFACE_DATA ;
typedef  int LONG ;
typedef  scalar_t__ HKEY ;
typedef  scalar_t__ HDEVINFO ;

/* Variables and functions */
 int /*<<< orphan*/  DIGCF_ALLCLASSES ; 
 int ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ HKEY_LOCAL_MACHINE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (scalar_t__) ; 
 int RegOpenKeyA (scalar_t__,char const*,scalar_t__*) ; 
 int RegQueryValueA (scalar_t__,int /*<<< orphan*/ *,char*,int*) ; 
 int RegSetValueA (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int SetupDiCreateDeviceInfoA (scalar_t__,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int SetupDiCreateDeviceInterfaceA (scalar_t__,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ SetupDiCreateDeviceInterfaceRegKeyA (scalar_t__,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SetupDiDeleteDeviceInterfaceRegKey (scalar_t__,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetupDiDestroyDeviceInfoList (scalar_t__) ; 
 scalar_t__ SetupDiGetClassDevsA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetupDiRemoveDevice (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  SetupDiRemoveDeviceInterface (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  guid ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void test_device_interface_key(void)
{
    const char keypath[] = "System\\CurrentControlSet\\Control\\DeviceClasses\\"
        "{6a55b5a4-3f65-11db-b704-0011955c2bdb}\\"
        "##?#ROOT#LEGACY_BOGUS#0001#{6a55b5a4-3f65-11db-b704-0011955c2bdb}";
    SP_DEVICE_INTERFACE_DATA iface = { sizeof(iface) };
    SP_DEVINFO_DATA devinfo = { sizeof(devinfo) };
    HKEY parent, key, dikey;
    char buffer[5];
    HDEVINFO set;
    LONG sz, ret;

    set = SetupDiGetClassDevsA(NULL, NULL, 0, DIGCF_ALLCLASSES);
    ok(set != INVALID_HANDLE_VALUE, "SetupDiGetClassDevs failed: %#x\n", GetLastError());

    ret = SetupDiCreateDeviceInfoA(set, "ROOT\\LEGACY_BOGUS\\0001", &guid, NULL, NULL, 0, &devinfo);
    ok(ret, "SetupDiCreateDeviceInfo failed: %#x\n", GetLastError());

    ret = SetupDiCreateDeviceInterfaceA(set, &devinfo, &guid, NULL, 0, &iface);
    ok(ret, "SetupDiCreateDeviceInterface failed: %#x\n", GetLastError());

    ret = RegOpenKeyA(HKEY_LOCAL_MACHINE, keypath, &parent);
    ok(!ret, "failed to open device parent key: %u\n", ret);

    ret = RegOpenKeyA(parent, "#\\Device Parameters", &key);
    ok(ret == ERROR_FILE_NOT_FOUND, "key shouldn't exist\n");

    dikey = SetupDiCreateDeviceInterfaceRegKeyA(set, &iface, 0, KEY_ALL_ACCESS, NULL, NULL);
    ok(dikey != INVALID_HANDLE_VALUE, "got error %u\n", GetLastError());

    ret = RegOpenKeyA(parent, "#\\Device Parameters", &key);
    ok(!ret, "key should exist: %u\n", ret);

    ret = RegSetValueA(key, NULL, REG_SZ, "test", 5);
    sz = sizeof(buffer);
    ret = RegQueryValueA(dikey, NULL, buffer, &sz);
    ok(!ret, "RegQueryValue failed: %u\n", ret);
    ok(!strcmp(buffer, "test"), "got wrong data %s\n", buffer);

    RegCloseKey(dikey);
    RegCloseKey(key);

    ret = SetupDiDeleteDeviceInterfaceRegKey(set, &iface, 0);
    ok(ret, "got error %u\n", GetLastError());

    ret = RegOpenKeyA(parent, "#\\Device Parameters", &key);
    ok(ret == ERROR_FILE_NOT_FOUND, "key shouldn't exist\n");

    RegCloseKey(parent);
    SetupDiRemoveDeviceInterface(set, &iface);
    SetupDiRemoveDevice(set, &devinfo);
    SetupDiDestroyDeviceInfoList(set);
}