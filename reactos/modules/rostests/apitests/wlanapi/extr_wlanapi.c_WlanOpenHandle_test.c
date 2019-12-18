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
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SERVICE_EXISTS ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  WlanCloseHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ WlanOpenHandle (int,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void WlanOpenHandle_test(void)
{
    DWORD ret;
    DWORD dwNegotiatedVersion;
    HANDLE hClientHandle;

    /* correct call to determine if WlanSvc is running */
    ret = WlanOpenHandle(1, NULL, &dwNegotiatedVersion, &hClientHandle);
    if (ret == ERROR_SERVICE_EXISTS)
    {
        skip("Skipping wlanapi tests, WlanSvc is not running\n");
        return;
    }
    ok(ret == ERROR_SUCCESS, "WlanOpenHandle failed, error %ld\n", ret);
    WlanCloseHandle(hClientHandle, NULL);

    /* invalid pdwNegotiatedVersion */
    ret = WlanOpenHandle(1, NULL, NULL, &hClientHandle);
    ok(ret == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %ld\n", GetLastError());

    /* invalid hClientHandle */
    ret = WlanOpenHandle(1, NULL, &dwNegotiatedVersion, NULL);
    ok(ret == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %ld\n", GetLastError());

    /* invalid pReserved */
    ret = WlanOpenHandle(1, (PVOID) 1, &dwNegotiatedVersion, &hClientHandle);
    ok(ret == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %ld\n", GetLastError());
}