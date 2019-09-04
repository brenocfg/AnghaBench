#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_5__ {int /*<<< orphan*/  RtlHandle; } ;
typedef  int /*<<< orphan*/  RTL_HANDLE_TABLE ;
typedef  int /*<<< orphan*/  RTL_HANDLE ;
typedef  TYPE_1__* NTSTATUS ;
typedef  TYPE_1__ MY_HANDLE ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  RtlpMakeHandleAllocated (int /*<<< orphan*/ *) ; 
 TYPE_1__* STATUS_SUCCESS ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pRtlAllocateHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* pRtlDestroyHandleTable (int /*<<< orphan*/ *) ; 
 int pRtlFreeHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pRtlInitializeHandleTable (int,int,int /*<<< orphan*/ *) ; 
 int pRtlIsValidIndexHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_HandleTables(void)
{
    BOOLEAN result;
    NTSTATUS status;
    ULONG Index;
    MY_HANDLE * MyHandle;
    RTL_HANDLE_TABLE HandleTable;

    if (!pRtlInitializeHandleTable)
    {
        win_skip("RtlInitializeHandleTable is not available\n");
        return;
    }

    pRtlInitializeHandleTable(0x3FFF, sizeof(MY_HANDLE), &HandleTable);
    MyHandle = (MY_HANDLE *)pRtlAllocateHandle(&HandleTable, &Index);
    ok(MyHandle != NULL, "RtlAllocateHandle failed\n");
    RtlpMakeHandleAllocated(&MyHandle->RtlHandle);
    MyHandle = NULL;
    result = pRtlIsValidIndexHandle(&HandleTable, Index, (RTL_HANDLE **)&MyHandle);
    ok(result, "Handle %p wasn't valid\n", MyHandle);
    result = pRtlFreeHandle(&HandleTable, &MyHandle->RtlHandle);
    ok(result, "Couldn't free handle %p\n", MyHandle);
    status = pRtlDestroyHandleTable(&HandleTable);
    ok(status == STATUS_SUCCESS, "RtlDestroyHandleTable failed with error 0x%08x\n", status);
}