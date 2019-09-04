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
typedef  int /*<<< orphan*/  sti ;
typedef  int ULONG ;
typedef  int NTSTATUS ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int STATUS_INFO_LENGTH_MISMATCH ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  SystemTimeOfDayInformation ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pNtQuerySystemInformation (int /*<<< orphan*/ ,struct _SYSTEM_TIMEOFDAY_INFORMATION_PRIVATE*,int,int*) ; 
 int /*<<< orphan*/  trace (char*,...) ; 

__attribute__((used)) static void test_query_timeofday(void)
{
    NTSTATUS status;
    ULONG ReturnLength;

    /* Copy of our winternl.h structure turned into a private one */
    typedef struct _SYSTEM_TIMEOFDAY_INFORMATION_PRIVATE {
        LARGE_INTEGER liKeBootTime;
        LARGE_INTEGER liKeSystemTime;
        LARGE_INTEGER liExpTimeZoneBias;
        ULONG uCurrentTimeZoneId;
        DWORD dwUnknown1[5];
    } SYSTEM_TIMEOFDAY_INFORMATION_PRIVATE;

    SYSTEM_TIMEOFDAY_INFORMATION_PRIVATE sti;
  
    /*  The struct size for NT (32 bytes) and Win2K/XP (48 bytes) differ.
     *
     *  Windows 2000 and XP return STATUS_INFO_LENGTH_MISMATCH if the given buffer size is greater
     *  then 48 and 0 otherwise
     *  Windows NT returns STATUS_INFO_LENGTH_MISMATCH when the given buffer size is not correct
     *  and 0 otherwise
     *
     *  Windows 2000 and XP copy the given buffer size into the provided buffer, if the return code is STATUS_SUCCESS
     *  NT only fills the buffer if the return code is STATUS_SUCCESS
     *
    */

    status = pNtQuerySystemInformation(SystemTimeOfDayInformation, &sti, sizeof(sti), &ReturnLength);

    if (status == STATUS_INFO_LENGTH_MISMATCH)
    {
        trace("Windows version is NT, we have to cater for differences with W2K/WinXP\n");
 
        status = pNtQuerySystemInformation(SystemTimeOfDayInformation, &sti, 0, &ReturnLength);
        ok( status == STATUS_INFO_LENGTH_MISMATCH, "Expected STATUS_INFO_LENGTH_MISMATCH, got %08x\n", status);
        ok( 0 == ReturnLength, "ReturnLength should be 0, it is (%d)\n", ReturnLength);

        sti.uCurrentTimeZoneId = 0xdeadbeef;
        status = pNtQuerySystemInformation(SystemTimeOfDayInformation, &sti, 28, &ReturnLength);
        ok(status == STATUS_SUCCESS || broken(status == STATUS_INFO_LENGTH_MISMATCH /* NT4 */), "Expected STATUS_SUCCESS, got %08x\n", status);
        ok( 0xdeadbeef == sti.uCurrentTimeZoneId, "This part of the buffer should not have been filled\n");

        status = pNtQuerySystemInformation(SystemTimeOfDayInformation, &sti, 32, &ReturnLength);
        ok( status == STATUS_SUCCESS, "Expected STATUS_SUCCESS, got %08x\n", status);
        ok( 32 == ReturnLength, "ReturnLength should be 0, it is (%d)\n", ReturnLength);
    }
    else
    {
        status = pNtQuerySystemInformation(SystemTimeOfDayInformation, &sti, 0, &ReturnLength);
        ok( status == STATUS_SUCCESS, "Expected STATUS_SUCCESS, got %08x\n", status);
        ok( 0 == ReturnLength, "ReturnLength should be 0, it is (%d)\n", ReturnLength);

        sti.uCurrentTimeZoneId = 0xdeadbeef;
        status = pNtQuerySystemInformation(SystemTimeOfDayInformation, &sti, 24, &ReturnLength);
        ok( status == STATUS_SUCCESS, "Expected STATUS_SUCCESS, got %08x\n", status);
        ok( 24 == ReturnLength, "ReturnLength should be 24, it is (%d)\n", ReturnLength);
        ok( 0xdeadbeef == sti.uCurrentTimeZoneId, "This part of the buffer should not have been filled\n");
    
        sti.uCurrentTimeZoneId = 0xdeadbeef;
        status = pNtQuerySystemInformation(SystemTimeOfDayInformation, &sti, 32, &ReturnLength);
        ok( status == STATUS_SUCCESS, "Expected STATUS_SUCCESS, got %08x\n", status);
        ok( 32 == ReturnLength, "ReturnLength should be 32, it is (%d)\n", ReturnLength);
        ok( 0xdeadbeef != sti.uCurrentTimeZoneId, "Buffer should have been partially filled\n");
    
        status = pNtQuerySystemInformation(SystemTimeOfDayInformation, &sti, 49, &ReturnLength);
        ok( status == STATUS_INFO_LENGTH_MISMATCH, "Expected STATUS_INFO_LENGTH_MISMATCH, got %08x\n", status);
        ok( ReturnLength == 0 || ReturnLength == sizeof(sti) /* vista */,
            "ReturnLength should be 0, it is (%d)\n", ReturnLength);
    
        status = pNtQuerySystemInformation(SystemTimeOfDayInformation, &sti, sizeof(sti), &ReturnLength);
        ok( status == STATUS_SUCCESS, "Expected STATUS_SUCCESS, got %08x\n", status);
        ok( sizeof(sti) == ReturnLength, "Inconsistent length %d\n", ReturnLength);
    }

    /* Check if we have some return values */
    trace("uCurrentTimeZoneId : (%d)\n", sti.uCurrentTimeZoneId);
}