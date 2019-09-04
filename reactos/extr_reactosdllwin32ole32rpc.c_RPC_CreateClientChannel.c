#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int refs; TYPE_3__ IRpcChannelBuffer_iface; void* dest_context_data; int /*<<< orphan*/  dest_context; } ;
struct TYPE_11__ {TYPE_1__ super; int /*<<< orphan*/  iid; int /*<<< orphan*/ * event; int /*<<< orphan*/  server_pid; int /*<<< orphan*/  oxid; int /*<<< orphan*/  bind; } ;
struct TYPE_9__ {int /*<<< orphan*/  dwPid; } ;
typedef  scalar_t__ RPC_STATUS ;
typedef  int /*<<< orphan*/  RPC_BINDING_HANDLE ;
typedef  TYPE_2__ OXID_INFO ;
typedef  int /*<<< orphan*/  OXID ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  TYPE_3__ IRpcChannelBuffer ;
typedef  int /*<<< orphan*/  IPID ;
typedef  int /*<<< orphan*/  IID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_4__ ClientRpcChannelBuffer ;
typedef  int /*<<< orphan*/  APARTMENT ;

/* Variables and functions */
 int /*<<< orphan*/  ClientRpcChannelBufferVtbl ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (scalar_t__) ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ RPC_S_OK ; 
 int /*<<< orphan*/  RpcBindingFree (int /*<<< orphan*/ *) ; 
 scalar_t__ RpcBindingFromStringBindingW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RpcBindingSetObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RpcStringBindingComposeW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RpcStringFreeW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apartment_getoxid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_rpc_endpoint (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wszRpcTransport ; 

HRESULT RPC_CreateClientChannel(const OXID *oxid, const IPID *ipid,
                                const OXID_INFO *oxid_info, const IID *iid,
                                DWORD dest_context, void *dest_context_data,
                                IRpcChannelBuffer **chan, APARTMENT *apt)
{
    ClientRpcChannelBuffer *This;
    WCHAR                   endpoint[200];
    RPC_BINDING_HANDLE      bind;
    RPC_STATUS              status;
    LPWSTR                  string_binding;

    /* FIXME: get the endpoint from oxid_info->psa instead */
    get_rpc_endpoint(endpoint, oxid);

    TRACE("proxy pipe: connecting to endpoint: %s\n", debugstr_w(endpoint));

    status = RpcStringBindingComposeW(
        NULL,
        wszRpcTransport,
        NULL,
        endpoint,
        NULL,
        &string_binding);
        
    if (status == RPC_S_OK)
    {
        status = RpcBindingFromStringBindingW(string_binding, &bind);

        if (status == RPC_S_OK)
        {
            IPID ipid2 = *ipid; /* why can't RpcBindingSetObject take a const? */
            status = RpcBindingSetObject(bind, &ipid2);
            if (status != RPC_S_OK)
                RpcBindingFree(&bind);
        }

        RpcStringFreeW(&string_binding);
    }

    if (status != RPC_S_OK)
    {
        ERR("Couldn't get binding for endpoint %s, status = %d\n", debugstr_w(endpoint), status);
        return HRESULT_FROM_WIN32(status);
    }

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(*This));
    if (!This)
    {
        RpcBindingFree(&bind);
        return E_OUTOFMEMORY;
    }

    This->super.IRpcChannelBuffer_iface.lpVtbl = &ClientRpcChannelBufferVtbl;
    This->super.refs = 1;
    This->super.dest_context = dest_context;
    This->super.dest_context_data = dest_context_data;
    This->bind = bind;
    apartment_getoxid(apt, &This->oxid);
    This->server_pid = oxid_info->dwPid;
    This->event = NULL;
    This->iid = *iid;

    *chan = &This->super.IRpcChannelBuffer_iface;

    return S_OK;
}