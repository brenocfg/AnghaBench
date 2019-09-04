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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ LSTATUS ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  (* ENUM_INTERFACE_CALLBACK ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_OUTOFMEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ ,int,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryInfoKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

LSTATUS
EnumInterfaces(
    ENUM_INTERFACE_CALLBACK CallbackRoutine,
    PVOID InterfaceCallbackContext)
{
    HKEY hKey, hInterface;
    LSTATUS Status;
    DWORD NumInterfaces, InterfaceNameLen, Index, Length;
    LPWSTR InterfaceName;

    /* first open interface key */
    Status = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces", 0, KEY_READ, &hKey);

    /* check for success */
    if (Status != ERROR_SUCCESS)
    {
        /* failed to open interface key */
        return Status;
    }

    /* now get maximum interface name length and number of interfaces */
    Status = RegQueryInfoKeyW(hKey, NULL, NULL, NULL, &NumInterfaces, &InterfaceNameLen, NULL, NULL, NULL, NULL, NULL, NULL);
    if (Status != ERROR_SUCCESS)
    {
        /* failed to get key info */
        RegCloseKey(hKey);
        return Status;
    }

    /* RegQueryInfoKey does not include terminating null */
    InterfaceNameLen++;

    /* allocate interface name */
    InterfaceName = (LPWSTR) HeapAlloc(GetProcessHeap(), 0, InterfaceNameLen * sizeof(WCHAR));

    if (!InterfaceName)
    {
        /* no memory */
        RegCloseKey(hKey);
        return ERROR_OUTOFMEMORY;
    }

    /* no enumerate all interfaces */
    for(Index = 0; Index < NumInterfaces; Index++)
    {
        /* query interface name */
        Length = InterfaceNameLen;
        Status = RegEnumKeyExW(hKey, Index, InterfaceName, &Length, NULL, NULL, NULL, NULL);

        if (Status == ERROR_SUCCESS)
        {
            /* make sure it is null terminated */
            InterfaceName[Length] = L'\0';

            /* now open child key */
            Status = RegOpenKeyExW(hKey, InterfaceName, 0, KEY_READ, &hInterface);

            if (Status == ERROR_SUCCESS)
            {
                /* perform enumeration callback */
                CallbackRoutine(hInterface, InterfaceName, InterfaceCallbackContext);

                /* close interface key */
                RegCloseKey(hInterface);
            }
        }
    }

    /* free interface name */
    HeapFree(GetProcessHeap(), 0, InterfaceName);

    /* close root interface key */
    RegCloseKey(hKey);

    /* done */
    return Status;
}