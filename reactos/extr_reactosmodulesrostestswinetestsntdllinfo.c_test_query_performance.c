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
typedef  int /*<<< orphan*/  ULONGLONG ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  SYSTEM_PERFORMANCE_INFORMATION ;
typedef  scalar_t__ NTSTATUS ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ STATUS_INFO_LENGTH_MISMATCH ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  SystemPerformanceInformation ; 
 scalar_t__ is_wow64 ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pNtQuerySystemInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static void test_query_performance(void)
{
    NTSTATUS status;
    ULONG ReturnLength;
    ULONGLONG buffer[sizeof(SYSTEM_PERFORMANCE_INFORMATION)/sizeof(ULONGLONG) + 5];
    DWORD size = sizeof(SYSTEM_PERFORMANCE_INFORMATION);

    status = pNtQuerySystemInformation(SystemPerformanceInformation, buffer, 0, &ReturnLength);
    ok( status == STATUS_INFO_LENGTH_MISMATCH, "Expected STATUS_INFO_LENGTH_MISMATCH, got %08x\n", status);

    status = pNtQuerySystemInformation(SystemPerformanceInformation, buffer, size, &ReturnLength);
    if (status == STATUS_INFO_LENGTH_MISMATCH && is_wow64)
    {
        /* size is larger on wow64 under w2k8/win7 */
        size += 16;
        status = pNtQuerySystemInformation(SystemPerformanceInformation, buffer, size, &ReturnLength);
    }
    ok( status == STATUS_SUCCESS, "Expected STATUS_SUCCESS, got %08x\n", status);
    ok( ReturnLength == size, "Inconsistent length %d\n", ReturnLength);

    status = pNtQuerySystemInformation(SystemPerformanceInformation, buffer, size + 2, &ReturnLength);
    ok( status == STATUS_SUCCESS, "Expected STATUS_SUCCESS, got %08x\n", status);
    ok( ReturnLength == size || ReturnLength == size + 2,
        "Inconsistent length %d\n", ReturnLength);

    /* Not return values yet, as struct members are unknown */
}