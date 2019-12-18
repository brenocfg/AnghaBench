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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  szData ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  DeviceId; int /*<<< orphan*/  VendorId; } ;
typedef  int /*<<< orphan*/  LSTATUS ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  TYPE_1__ DXGI_ADAPTER_DESC ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  RegQueryValueEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  _snwprintf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcslen (int /*<<< orphan*/ *) ; 
 scalar_t__ wcsncmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HKEY GetAdapterRegistry(vlc_object_t *obj, DXGI_ADAPTER_DESC *adapterDesc)
{
    HKEY hKey;
    WCHAR key[128];
    WCHAR szData[256], lookup[256];
    DWORD len = 256;
    LSTATUS ret;

    _snwprintf(lookup, 256, TEXT("pci\\ven_%04x&dev_%04x"), adapterDesc->VendorId, adapterDesc->DeviceId);
    for (int i=0;;i++)
    {
        _snwprintf(key, 128, TEXT("SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}\\%04d"), i);
        ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, key, 0, KEY_READ, &hKey);
        if ( ret != ERROR_SUCCESS )
        {
            msg_Warn(obj, "failed to read the %d Display Adapter registry key (%ld)", i, ret);
            return NULL;
        }

        len = sizeof(szData);
        ret = RegQueryValueEx( hKey, TEXT("MatchingDeviceId"), NULL, NULL, (LPBYTE) &szData, &len );
        if ( ret == ERROR_SUCCESS ) {
            if (wcsncmp(lookup, szData, wcslen(lookup)) == 0)
                return hKey;
            msg_Dbg(obj, "different %d device %ls vs %ls", i, lookup, szData);
        }
        else
            msg_Warn(obj, "failed to get the %d MatchingDeviceId (%ld)", i, ret);

        RegCloseKey(hKey);
    }
    return NULL;
}