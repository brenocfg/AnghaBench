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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateServiceW (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DELETE ; 
 int /*<<< orphan*/  DNS_ERROR_RCODE_NXRRSET ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 scalar_t__ REG_DWORD ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  SERVICE_BOOT_START ; 
 int /*<<< orphan*/  SERVICE_ERROR_IGNORE ; 
 int /*<<< orphan*/  SERVICE_KERNEL_DRIVER ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StringCbPrintfW (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_err (scalar_t__) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static int MakeService(SC_HANDLE hScm, const wchar_t *serviceName, SC_HANDLE *hService, DWORD *tag)
{
    DWORD ret;
    HKEY hKey = NULL;
    DWORD type = 0, tagData = 0, tagSize;
    wchar_t keyName[256];

    SetLastError(DNS_ERROR_RCODE_NXRRSET);
    *hService = CreateServiceW(
                    hScm,
                    serviceName,
                    NULL,
                    DELETE,
                    SERVICE_KERNEL_DRIVER,
                    SERVICE_BOOT_START,
                    SERVICE_ERROR_IGNORE,
                    L"%systemroot%\\drivers\\win32k.sys",
                    L"advapi32_apitest_CreateService_Test_Group",
                    tag,
                    NULL,
                    NULL,
                    NULL);

    ok(*hService != NULL, "Failed to create service, error=0x%08lx\n", GetLastError());
    if (!*hService)
    {
        skip("No service; cannot proceed with CreateService test\n");
        return 1;
    }

    ok_err(ERROR_SUCCESS);

    ok(*tag != 0, "tag is zero, expected nonzero\n");

    StringCbPrintfW(keyName, sizeof keyName, L"System\\CurrentControlSet\\Services\\%ls", serviceName);
    ret = RegOpenKeyW(HKEY_LOCAL_MACHINE, keyName, &hKey);
    ok(ret == ERROR_SUCCESS, "RegOpenKeyW failed with 0x%08lx\n", ret);
    if (ret)
    {
        skip("No regkey; cannot proceed with CreateService test\n");
        return 2;
    }

    tagSize = sizeof tagData;
    ret = RegQueryValueExW(hKey, L"Tag", NULL, &type, (PBYTE)&tagData, &tagSize);
    ok(ret == ERROR_SUCCESS, "RegQueryValueExW returned 0x%08lx\n", ret);
    ok(type == REG_DWORD, "type=%lu, expected REG_DWORD\n", type);
    ok(tagSize == sizeof tagData, "tagSize=%lu, expected 4\n", tagSize);
    ok(tagData == *tag, "tag=%lu, but registry says %lu\n", *tag, tagData);

    RegCloseKey(hKey);

    return 0;
}