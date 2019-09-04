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
typedef  int /*<<< orphan*/  bufW ;
typedef  int /*<<< orphan*/  bufA ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/ * HMODULE ;
typedef  int DWORD ;

/* Variables and functions */
 int ERROR_SUCCESS ; 
 int GetLastError () ; 
 int GetModuleFileNameA (int /*<<< orphan*/ *,char*,int) ; 
 int GetModuleFileNameW (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * GetModuleHandleA (char const*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  cmpStrAW (char*,char*,int,int) ; 
 scalar_t__ is_unicode_enabled ; 
 int lstrlenA (char*) ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static void testGetModuleFileName(const char* name)
{
    HMODULE     hMod;
    char        bufA[MAX_PATH];
    WCHAR       bufW[MAX_PATH];
    DWORD       len1A, len1W = 0, len2A, len2W = 0;

    hMod = (name) ? GetModuleHandleA(name) : NULL;

    /* first test, with enough space in buffer */
    memset(bufA, '-', sizeof(bufA));
    SetLastError(0xdeadbeef);
    len1A = GetModuleFileNameA(hMod, bufA, sizeof(bufA));
    ok(GetLastError() == ERROR_SUCCESS ||
       broken(GetLastError() == 0xdeadbeef), /* <= XP SP3 */
       "LastError was not reset: %u\n", GetLastError());
    ok(len1A > 0, "Getting module filename for handle %p\n", hMod);

    if (is_unicode_enabled)
    {
        memset(bufW, '-', sizeof(bufW));
        SetLastError(0xdeadbeef);
        len1W = GetModuleFileNameW(hMod, bufW, sizeof(bufW) / sizeof(WCHAR));
        ok(GetLastError() == ERROR_SUCCESS ||
           broken(GetLastError() == 0xdeadbeef), /* <= XP SP3 */
           "LastError was not reset: %u\n", GetLastError());
        ok(len1W > 0, "Getting module filename for handle %p\n", hMod);
    }

    ok(len1A == strlen(bufA), "Unexpected length of GetModuleFilenameA (%d/%d)\n", len1A, lstrlenA(bufA));

    if (is_unicode_enabled)
    {
        ok(len1W == lstrlenW(bufW), "Unexpected length of GetModuleFilenameW (%d/%d)\n", len1W, lstrlenW(bufW));
        ok(cmpStrAW(bufA, bufW, len1A, len1W), "Comparing GetModuleFilenameAW results\n");
    }

    /* second test with a buffer too small */
    memset(bufA, '-', sizeof(bufA));
    len2A = GetModuleFileNameA(hMod, bufA, len1A / 2);
    ok(len2A > 0, "Getting module filename for handle %p\n", hMod);

    if (is_unicode_enabled)
    {
        memset(bufW, '-', sizeof(bufW));
        len2W = GetModuleFileNameW(hMod, bufW, len1W / 2);
        ok(len2W > 0, "Getting module filename for handle %p\n", hMod);
        ok(cmpStrAW(bufA, bufW, len2A, len2W), "Comparing GetModuleFilenameAW results with buffer too small\n" );
        ok(len1W / 2 == len2W, "Correct length in GetModuleFilenameW with buffer too small (%d/%d)\n", len1W / 2, len2W);
    }

    ok(len1A / 2 == len2A,
       "Correct length in GetModuleFilenameA with buffer too small (%d/%d)\n", len1A / 2, len2A);
}