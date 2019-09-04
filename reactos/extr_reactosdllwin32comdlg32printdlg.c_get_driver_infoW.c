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
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  DRIVER_INFO_3W ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetPrinterDriverW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 

__attribute__((used)) static DRIVER_INFO_3W * get_driver_infoW(HANDLE hprn)
{
    DRIVER_INFO_3W *di3 = NULL;
    DWORD needed = 0;
    BOOL res;

    res = GetPrinterDriverW(hprn, NULL, 3, NULL, 0, &needed);
    if (!res && (GetLastError() == ERROR_INSUFFICIENT_BUFFER)) {
        di3 = HeapAlloc(GetProcessHeap(), 0, needed);
        res = GetPrinterDriverW(hprn, NULL, 3, (LPBYTE)di3, needed, &needed);
    }

    if (res)
        return di3;

    TRACE("GetPrinterDriverW failed with %u\n", GetLastError());
    HeapFree(GetProcessHeap(), 0, di3);
    return NULL;
}