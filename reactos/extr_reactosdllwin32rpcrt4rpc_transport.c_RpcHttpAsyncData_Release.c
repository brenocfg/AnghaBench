#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_11__ {TYPE_2__* DebugInfo; } ;
struct TYPE_8__ {TYPE_3__* lpvBuffer; } ;
struct TYPE_10__ {TYPE_7__ cs; TYPE_1__ inet_buffers; int /*<<< orphan*/  completion_event; int /*<<< orphan*/  refs; } ;
struct TYPE_9__ {scalar_t__* Spare; } ;
typedef  TYPE_3__ RpcHttpAsyncData ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteCriticalSection (TYPE_7__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*) ; 

__attribute__((used)) static ULONG RpcHttpAsyncData_Release(RpcHttpAsyncData *data)
{
    ULONG refs = InterlockedDecrement(&data->refs);
    if (!refs)
    {
        TRACE("destroying async data %p\n", data);
        CloseHandle(data->completion_event);
        HeapFree(GetProcessHeap(), 0, data->inet_buffers.lpvBuffer);
        data->cs.DebugInfo->Spare[0] = 0;
        DeleteCriticalSection(&data->cs);
        HeapFree(GetProcessHeap(), 0, data);
    }
    return refs;
}