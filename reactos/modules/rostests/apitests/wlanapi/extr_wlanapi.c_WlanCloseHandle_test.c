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
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ WlanCloseHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void WlanCloseHandle_test(void)
{
    DWORD ret;
    HANDLE hClientHandle = (HANDLE)(ULONG_PTR)0xdeadbeefdeadbeef;

    /* invalid pReserved */
    ret = WlanCloseHandle(hClientHandle, (PVOID) 1);
    ok(ret == ERROR_INVALID_PARAMETER, "expected failure\n");

    /* invalid hClientHandle */
    ret = WlanCloseHandle(NULL, NULL);
    ok(ret == ERROR_INVALID_PARAMETER, "expected failure\n");

    /* invalid hClientHandle */
    ret = WlanCloseHandle(hClientHandle, NULL);
    ok(ret == ERROR_INVALID_HANDLE, "expected failure\n");
}