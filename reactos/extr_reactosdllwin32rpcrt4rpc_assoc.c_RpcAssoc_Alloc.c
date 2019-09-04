#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* DebugInfo; } ;
struct TYPE_7__ {int refs; int /*<<< orphan*/  entry; int /*<<< orphan*/  http_uuid; scalar_t__ connection_cnt; scalar_t__ assoc_group_id; int /*<<< orphan*/ * NetworkOptions; void* Endpoint; void* NetworkAddr; void* Protseq; TYPE_4__ cs; int /*<<< orphan*/  context_handle_list; int /*<<< orphan*/  free_connection_pool; } ;
struct TYPE_6__ {scalar_t__* Spare; } ;
typedef  TYPE_2__ RpcAssoc ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_4__*) ; 
 void* RPCRT4_strdupA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RPCRT4_strdupW (scalar_t__) ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  RPC_S_OUT_OF_RESOURCES ; 
 int /*<<< orphan*/  UuidCreate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static RPC_STATUS RpcAssoc_Alloc(LPCSTR Protseq, LPCSTR NetworkAddr,
                                 LPCSTR Endpoint, LPCWSTR NetworkOptions,
                                 RpcAssoc **assoc_out)
{
    RpcAssoc *assoc;
    assoc = HeapAlloc(GetProcessHeap(), 0, sizeof(*assoc));
    if (!assoc)
        return RPC_S_OUT_OF_RESOURCES;
    assoc->refs = 1;
    list_init(&assoc->free_connection_pool);
    list_init(&assoc->context_handle_list);
    InitializeCriticalSection(&assoc->cs);
    assoc->cs.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": RpcAssoc.cs");
    assoc->Protseq = RPCRT4_strdupA(Protseq);
    assoc->NetworkAddr = RPCRT4_strdupA(NetworkAddr);
    assoc->Endpoint = RPCRT4_strdupA(Endpoint);
    assoc->NetworkOptions = NetworkOptions ? RPCRT4_strdupW(NetworkOptions) : NULL;
    assoc->assoc_group_id = 0;
    assoc->connection_cnt = 0;
    UuidCreate(&assoc->http_uuid);
    list_init(&assoc->entry);
    *assoc_out = assoc;
    return RPC_S_OK;
}