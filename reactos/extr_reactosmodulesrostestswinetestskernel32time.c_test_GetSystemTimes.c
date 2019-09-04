#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usertime ;
typedef  int /*<<< orphan*/  sbi ;
typedef  int /*<<< orphan*/  kerneltime ;
typedef  int /*<<< orphan*/  idletime ;
typedef  int ULONG ;
struct TYPE_18__ {int QuadPart; int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
typedef  TYPE_4__ ULARGE_INTEGER ;
struct TYPE_20__ {int /*<<< orphan*/  dwHighDateTime; int /*<<< orphan*/  dwLowDateTime; } ;
struct TYPE_17__ {int QuadPart; } ;
struct TYPE_16__ {int QuadPart; } ;
struct TYPE_15__ {int QuadPart; } ;
struct TYPE_19__ {int NumberOfProcessors; TYPE_3__ IdleTime; TYPE_2__ KernelTime; TYPE_1__ UserTime; } ;
typedef  TYPE_5__ SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION ;
typedef  TYPE_5__ SYSTEM_BASIC_INFORMATION ;
typedef  TYPE_7__ FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_5__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  NtQuerySystemInformation (int /*<<< orphan*/ ,TYPE_5__*,int,int*) ; 
 int /*<<< orphan*/  SystemBasicInformation ; 
 int /*<<< orphan*/  SystemProcessorPerformanceInformation ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pGetSystemTimes (TYPE_7__*,TYPE_7__*,TYPE_7__*) ; 
 int /*<<< orphan*/  trace (char*,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetSystemTimes(void)
{

    FILETIME idletime, kerneltime, usertime;
    int i;
    ULARGE_INTEGER ul1, ul2, ul3;
    SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION *sppi;
    SYSTEM_BASIC_INFORMATION sbi;
    ULONG ReturnLength;
    ULARGE_INTEGER total_usertime, total_kerneltime, total_idletime;

    if (!pGetSystemTimes)
    {
        win_skip("GetSystemTimes not available\n");
        return;
    }

    ok( pGetSystemTimes(NULL, NULL, NULL), "GetSystemTimes failed unexpectedly\n" );

    total_usertime.QuadPart = 0;
    total_kerneltime.QuadPart = 0;
    total_idletime.QuadPart = 0;
    memset( &idletime, 0x11, sizeof(idletime) );
    memset( &kerneltime, 0x11, sizeof(kerneltime) );
    memset( &usertime, 0x11, sizeof(usertime) );
    ok( pGetSystemTimes(&idletime, &kerneltime , &usertime),
        "GetSystemTimes failed unexpectedly\n" );

    ul1.LowPart = idletime.dwLowDateTime;
    ul1.HighPart = idletime.dwHighDateTime;
    ul2.LowPart = kerneltime.dwLowDateTime;
    ul2.HighPart = kerneltime.dwHighDateTime;
    ul3.LowPart = usertime.dwLowDateTime;
    ul3.HighPart = usertime.dwHighDateTime;

    ok( !NtQuerySystemInformation(SystemBasicInformation, &sbi, sizeof(sbi), &ReturnLength),
                                  "NtQuerySystemInformation failed\n" );
    ok( sizeof(sbi) == ReturnLength, "Inconsistent length %d\n", ReturnLength );

    /* Check if we have some return values */
    trace( "Number of Processors : %d\n", sbi.NumberOfProcessors );
    ok( sbi.NumberOfProcessors > 0, "Expected more than 0 processors, got %d\n",
        sbi.NumberOfProcessors );

    sppi = HeapAlloc( GetProcessHeap(), 0,
                      sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION) * sbi.NumberOfProcessors);

    ok( !NtQuerySystemInformation( SystemProcessorPerformanceInformation, sppi,
                                   sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION) * sbi.NumberOfProcessors,
                                   &ReturnLength),
                                   "NtQuerySystemInformation failed\n" );

    for (i = 0; i < sbi.NumberOfProcessors; i++)
    {
        total_usertime.QuadPart += sppi[i].UserTime.QuadPart;
        total_kerneltime.QuadPart += sppi[i].KernelTime.QuadPart;
        total_idletime.QuadPart += sppi[i].IdleTime.QuadPart;
    }

    ok( total_idletime.QuadPart - ul1.QuadPart < 10000000, "test idletime failed\n" );
    ok( total_kerneltime.QuadPart - ul2.QuadPart < 10000000, "test kerneltime failed\n" );
    ok( total_usertime.QuadPart - ul3.QuadPart < 10000000, "test usertime failed\n" );

    HeapFree(GetProcessHeap(), 0, sppi);
}