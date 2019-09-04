#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* DebugInfo; } ;
struct TYPE_7__ {int dwStructSize; } ;
struct TYPE_10__ {int refs; TYPE_5__ cs; TYPE_1__ inet_buffers; } ;
struct TYPE_9__ {int /*<<< orphan*/  common; TYPE_4__* async_data; int /*<<< orphan*/  cancel_event; } ;
struct TYPE_8__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/  RpcHttpAsyncData ;
typedef  TYPE_3__ RpcConnection_http ;
typedef  int /*<<< orphan*/  RpcConnection ;
typedef  int /*<<< orphan*/  INTERNET_BUFFERSW ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_5__*) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_4__*) ; 

__attribute__((used)) static RpcConnection *rpcrt4_ncacn_http_alloc(void)
{
    RpcConnection_http *httpc;
    httpc = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*httpc));
    if (!httpc) return NULL;
    httpc->async_data = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(RpcHttpAsyncData));
    if (!httpc->async_data)
    {
        HeapFree(GetProcessHeap(), 0, httpc);
        return NULL;
    }
    TRACE("async data = %p\n", httpc->async_data);
    httpc->cancel_event = CreateEventW(NULL, FALSE, FALSE, NULL);
    httpc->async_data->refs = 1;
    httpc->async_data->inet_buffers.dwStructSize = sizeof(INTERNET_BUFFERSW);
    InitializeCriticalSection(&httpc->async_data->cs);
    httpc->async_data->cs.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": RpcHttpAsyncData.cs");
    return &httpc->common;
}