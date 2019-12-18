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
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ RetrieveUrlCacheEntryFileA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * test_url ; 

__attribute__((used)) static void test_RetrieveUrlCacheEntryA(void)
{
    BOOL ret;
    DWORD cbCacheEntryInfo;

    cbCacheEntryInfo = 0;
    SetLastError(0xdeadbeef);
    ret = RetrieveUrlCacheEntryFileA(NULL, NULL, &cbCacheEntryInfo, 0);
    ok(!ret, "RetrieveUrlCacheEntryFile should have failed\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "RetrieveUrlCacheEntryFile should have set last error to ERROR_INVALID_PARAMETER instead of %d\n", GetLastError());

    if (0)
    {
        /* Crashes on Win9x, NT4 and W2K */
        SetLastError(0xdeadbeef);
        ret = RetrieveUrlCacheEntryFileA(test_url, NULL, NULL, 0);
        ok(!ret, "RetrieveUrlCacheEntryFile should have failed\n");
        ok(GetLastError() == ERROR_INVALID_PARAMETER, "RetrieveUrlCacheEntryFile should have set last error to ERROR_INVALID_PARAMETER instead of %d\n", GetLastError());
    }

    SetLastError(0xdeadbeef);
    cbCacheEntryInfo = 100000;
    ret = RetrieveUrlCacheEntryFileA(NULL, NULL, &cbCacheEntryInfo, 0);
    ok(!ret, "RetrieveUrlCacheEntryFile should have failed\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "RetrieveUrlCacheEntryFile should have set last error to ERROR_INVALID_PARAMETER instead of %d\n", GetLastError());
}