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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  wMilliseconds; int /*<<< orphan*/  wSecond; int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wHour; int /*<<< orphan*/  wYear; int /*<<< orphan*/  wDay; int /*<<< orphan*/  wMonth; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int /*<<< orphan*/  GlobalFifoEnable ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FileTimeToSystemTime (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 int /*<<< orphan*/  REG_OPTION_VOLATILE ; 
 int /*<<< orphan*/  REG_SZ ; 
 scalar_t__ RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__*) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ RegQueryInfoKeyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ RegSetValueExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 

void test4(void)
{
  HKEY hKey = NULL,hKey1;
  DWORD dwDisposition;
  DWORD dwError;
  DWORD  RegDataType, RegDataSize;
  BOOL GlobalFifoEnable;
  HKEY hPortKey;
  DWORD RegDisposition;
  WCHAR szClass[260];
  DWORD cchClass;
  DWORD cSubKeys;
  DWORD cchMaxSubkey;
  DWORD cchMaxClass;
  DWORD cValues;
  DWORD cchMaxValueName;
  DWORD cbMaxValueData;
  DWORD cbSecurityDescriptor;
  FILETIME ftLastWriteTime;
  SYSTEMTIME LastWriteTime;

  dprintf ("RegOpenKeyExW HKLM\\System\\Setup: ");
  dwError = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                           L"System\\Setup",
                           0,
                           KEY_ALL_ACCESS,
                           &hKey1);
  dprintf("\t\tdwError =%x\n",dwError);
  if (dwError == ERROR_SUCCESS)
    {
      dprintf("RegQueryInfoKeyW: ");
      cchClass=260;
      dwError = RegQueryInfoKeyW(hKey1
	, szClass, &cchClass, NULL, &cSubKeys
	, &cchMaxSubkey, &cchMaxClass, &cValues, &cchMaxValueName
	, &cbMaxValueData, &cbSecurityDescriptor, &ftLastWriteTime);
      dprintf ("\t\t\t\tdwError %x\n", dwError);
      FileTimeToSystemTime(&ftLastWriteTime,&LastWriteTime);
      dprintf ("\tnb of subkeys=%d,last write : %d/%d/%d %d:%02.2d'%02.2d''%03.3d\n",cSubKeys
		,LastWriteTime.wMonth
		,LastWriteTime.wDay
		,LastWriteTime.wYear
		,LastWriteTime.wHour
		,LastWriteTime.wMinute
		,LastWriteTime.wSecond
		,LastWriteTime.wMilliseconds
		);
    }


   dprintf ("RegOpenKeyExW: ");
   dwError = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                           L"System\\ControlSet001\\Services\\Serial",
                           0,
                           KEY_ALL_ACCESS,
                           &hKey);
   dprintf ("\t\t\t\t\tdwError %x\n", dwError);
   RegDataSize = sizeof(GlobalFifoEnable);
   if (dwError == ERROR_SUCCESS)
   {
     dprintf ("RegQueryValueExW: ");
     dwError = RegQueryValueExW(hKey,
                        L"ForceFifoEnable",
                        NULL,
                        &RegDataType,
                        (PBYTE)&GlobalFifoEnable,
                        &RegDataSize);
    dprintf("\t\t\t\tdwError =%x\n",dwError);
    if (dwError == 0)
    {
        dprintf("\tValue:DT=%d, DS=%d, Value=%d\n"
		,RegDataType
		,RegDataSize
		,GlobalFifoEnable);
    }
   }
   dprintf ("RegCreateKeyExW: ");
   dwError = RegCreateKeyExW(hKey,
                         L"Parameters\\Serial001",
                         0,
                         NULL,
                         0,
                         KEY_ALL_ACCESS,
                         NULL,
                         &hPortKey,
                         &RegDisposition
                        );
   dprintf ("\t\t\t\tdwError %x\n", dwError);

   dprintf ("RegCreateKeyExW: ");
   dwError = RegCreateKeyExW (HKEY_LOCAL_MACHINE,
                              L"Software\\test4reactos\\test",
                              0,
                              NULL,
                              REG_OPTION_NON_VOLATILE,
                              KEY_ALL_ACCESS,
                              NULL,
                              &hKey,
                              &dwDisposition);

   dprintf ("\t\t\t\tdwError %x ", dwError);
   dprintf ("dwDisposition %x\n", dwDisposition);
   if (dwError == ERROR_SUCCESS)
   {
     dprintf ("RegSetValueExW: ");
     dwError = RegSetValueExW (hKey,
                             L"TestValue",
                             0,
                             REG_SZ,
                             (BYTE*)L"TestString",
                             20);

     dprintf ("\t\t\t\tdwError %x\n", dwError);
     dprintf ("RegCloseKey: ");
     dwError = RegCloseKey (hKey);
     dprintf ("\t\t\t\t\tdwError %x\n", dwError);
   }
   dprintf ("\n\n");

   hKey = NULL;

   dprintf ("RegCreateKeyExW: ");
   dwError = RegCreateKeyExW (HKEY_LOCAL_MACHINE,
                              L"software\\Test",
                              0,
                              NULL,
                              REG_OPTION_VOLATILE,
                              KEY_ALL_ACCESS,
                              NULL,
                              &hKey,
                              &dwDisposition);

   dprintf ("\t\t\t\tdwError %x ", dwError);
   dprintf ("dwDisposition %x\n", dwDisposition);


   if (dwError == ERROR_SUCCESS)
   {
     dprintf("RegQueryInfoKeyW: ");
     cchClass=260;
     dwError = RegQueryInfoKeyW(hKey
	, szClass, &cchClass, NULL, &cSubKeys
	, &cchMaxSubkey, &cchMaxClass, &cValues, &cchMaxValueName
	, &cbMaxValueData, &cbSecurityDescriptor, &ftLastWriteTime);
     dprintf ("\t\t\t\tdwError %x\n", dwError);
     FileTimeToSystemTime(&ftLastWriteTime,&LastWriteTime);
     dprintf ("\tnb of subkeys=%d,last write : %d/%d/%d %d:%02.2d'%02.2d''%03.3d\n",cSubKeys
		,LastWriteTime.wMonth
		,LastWriteTime.wDay
		,LastWriteTime.wYear
		,LastWriteTime.wHour
		,LastWriteTime.wMinute
		,LastWriteTime.wSecond
		,LastWriteTime.wMilliseconds
		);
     dprintf ("RegCloseKey: ");
     dwError = RegCloseKey (hKey);
     dprintf ("\t\t\t\t\tdwError %x\n", dwError);
   }
   dprintf ("\nTests done...\n");
}