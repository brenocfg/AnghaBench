#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int dwFileVersionLS; scalar_t__ dwFileVersionMS; } ;
typedef  TYPE_1__ VS_FIXEDFILEINFO ;
typedef  int /*<<< orphan*/  UINT ;
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int DWORDLONG ;
typedef  long DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 long ERROR_BAD_PATHNAME ; 
 long ERROR_INVALID_DATA ; 
 int GetFileVersionInfoA (char*,int /*<<< orphan*/ ,long,scalar_t__) ; 
 long GetFileVersionInfoSizeA (char*,long*) ; 
 long GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int MAX_PATH ; 
 long MY_LAST_ERROR ; 
 long NO_ERROR ; 
 int /*<<< orphan*/  SetLastError (long) ; 
 int VerQueryValueA (scalar_t__,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VersionDwordLong2String (int,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void test_info(void)
{
    DWORD hdl, retval;
    PVOID pVersionInfo = NULL;
    BOOL boolret;
    VS_FIXEDFILEINFO *pFixedVersionInfo;
    UINT uiLength;
    char VersionString[MAX_PATH];
    static const char backslash[] = "\\";
    DWORDLONG dwlVersion;

    hdl = 0x55555555;
    SetLastError(MY_LAST_ERROR);
    retval = GetFileVersionInfoSizeA( "kernel32.dll", &hdl);
    ok( retval,
	"GetFileVersionInfoSizeA result wrong! <> 0L expected, got 0x%08x\n",
	retval);
    ok((NO_ERROR == GetLastError()) || (MY_LAST_ERROR == GetLastError()),
	"Last error wrong! NO_ERROR/0x%08x (NT4)  expected, got %u\n",
	MY_LAST_ERROR, GetLastError());
    ok( hdl == 0L,
	"Handle wrong! 0L expected, got 0x%08x\n", hdl);

    if ( retval == 0 || hdl != 0)
        return;

    pVersionInfo = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, retval );
    ok(pVersionInfo != 0, "HeapAlloc failed\n" );
    if (pVersionInfo == 0)
        return;

    if (0)
    {
    /* this test crashes on WinNT4
     */
    boolret = GetFileVersionInfoA( "kernel32.dll", 0, retval, 0);
    ok (!boolret, "GetFileVersionInfoA should have failed: GetLastError = %u\n", GetLastError());
    ok ((GetLastError() == ERROR_INVALID_DATA) || (GetLastError() == ERROR_BAD_PATHNAME) ||
	(GetLastError() == NO_ERROR),
        "Last error wrong! ERROR_INVALID_DATA/ERROR_BAD_PATHNAME (ME)/"
	"NO_ERROR (95) expected, got %u\n",
        GetLastError());
    }

    boolret = GetFileVersionInfoA( "kernel32.dll", 0, retval, pVersionInfo );
    ok (boolret, "GetFileVersionInfoA failed: GetLastError = %u\n", GetLastError());
    if (!boolret)
        goto cleanup;

    boolret = VerQueryValueA( pVersionInfo, NULL, (LPVOID *)&pFixedVersionInfo, &uiLength );
    ok (boolret || GetLastError() == NO_ERROR /* Win98 */,
       "VerQueryValueA failed: GetLastError = %u\n", GetLastError());

    boolret = VerQueryValueA( pVersionInfo, "", (LPVOID *)&pFixedVersionInfo, &uiLength );
    ok (boolret, "VerQueryValueA failed: GetLastError = %u\n", GetLastError());

    boolret = VerQueryValueA( pVersionInfo, backslash, (LPVOID *)&pFixedVersionInfo, &uiLength );
    ok (boolret, "VerQueryValueA failed: GetLastError = %u\n", GetLastError());
    if (!boolret)
        goto cleanup;

    dwlVersion = (((DWORDLONG)pFixedVersionInfo->dwFileVersionMS) << 32) +
        pFixedVersionInfo->dwFileVersionLS;

    VersionDwordLong2String(dwlVersion, VersionString);

    trace("kernel32.dll version: %s\n", VersionString);

    if (0)
    {
    /* this test crashes on WinNT4
     */
    boolret = VerQueryValueA( pVersionInfo, backslash, (LPVOID *)&pFixedVersionInfo, 0);
    ok (boolret, "VerQueryValue failed: GetLastError = %u\n", GetLastError());
    }

cleanup:
    HeapFree( GetProcessHeap(), 0, pVersionInfo);
}