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
typedef  int /*<<< orphan*/  sci ;
typedef  int ULONG ;
struct TYPE_3__ {int FeatureSet; } ;
typedef  TYPE_1__ SYSTEM_CPU_INFORMATION ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  SystemCpuInformation ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 scalar_t__ pNtQuerySystemInformation (int /*<<< orphan*/ ,TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  trace (char*,int) ; 

__attribute__((used)) static void test_query_cpu(void)
{
    DWORD status;
    ULONG ReturnLength;
    SYSTEM_CPU_INFORMATION sci;

    status = pNtQuerySystemInformation(SystemCpuInformation, &sci, sizeof(sci), &ReturnLength);
    ok( status == STATUS_SUCCESS, "Expected STATUS_SUCCESS, got %08x\n", status);
    ok( sizeof(sci) == ReturnLength, "Inconsistent length %d\n", ReturnLength);

    /* Check if we have some return values */
    trace("Processor FeatureSet : %08x\n", sci.FeatureSet);
    ok( sci.FeatureSet != 0, "Expected some features for this processor, got %08x\n", sci.FeatureSet);
}