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
struct TYPE_5__ {scalar_t__ QOS; scalar_t__ AuthInfo; struct TYPE_5__* CookieAuth; struct TYPE_5__* NetworkOptions; int /*<<< orphan*/  Protseq; int /*<<< orphan*/  NetworkAddr; int /*<<< orphan*/  Endpoint; scalar_t__ Assoc; int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ RpcBinding ;
typedef  int /*<<< orphan*/  RPC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPCRT4_strfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  RpcAssoc_Release (scalar_t__) ; 
 int /*<<< orphan*/  RpcAuthInfo_Release (scalar_t__) ; 
 int /*<<< orphan*/  RpcQualityOfService_Release (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 

RPC_STATUS RPCRT4_ReleaseBinding(RpcBinding* Binding)
{
  if (InterlockedDecrement(&Binding->refs))
    return RPC_S_OK;

  TRACE("binding: %p\n", Binding);
  if (Binding->Assoc) RpcAssoc_Release(Binding->Assoc);
  RPCRT4_strfree(Binding->Endpoint);
  RPCRT4_strfree(Binding->NetworkAddr);
  RPCRT4_strfree(Binding->Protseq);
  HeapFree(GetProcessHeap(), 0, Binding->NetworkOptions);
  HeapFree(GetProcessHeap(), 0, Binding->CookieAuth);
  if (Binding->AuthInfo) RpcAuthInfo_Release(Binding->AuthInfo);
  if (Binding->QOS) RpcQualityOfService_Release(Binding->QOS);
  HeapFree(GetProcessHeap(), 0, Binding);
  return RPC_S_OK;
}