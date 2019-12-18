#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int CacheEntryType; } ;
typedef  TYPE_1__ INTERNET_CACHE_ENTRY_INFOA ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_ENTRY_ATTRIBUTE_FC ; 
 int ERROR_FILE_NOT_FOUND ; 
 int ERROR_INSUFFICIENT_BUFFER ; 
 int ERROR_INVALID_PARAMETER ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int GetUrlCacheEntryInfoExA (char*,TYPE_1__*,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int) ; 
 int GetUrlCacheEntryInfoExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int SetUrlCacheEntryInfoA (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  check_cache_entry_infoA (char*,TYPE_1__*) ; 
 int ie10_cache ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ old_ie ; 
 char* test_url ; 
 int /*<<< orphan*/  test_urlW ; 

__attribute__((used)) static void test_GetUrlCacheEntryInfoExA(void)
{
    BOOL ret;
    DWORD cbCacheEntryInfo, cbRedirectUrl;
    INTERNET_CACHE_ENTRY_INFOA *lpCacheEntryInfo;

    SetLastError(0xdeadbeef);
    ret = GetUrlCacheEntryInfoExA(NULL, NULL, NULL, NULL, NULL, NULL, 0);
    ok(!ret, "GetUrlCacheEntryInfoEx with NULL URL and NULL args should have failed\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "GetUrlCacheEntryInfoEx with NULL URL and NULL args should have set last error to ERROR_INVALID_PARAMETER instead of %d\n", GetLastError());

    cbCacheEntryInfo = sizeof(INTERNET_CACHE_ENTRY_INFOA);
    SetLastError(0xdeadbeef);
    ret = GetUrlCacheEntryInfoExA("", NULL, &cbCacheEntryInfo, NULL, NULL, NULL, 0);
    ok(!ret, "GetUrlCacheEntryInfoEx with zero-length buffer should fail\n");
    ok(GetLastError() == ERROR_FILE_NOT_FOUND,
       "GetUrlCacheEntryInfoEx should have set last error to ERROR_FILE_NOT_FOUND instead of %d\n", GetLastError());

    ret = GetUrlCacheEntryInfoExA(test_url, NULL, NULL, NULL, NULL, NULL, 0);
    ok(ret, "GetUrlCacheEntryInfoEx with NULL args failed with error %d\n", GetLastError());

    cbCacheEntryInfo = 0;
    SetLastError(0xdeadbeef);
    ret = GetUrlCacheEntryInfoExA(test_url, NULL, &cbCacheEntryInfo, NULL, NULL, NULL, 0);
    ok(!ret, "GetUrlCacheEntryInfoEx with zero-length buffer should fail\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER,
       "GetUrlCacheEntryInfoEx should have set last error to ERROR_INSUFFICIENT_BUFFER instead of %d\n", GetLastError());

    lpCacheEntryInfo = HeapAlloc(GetProcessHeap(), 0, cbCacheEntryInfo);

    SetLastError(0xdeadbeef);
    ret = GetUrlCacheEntryInfoExA(test_url, NULL, NULL, NULL, NULL, NULL, 0x200 /*GET_INSTALLED_ENTRY*/);
    ok(ret == ie10_cache, "GetUrlCacheEntryInfoEx returned %x\n", ret);
    if (!ret) ok(GetLastError() == ERROR_FILE_NOT_FOUND,
            "GetUrlCacheEntryInfoEx should have set last error to ERROR_FILE_NOT_FOUND instead of %d\n", GetLastError());

    /* Unicode version of function seems to ignore 0x200 flag */
    ret = GetUrlCacheEntryInfoExW(test_urlW, NULL, NULL, NULL, NULL, NULL, 0x200 /*GET_INSTALLED_ENTRY*/);
    ok(ret || broken(old_ie && !ret), "GetUrlCacheEntryInfoExW failed with error %d\n", GetLastError());

    ret = GetUrlCacheEntryInfoExA(test_url, lpCacheEntryInfo, &cbCacheEntryInfo, NULL, NULL, NULL, 0);
    ok(ret, "GetUrlCacheEntryInfoEx failed with error %d\n", GetLastError());

    if (ret) check_cache_entry_infoA("GetUrlCacheEntryInfoEx", lpCacheEntryInfo);

    lpCacheEntryInfo->CacheEntryType |= 0x10000000; /* INSTALLED_CACHE_ENTRY */
    ret = SetUrlCacheEntryInfoA(test_url, lpCacheEntryInfo, CACHE_ENTRY_ATTRIBUTE_FC);
    ok(ret, "SetUrlCacheEntryInfoA failed with error %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = GetUrlCacheEntryInfoExA(test_url, NULL, NULL, NULL, NULL, NULL, 0x200 /*GET_INSTALLED_ENTRY*/);
    ok(ret, "GetUrlCacheEntryInfoEx failed with error %d\n", GetLastError());

    cbCacheEntryInfo = 100000;
    SetLastError(0xdeadbeef);
    ret = GetUrlCacheEntryInfoExA(test_url, NULL, &cbCacheEntryInfo, NULL, NULL, NULL, 0);
    ok(!ret, "GetUrlCacheEntryInfoEx with zero-length buffer should fail\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "GetUrlCacheEntryInfoEx should have set last error to ERROR_INSUFFICIENT_BUFFER instead of %d\n", GetLastError());

    HeapFree(GetProcessHeap(), 0, lpCacheEntryInfo);

    /* Querying the redirect URL fails with ERROR_INVALID_PARAMETER */
    SetLastError(0xdeadbeef);
    ret = GetUrlCacheEntryInfoExA(test_url, NULL, NULL, NULL, &cbRedirectUrl, NULL, 0);
    ok(!ret, "GetUrlCacheEntryInfoEx should have failed\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
    SetLastError(0xdeadbeef);
    ret = GetUrlCacheEntryInfoExA(test_url, NULL, &cbCacheEntryInfo, NULL, &cbRedirectUrl, NULL, 0);
    ok(!ret, "GetUrlCacheEntryInfoEx should have failed\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
}