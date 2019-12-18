#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int ULONGLONG ;
struct TYPE_12__ {int LowPart; int HighPart; } ;
struct TYPE_13__ {int QuadPart; TYPE_1__ u; } ;
typedef  TYPE_2__ ULARGE_INTEGER ;
struct TYPE_15__ {int dwLowDateTime; int dwHighDateTime; } ;
struct TYPE_11__ {int dwLowDateTime; int dwHighDateTime; } ;
struct TYPE_14__ {TYPE_10__ LastModifiedTime; TYPE_10__ ExpireTime; } ;
typedef  TYPE_3__ INTERNET_CACHE_ENTRY_INFOA ;
typedef  TYPE_4__ FILETIME ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_ENTRY_EXPTIME_FC ; 
 int /*<<< orphan*/  CACHE_ENTRY_MODTIME_FC ; 
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetSystemTimeAsFileTime (TYPE_10__*) ; 
 int /*<<< orphan*/  GetUrlCacheEntryInfoA (char const*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  IsUrlCacheEntryExpiredA (char const*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  SetUrlCacheEntryInfoA (char const*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ie10_cache ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 char const* test_url ; 

__attribute__((used)) static void test_IsUrlCacheEntryExpiredA(void)
{
    static const char uncached_url[] =
        "What's the airspeed velocity of an unladen swallow?";
    BOOL ret;
    FILETIME ft;
    DWORD size;
    INTERNET_CACHE_ENTRY_INFOA *info;
    ULARGE_INTEGER exp_time;

    /* The function returns TRUE when the output time is NULL or the tested URL
     * is NULL.
     */
    ret = IsUrlCacheEntryExpiredA(NULL, 0, NULL);
    ok(ret != ie10_cache, "IsUrlCacheEntryExpiredA returned %x\n", ret);
    ft.dwLowDateTime = 0xdeadbeef;
    ft.dwHighDateTime = 0xbaadf00d;
    ret = IsUrlCacheEntryExpiredA(NULL, 0, &ft);
    ok(ret != ie10_cache, "IsUrlCacheEntryExpiredA returned %x\n", ret);
    ok(ft.dwLowDateTime == 0xdeadbeef && ft.dwHighDateTime == 0xbaadf00d,
       "expected time to be unchanged, got (%u,%u)\n",
       ft.dwLowDateTime, ft.dwHighDateTime);
    ret = IsUrlCacheEntryExpiredA(test_url, 0, NULL);
    ok(ret != ie10_cache, "IsUrlCacheEntryExpiredA returned %x\n", ret);

    /* The return value should indicate whether the URL is expired,
     * and the filetime indicates the last modified time, but a cache entry
     * with a zero expire time is "not expired".
     */
    ft.dwLowDateTime = 0xdeadbeef;
    ft.dwHighDateTime = 0xbaadf00d;
    ret = IsUrlCacheEntryExpiredA(test_url, 0, &ft);
    ok(!ret, "expected FALSE\n");
    ok(!ft.dwLowDateTime && !ft.dwHighDateTime,
       "expected time (0,0), got (%u,%u)\n",
       ft.dwLowDateTime, ft.dwHighDateTime);

    /* Same behavior with bogus flags. */
    ft.dwLowDateTime = 0xdeadbeef;
    ft.dwHighDateTime = 0xbaadf00d;
    ret = IsUrlCacheEntryExpiredA(test_url, 0xffffffff, &ft);
    ok(!ret, "expected FALSE\n");
    ok(!ft.dwLowDateTime && !ft.dwHighDateTime,
       "expected time (0,0), got (%u,%u)\n",
       ft.dwLowDateTime, ft.dwHighDateTime);

    /* Set the expire time to a point in the past.. */
    ret = GetUrlCacheEntryInfoA(test_url, NULL, &size);
    ok(!ret, "GetUrlCacheEntryInfo should have failed\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER,
       "expected ERROR_INSUFFICIENT_BUFFER, got %d\n", GetLastError());
    info = HeapAlloc(GetProcessHeap(), 0, size);
    ret = GetUrlCacheEntryInfoA(test_url, info, &size);
    ok(ret, "GetUrlCacheEntryInfo failed: %d\n", GetLastError());
    GetSystemTimeAsFileTime(&info->ExpireTime);
    exp_time.u.LowPart = info->ExpireTime.dwLowDateTime;
    exp_time.u.HighPart = info->ExpireTime.dwHighDateTime;
    exp_time.QuadPart -= 10 * 60 * (ULONGLONG)10000000;
    info->ExpireTime.dwLowDateTime = exp_time.u.LowPart;
    info->ExpireTime.dwHighDateTime = exp_time.u.HighPart;
    ret = SetUrlCacheEntryInfoA(test_url, info, CACHE_ENTRY_EXPTIME_FC);
    ok(ret, "SetUrlCacheEntryInfo failed: %d\n", GetLastError());
    ft.dwLowDateTime = 0xdeadbeef;
    ft.dwHighDateTime = 0xbaadf00d;
    /* and the entry should be expired. */
    ret = IsUrlCacheEntryExpiredA(test_url, 0, &ft);
    ok(ret, "expected TRUE\n");
    /* The modified time returned is 0. */
    ok(!ft.dwLowDateTime && !ft.dwHighDateTime,
       "expected time (0,0), got (%u,%u)\n",
       ft.dwLowDateTime, ft.dwHighDateTime);
    /* Set the expire time to a point in the future.. */
    exp_time.QuadPart += 20 * 60 * (ULONGLONG)10000000;
    info->ExpireTime.dwLowDateTime = exp_time.u.LowPart;
    info->ExpireTime.dwHighDateTime = exp_time.u.HighPart;
    ret = SetUrlCacheEntryInfoA(test_url, info, CACHE_ENTRY_EXPTIME_FC);
    ok(ret, "SetUrlCacheEntryInfo failed: %d\n", GetLastError());
    ft.dwLowDateTime = 0xdeadbeef;
    ft.dwHighDateTime = 0xbaadf00d;
    /* and the entry should no longer be expired. */
    ret = IsUrlCacheEntryExpiredA(test_url, 0, &ft);
    ok(!ret, "expected FALSE\n");
    /* The modified time returned is still 0. */
    ok(!ft.dwLowDateTime && !ft.dwHighDateTime,
       "expected time (0,0), got (%u,%u)\n",
       ft.dwLowDateTime, ft.dwHighDateTime);
    /* Set the modified time... */
    GetSystemTimeAsFileTime(&info->LastModifiedTime);
    ret = SetUrlCacheEntryInfoA(test_url, info, CACHE_ENTRY_MODTIME_FC);
    ok(ret, "SetUrlCacheEntryInfo failed: %d\n", GetLastError());
    /* and the entry should still be unexpired.. */
    ret = IsUrlCacheEntryExpiredA(test_url, 0, &ft);
    ok(!ret, "expected FALSE\n");
    /* but the modified time returned is the last modified time just set. */
    ok(ft.dwLowDateTime == info->LastModifiedTime.dwLowDateTime &&
       ft.dwHighDateTime == info->LastModifiedTime.dwHighDateTime,
       "expected time (%u,%u), got (%u,%u)\n",
       info->LastModifiedTime.dwLowDateTime,
       info->LastModifiedTime.dwHighDateTime,
       ft.dwLowDateTime, ft.dwHighDateTime);
    HeapFree(GetProcessHeap(), 0, info);

    /* An uncached URL is implicitly expired, but with unknown time. */
    ft.dwLowDateTime = 0xdeadbeef;
    ft.dwHighDateTime = 0xbaadf00d;
    ret = IsUrlCacheEntryExpiredA(uncached_url, 0, &ft);
    ok(ret != ie10_cache, "IsUrlCacheEntryExpiredA returned %x\n", ret);
    ok(!ft.dwLowDateTime && !ft.dwHighDateTime,
       "expected time (0,0), got (%u,%u)\n",
       ft.dwLowDateTime, ft.dwHighDateTime);
}