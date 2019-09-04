#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sbi ;
typedef  int ULONG ;
struct TYPE_3__ {int NumberOfProcessors; } ;
typedef  TYPE_1__ SYSTEM_BASIC_INFORMATION ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 scalar_t__ STATUS_ACCESS_VIOLATION ; 
 scalar_t__ STATUS_INFO_LENGTH_MISMATCH ; 
 scalar_t__ STATUS_INVALID_INFO_CLASS ; 
 scalar_t__ STATUS_INVALID_PARAMETER ; 
 scalar_t__ STATUS_NOT_IMPLEMENTED ; 
 scalar_t__ STATUS_SUCCESS ; 
 int SystemBasicInformation ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 scalar_t__ pNtQuerySystemInformation (int,TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  trace (char*,...) ; 

__attribute__((used)) static void test_query_basic(void)
{
    NTSTATUS status;
    ULONG ReturnLength;
    SYSTEM_BASIC_INFORMATION sbi;

    /* This test also covers some basic parameter testing that should be the same for 
     * every information class
    */

    /* Use a nonexistent info class */
    trace("Check nonexistent info class\n");
    status = pNtQuerySystemInformation(-1, NULL, 0, NULL);
    ok( status == STATUS_INVALID_INFO_CLASS || status == STATUS_NOT_IMPLEMENTED /* vista */,
        "Expected STATUS_INVALID_INFO_CLASS or STATUS_NOT_IMPLEMENTED, got %08x\n", status);

    /* Use an existing class but with a zero-length buffer */
    trace("Check zero-length buffer\n");
    status = pNtQuerySystemInformation(SystemBasicInformation, NULL, 0, NULL);
    ok( status == STATUS_INFO_LENGTH_MISMATCH, "Expected STATUS_INFO_LENGTH_MISMATCH, got %08x\n", status);

    /* Use an existing class, correct length but no SystemInformation buffer */
    trace("Check no SystemInformation buffer\n");
    status = pNtQuerySystemInformation(SystemBasicInformation, NULL, sizeof(sbi), NULL);
    ok( status == STATUS_ACCESS_VIOLATION || status == STATUS_INVALID_PARAMETER /* vista */,
        "Expected STATUS_ACCESS_VIOLATION or STATUS_INVALID_PARAMETER, got %08x\n", status);

    /* Use an existing class, correct length, a pointer to a buffer but no ReturnLength pointer */
    trace("Check no ReturnLength pointer\n");
    status = pNtQuerySystemInformation(SystemBasicInformation, &sbi, sizeof(sbi), NULL);
    ok( status == STATUS_SUCCESS, "Expected STATUS_SUCCESS, got %08x\n", status);

    /* Check a too large buffer size */
    trace("Check a too large buffer size\n");
    status = pNtQuerySystemInformation(SystemBasicInformation, &sbi, sizeof(sbi) * 2, &ReturnLength);
    ok( status == STATUS_INFO_LENGTH_MISMATCH, "Expected STATUS_INFO_LENGTH_MISMATCH, got %08x\n", status);

    /* Finally some correct calls */
    trace("Check with correct parameters\n");
    status = pNtQuerySystemInformation(SystemBasicInformation, &sbi, sizeof(sbi), &ReturnLength);
    ok( status == STATUS_SUCCESS, "Expected STATUS_SUCCESS, got %08x\n", status);
    ok( sizeof(sbi) == ReturnLength, "Inconsistent length %d\n", ReturnLength);

    /* Check if we have some return values */
    trace("Number of Processors : %d\n", sbi.NumberOfProcessors);
    ok( sbi.NumberOfProcessors > 0, "Expected more than 0 processors, got %d\n", sbi.NumberOfProcessors);
}