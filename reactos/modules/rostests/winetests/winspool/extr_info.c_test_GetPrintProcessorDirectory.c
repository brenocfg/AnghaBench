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
typedef  char* LPBYTE ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  ERROR_INVALID_ENVIRONMENT ; 
 int /*<<< orphan*/  ERROR_INVALID_LEVEL ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERROR_INVALID_USER_BUFFER ; 
 int /*<<< orphan*/  GetLastError () ; 
 int GetPrintProcessorDirectoryA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,int,int*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RPC_S_INVALID_NET_ADDR ; 
 int /*<<< orphan*/  RPC_S_SERVER_UNAVAILABLE ; 
 int /*<<< orphan*/  RPC_X_NULL_REF_POINTER ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/ * empty ; 
 int /*<<< orphan*/ * env_win9x_case ; 
 int /*<<< orphan*/ * env_x86 ; 
 int /*<<< orphan*/ * invalid_env ; 
 scalar_t__ is_spooler_deactivated (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * server_does_not_exist ; 

__attribute__((used)) static void test_GetPrintProcessorDirectory(void)
{
    LPBYTE      buffer = NULL;
    DWORD       cbBuf = 0;
    DWORD       pcbNeeded = 0;
    BOOL        res;


    SetLastError(0xdeadbeef);
    res = GetPrintProcessorDirectoryA(NULL, NULL, 1, NULL, 0, &cbBuf);
    if (is_spooler_deactivated(res, GetLastError())) return;

    ok( !res && (GetLastError() == ERROR_INSUFFICIENT_BUFFER),
        "returned %d with %d (expected '0' with ERROR_INSUFFICIENT_BUFFER)\n",
        res, GetLastError());

    buffer = HeapAlloc(GetProcessHeap(), 0, cbBuf*2);
    if(buffer == NULL)  return;

    buffer[0] = '\0';
    SetLastError(0xdeadbeef);
    res = GetPrintProcessorDirectoryA(NULL, NULL, 1, buffer, cbBuf, &pcbNeeded);
    ok(res, "returned %d with %d (expected '!= 0')\n", res, GetLastError());

    SetLastError(0xdeadbeef);
    buffer[0] = '\0';
    res = GetPrintProcessorDirectoryA(NULL, NULL, 1, buffer, cbBuf*2, &pcbNeeded);
    ok(res, "returned %d with %d (expected '!= 0')\n", res, GetLastError());
 
    /* Buffer too small */
    buffer[0] = '\0';
    SetLastError(0xdeadbeef);
    res = GetPrintProcessorDirectoryA( NULL, NULL, 1, buffer, cbBuf-1, &pcbNeeded);
    ok( !res && (GetLastError() == ERROR_INSUFFICIENT_BUFFER),
        "returned %d with %d (expected '0' with ERROR_INSUFFICIENT_BUFFER)\n",
        res, GetLastError());

    if (0)
    {
    /* XPsp2: the program will crash here, when the spooler is not running  */
    /*        GetPrinterDriverDirectory has the same bug */
    pcbNeeded = 0;
    SetLastError(0xdeadbeef);
    res = GetPrintProcessorDirectoryA( NULL, NULL, 1, NULL, cbBuf, &pcbNeeded);
    /* NT: ERROR_INVALID_USER_BUFFER, 9x: res != 0  */
    ok( (!res && (GetLastError() == ERROR_INVALID_USER_BUFFER)) ||
        broken(res),
        "returned %d with %d (expected '0' with ERROR_INVALID_USER_BUFFER)\n",
        res, GetLastError());
    }

    buffer[0] = '\0';
    SetLastError(0xdeadbeef);
    res = GetPrintProcessorDirectoryA( NULL, NULL, 1, buffer, cbBuf, NULL);
    /* w7 with deactivated spooler: ERROR_INVALID_PARAMETER,
       NT: RPC_X_NULL_REF_POINTER, 9x: res != 0  */
    ok( !res && ((GetLastError() == RPC_X_NULL_REF_POINTER) ||
                 (GetLastError() == ERROR_INVALID_PARAMETER)),
        "returned %d with %d (expected '0' with RPC_X_NULL_REF_POINTER "
        "or with ERROR_INVALID_PARAMETER)\n", res, GetLastError());

    buffer[0] = '\0';
    SetLastError(0xdeadbeef);
    res = GetPrintProcessorDirectoryA( NULL, NULL, 1, NULL, cbBuf, NULL);
    /* w7 with deactivated spooler: ERROR_INVALID_PARAMETER,
       NT: RPC_X_NULL_REF_POINTER, 9x: res != 0  */
    ok( !res && ((GetLastError() == RPC_X_NULL_REF_POINTER) ||
                 (GetLastError() == ERROR_INVALID_PARAMETER)),
        "returned %d with %d (expected '0' with RPC_X_NULL_REF_POINTER "
        "or with ERROR_INVALID_PARAMETER)\n", res, GetLastError());

    /* with a valid buffer, but level is invalid */
    buffer[0] = '\0';
    SetLastError(0xdeadbeef);
    res = GetPrintProcessorDirectoryA(NULL, NULL, 0, buffer, cbBuf, &pcbNeeded);
    /* Level is ignored in win9x*/
    ok( (!res && (GetLastError() == ERROR_INVALID_LEVEL)) ||
        broken(res && buffer[0]),
        "returned %d with %d (expected '0' with ERROR_INVALID_LEVEL)\n",
        res, GetLastError());

    buffer[0] = '\0';
    SetLastError(0xdeadbeef);
    res = GetPrintProcessorDirectoryA(NULL, NULL, 2, buffer, cbBuf, &pcbNeeded);
    /* Level is ignored on win9x*/
    ok( (!res && (GetLastError() == ERROR_INVALID_LEVEL)) ||
        broken(res && buffer[0]),
        "returned %d with %d (expected '0' with ERROR_INVALID_LEVEL)\n",
        res, GetLastError());

    /* Empty environment is the same as the default environment */
    buffer[0] = '\0';
    SetLastError(0xdeadbeef);
    res = GetPrintProcessorDirectoryA(NULL, empty, 1, buffer, cbBuf*2, &pcbNeeded);
    ok(res, "returned %d with %d (expected '!= 0')\n", res, GetLastError());

    /* "Windows 4.0" is valid for win9x and NT */
    buffer[0] = '\0';
    SetLastError(0xdeadbeef);
    res = GetPrintProcessorDirectoryA(NULL, env_win9x_case, 1, buffer, cbBuf*2, &pcbNeeded);
    ok(res, "returned %d with %d (expected '!= 0')\n", res, GetLastError());


    /* "Windows NT x86" is invalid for win9x */
    buffer[0] = '\0';
    SetLastError(0xdeadbeef);
    res = GetPrintProcessorDirectoryA(NULL, env_x86, 1, buffer, cbBuf*2, &pcbNeeded);
    ok( res || (GetLastError() == ERROR_INVALID_ENVIRONMENT), 
        "returned %d with %d (expected '!= 0' or '0' with "
        "ERROR_INVALID_ENVIRONMENT)\n", res, GetLastError());

    /* invalid on all systems */
    buffer[0] = '\0';
    SetLastError(0xdeadbeef);
    res = GetPrintProcessorDirectoryA(NULL, invalid_env, 1, buffer, cbBuf*2, &pcbNeeded);
    ok( !res && (GetLastError() == ERROR_INVALID_ENVIRONMENT), 
        "returned %d with %d (expected '0' with ERROR_INVALID_ENVIRONMENT)\n",
        res, GetLastError());

    /* Empty servername is the same as the local computer */
    buffer[0] = '\0';
    SetLastError(0xdeadbeef);
    res = GetPrintProcessorDirectoryA(empty, NULL, 1, buffer, cbBuf*2, &pcbNeeded);
    ok(res, "returned %d with %d (expected '!= 0')\n", res, GetLastError());

    /* invalid on all systems */
    buffer[0] = '\0';
    SetLastError(0xdeadbeef);
    res = GetPrintProcessorDirectoryA(server_does_not_exist, NULL, 1, buffer, cbBuf*2, &pcbNeeded);
    ok( !res, "expected failure\n");
    ok( GetLastError() == RPC_S_SERVER_UNAVAILABLE || /* NT */
        GetLastError() == ERROR_INVALID_PARAMETER ||  /* 9x */
        GetLastError() == RPC_S_INVALID_NET_ADDR,     /* Some Vista */
        "unexpected last error %d\n", GetLastError());

    HeapFree(GetProcessHeap(), 0, buffer);
}