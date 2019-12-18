#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lpszFontSearch ;
typedef  int /*<<< orphan*/  lpszFontPath ;
struct TYPE_7__ {char* cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATAW ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_8__ {int Length; int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_2__ UNICODE_STRING ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int INT ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 scalar_t__ FindFirstFileW (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetWindowsDirectoryW (int /*<<< orphan*/ *,int) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int NtGdiAddFontResourceW (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlDosPathNameToNtPathName_U (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlFreeUnicodeString (TYPE_2__*) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  StringCbCatW (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  StringCbCopyW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  skip (char*) ; 

void Test_NtGdiAddFontResourceW()
{
    WCHAR lpszFontPath[MAX_PATH];
    WCHAR lpszFontSearch[MAX_PATH];

    INT ret;
    UNICODE_STRING NtAbsPath;
    WIN32_FIND_DATAW FindFileData;
    HANDLE hFind;
    ULONG cwc;

    // Create "Font" folder Path
    GetWindowsDirectoryW(lpszFontPath, MAX_PATH);
    StringCbCatW(lpszFontPath, sizeof(lpszFontPath), L"\\Fonts\\");

    // Search first .ttf file in Fonts Path
    StringCbCopyW(lpszFontSearch, sizeof(lpszFontSearch), lpszFontPath);
    StringCbCatW(lpszFontSearch, sizeof(lpszFontSearch), L"*.ttf");

    hFind = FindFirstFileW(lpszFontSearch, &FindFileData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        skip("Unable to find fonts in Font directory!\n");
        return;
    }

    // File found. Create FontPath to File.
    StringCbCatW(lpszFontPath, sizeof(lpszFontPath), FindFileData.cFileName);

    // Fail due "cwc" being zero.
    SetLastError(0xdeaddead);
    RtlInitUnicodeString(&NtAbsPath, NULL);
    RtlDosPathNameToNtPathName_U(lpszFontPath, &NtAbsPath, NULL, NULL);
    cwc = 0;
    ret =  NtGdiAddFontResourceW(NtAbsPath.Buffer, cwc, 1, 0, 0, 0);

    ok(ret == 0, "Expected 0 files added. Added: %d\n", ret);
    ok(GetLastError() == 0xdeaddead, "Expected 0xdeaddead. Obtained: 0x%lx\n", GetLastError());

    RtlFreeUnicodeString(&NtAbsPath);

    // "cwc" must count the null terminator. Otherwise fails.
    SetLastError(0xdeaddead);
    RtlInitUnicodeString(&NtAbsPath, NULL);
    RtlDosPathNameToNtPathName_U(lpszFontPath, &NtAbsPath, NULL, NULL);
    cwc = NtAbsPath.Length / sizeof(WCHAR);
    ret =  NtGdiAddFontResourceW(NtAbsPath.Buffer, cwc, 1, 0, 0, 0);

    ok(ret == 0, "Expected 0 files added. Added: %d\n", ret);
    ok(GetLastError() == 0xdeaddead, "Expected 0xdeaddead. Obtained: 0x%lx\n", GetLastError());

    RtlFreeUnicodeString(&NtAbsPath);

    // Correct "cwc" value.
    SetLastError(0xdeaddead);
    RtlInitUnicodeString(&NtAbsPath, NULL);
    RtlDosPathNameToNtPathName_U(lpszFontPath, &NtAbsPath, NULL, NULL);
    cwc = NtAbsPath.Length / sizeof(WCHAR) + 1;
    ret =  NtGdiAddFontResourceW(NtAbsPath.Buffer, cwc, 1, 0, 0, 0);

    ok(ret == 1, "Expected 1 files added. Added: %d\n", ret);
    ok(GetLastError() == 0xdeaddead, "Expected 0xdeaddead. Obtained: 0x%lx\n", GetLastError());

    RtlFreeUnicodeString(&NtAbsPath);

    // Test an invalid pointer.
    SetLastError(0xdeadbeef);
    ret =  NtGdiAddFontResourceW((PVOID)-4, 123, 1, 0, 0, NULL);

    ok(ret == 0, "Expected 0 files added. Added: %d\n", ret);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef. Obtained: 0x%lx\n", GetLastError());
}