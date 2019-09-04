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
typedef  int /*<<< orphan*/  org_value ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 int ERROR_ACCESS_DENIED ; 
 int ERROR_FILE_NOT_FOUND ; 
 int ERROR_INSUFFICIENT_BUFFER ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteValueA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RegOpenKeyExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int RegQueryValueExA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int RegSetValueExA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TransmissionRetryTimeoutA ; 
 int /*<<< orphan*/  WinNT_CV_WindowsA ; 
 int /*<<< orphan*/  cmd_GetTransmissionRetryTimeoutW ; 
 scalar_t__ emptyA ; 
 int /*<<< orphan*/  hXcv ; 
 int lstrlenA (char*) ; 
 char* num_0A ; 
 char* num_1000000A ; 
 char* num_1A ; 
 char* num_999999A ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int pXcvDataPort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  skip (char*,...) ; 

__attribute__((used)) static void test_XcvDataPort_GetTransmissionRetryTimeout(void)
{
    CHAR    org_value[16];
    HKEY    hroot = NULL;
    DWORD   buffer[2];
    DWORD   res;
    DWORD   needed;
    DWORD   len;


    /* ask for needed size */
    needed = (DWORD) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(hXcv, cmd_GetTransmissionRetryTimeoutW, NULL, 0, NULL, 0, &needed);
    if (res == ERROR_INVALID_PARAMETER) {
        skip("'GetTransmissionRetryTimeout' not supported\n");
        return;
    }
    len = sizeof(DWORD);
    ok( (res == ERROR_INSUFFICIENT_BUFFER) && (needed == len),
        "returned %d with %u and %u (expected ERROR_INSUFFICIENT_BUFFER "
        "and '%u')\n", res, GetLastError(), needed, len);
    len = needed;

    /* Read the original value from the registry */
    res = RegOpenKeyExA(HKEY_LOCAL_MACHINE, WinNT_CV_WindowsA, 0, KEY_ALL_ACCESS, &hroot);
    if (res == ERROR_ACCESS_DENIED) {
        skip("ACCESS_DENIED\n");
        return;
    }

    if (res != ERROR_SUCCESS) {
        /* unable to open the registry: skip the test */
        skip("got %d\n", res);
        return;
    }

    org_value[0] = '\0';
    needed = sizeof(org_value)-1 ;
    res = RegQueryValueExA(hroot, TransmissionRetryTimeoutA, NULL, NULL, (PBYTE) org_value, &needed);
    ok( (res == ERROR_SUCCESS) || (res == ERROR_FILE_NOT_FOUND),
        "returned %u and %u for \"%s\" (expected ERROR_SUCCESS or "
        "ERROR_FILE_NOT_FOUND)\n", res, needed, org_value);

    /* Get default value (documented as 90 in the w2k reskit, but that is wrong) */
    RegDeleteValueA(hroot, TransmissionRetryTimeoutA);
    needed = (DWORD) 0xdeadbeef;
    buffer[0] = 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(hXcv, cmd_GetTransmissionRetryTimeoutW, NULL, 0, (PBYTE) buffer, len, &needed);
    ok( (res == ERROR_SUCCESS) && (buffer[0] == 45),
        "returned %d with %u and %u for %d\n (expected ERROR_SUCCESS "
        "for '45')\n", res, GetLastError(), needed, buffer[0]);

    /* the default timeout is returned, when the value is empty */
    res = RegSetValueExA(hroot, TransmissionRetryTimeoutA, 0, REG_SZ, (PBYTE)emptyA, 1);
    ok(res == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %u\n", GetLastError());
    needed = (DWORD) 0xdeadbeef;
    buffer[0] = 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(hXcv, cmd_GetTransmissionRetryTimeoutW, NULL, 0, (PBYTE) buffer, len, &needed);
    ok( (res == ERROR_SUCCESS) && (buffer[0] == 45),
        "returned %d with %u and %u for %d\n (expected ERROR_SUCCESS "
        "for '45')\n", res, GetLastError(), needed, buffer[0]);

    /* the dialog is limited (1 - 999999), but that is done somewhere else */
    res = RegSetValueExA(hroot, TransmissionRetryTimeoutA, 0, REG_SZ, (PBYTE)num_0A, lstrlenA(num_0A)+1);
    ok(res == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %u\n", GetLastError());
    needed = (DWORD) 0xdeadbeef;
    buffer[0] = 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(hXcv, cmd_GetTransmissionRetryTimeoutW, NULL, 0, (PBYTE) buffer, len, &needed);
    ok( (res == ERROR_SUCCESS) && (buffer[0] == 0),
        "returned %d with %u and %u for %d\n (expected ERROR_SUCCESS "
        "for '0')\n", res, GetLastError(), needed, buffer[0]);


    res = RegSetValueExA(hroot, TransmissionRetryTimeoutA, 0, REG_SZ, (PBYTE)num_1A, lstrlenA(num_1A)+1);
    ok(res == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %u\n", GetLastError());
    needed = (DWORD) 0xdeadbeef;
    buffer[0] = 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(hXcv, cmd_GetTransmissionRetryTimeoutW, NULL, 0, (PBYTE) buffer, len, &needed);
    ok( (res == ERROR_SUCCESS) && (buffer[0] == 1),
        "returned %d with %u and %u for %d\n (expected 'ERROR_SUCCESS' "
        "for '1')\n", res, GetLastError(), needed, buffer[0]);

    res = RegSetValueExA(hroot, TransmissionRetryTimeoutA, 0, REG_SZ, (PBYTE)num_999999A, lstrlenA(num_999999A)+1);
    ok(res == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %u\n", GetLastError());
    needed = (DWORD) 0xdeadbeef;
    buffer[0] = 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(hXcv, cmd_GetTransmissionRetryTimeoutW, NULL, 0, (PBYTE) buffer, len, &needed);
    ok( (res == ERROR_SUCCESS) && (buffer[0] == 999999),
        "returned %d with %u and %u for %d\n (expected ERROR_SUCCESS "
        "for '999999')\n", res, GetLastError(), needed, buffer[0]);


    res = RegSetValueExA(hroot, TransmissionRetryTimeoutA, 0, REG_SZ, (PBYTE)num_1000000A, lstrlenA(num_1000000A)+1);
    ok(res == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %u\n", GetLastError());
    needed = (DWORD) 0xdeadbeef;
    buffer[0] = 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(hXcv, cmd_GetTransmissionRetryTimeoutW, NULL, 0, (PBYTE) buffer, len, &needed);
    ok( (res == ERROR_SUCCESS) && (buffer[0] == 1000000),
        "returned %d with %u and %u for %d\n (expected ERROR_SUCCESS "
        "for '1000000')\n", res, GetLastError(), needed, buffer[0]);

    /* restore the original value */
    RegDeleteValueA(hroot, TransmissionRetryTimeoutA);
    if (org_value[0]) {
        res = RegSetValueExA(hroot, TransmissionRetryTimeoutA, 0, REG_SZ, (PBYTE)org_value, lstrlenA(org_value)+1);
        ok(res == ERROR_SUCCESS, "unable to restore original value (got %u): %s\n", res, org_value);
    }

    RegCloseKey(hroot);
}