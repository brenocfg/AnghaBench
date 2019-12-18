#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  lpszSourceUrlName; } ;
typedef  TYPE_1__ INTERNET_CACHE_ENTRY_INFOA ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 int FALSE ; 
 int FindCloseUrlCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FindFirstUrlCacheEntryA (int /*<<< orphan*/ *,TYPE_1__*,int*) ; 
 int FindNextUrlCacheEntryA (int /*<<< orphan*/ *,TYPE_1__*,int*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_url ; 

__attribute__((used)) static void test_find_url_cache_entriesA(void)
{
    BOOL ret;
    HANDLE hEnumHandle;
    BOOL found = FALSE;
    DWORD cbCacheEntryInfo;
    DWORD cbCacheEntryInfoSaved;
    INTERNET_CACHE_ENTRY_INFOA *lpCacheEntryInfo;

    cbCacheEntryInfo = 0;
    SetLastError(0xdeadbeef);
    hEnumHandle = FindFirstUrlCacheEntryA(NULL, NULL, &cbCacheEntryInfo);
    ok(!hEnumHandle, "FindFirstUrlCacheEntry should have failed\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "FindFirstUrlCacheEntry should have set last error to ERROR_INSUFFICIENT_BUFFER instead of %d\n", GetLastError());
    lpCacheEntryInfo = HeapAlloc(GetProcessHeap(), 0, cbCacheEntryInfo * sizeof(char));
    cbCacheEntryInfoSaved = cbCacheEntryInfo;
    hEnumHandle = FindFirstUrlCacheEntryA(NULL, lpCacheEntryInfo, &cbCacheEntryInfo);
    ok(hEnumHandle != NULL, "FindFirstUrlCacheEntry failed with error %d\n", GetLastError());
    while (TRUE)
    {
        if (!strcmp(lpCacheEntryInfo->lpszSourceUrlName, test_url))
        {
            found = TRUE;
            ret = TRUE;
            break;
        }
        SetLastError(0xdeadbeef);
        cbCacheEntryInfo = cbCacheEntryInfoSaved;
        ret = FindNextUrlCacheEntryA(hEnumHandle, lpCacheEntryInfo, &cbCacheEntryInfo);
        if (!ret)
        {
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
                lpCacheEntryInfo = HeapReAlloc(GetProcessHeap(), 0, lpCacheEntryInfo, cbCacheEntryInfo);
                cbCacheEntryInfoSaved = cbCacheEntryInfo;
                ret = FindNextUrlCacheEntryA(hEnumHandle, lpCacheEntryInfo, &cbCacheEntryInfo);
            }
        }
        if (!ret)
            break;
    }
    ok(ret, "FindNextUrlCacheEntry failed with error %d\n", GetLastError());
    ok(found, "Committed url cache entry not found during enumeration\n");

    ret = FindCloseUrlCache(hEnumHandle);
    ok(ret, "FindCloseUrlCache failed with error %d\n", GetLastError());
    HeapFree(GetProcessHeap(), 0, lpCacheEntryInfo);
}