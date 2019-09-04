#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int refs; TYPE_2__ IRpcChannelBuffer_iface; void* dest_context_data; int /*<<< orphan*/  dest_context; } ;
typedef  TYPE_1__ RpcChannelBuffer ;
typedef  TYPE_2__ IRpcChannelBuffer ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  ServerRpcChannelBufferVtbl ; 

HRESULT RPC_CreateServerChannel(DWORD dest_context, void *dest_context_data, IRpcChannelBuffer **chan)
{
    RpcChannelBuffer *This = HeapAlloc(GetProcessHeap(), 0, sizeof(*This));
    if (!This)
        return E_OUTOFMEMORY;

    This->IRpcChannelBuffer_iface.lpVtbl = &ServerRpcChannelBufferVtbl;
    This->refs = 1;
    This->dest_context = dest_context;
    This->dest_context_data = dest_context_data;
    
    *chan = &This->IRpcChannelBuffer_iface;

    return S_OK;
}