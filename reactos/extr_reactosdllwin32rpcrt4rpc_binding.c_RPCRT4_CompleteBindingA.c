#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Assoc; int /*<<< orphan*/  NetworkOptions; void* Endpoint; void* NetworkAddr; int /*<<< orphan*/  Protseq; } ;
typedef  TYPE_1__ RpcBinding ;
typedef  scalar_t__ RPC_STATUS ;
typedef  char* LPCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RPCRT4_GetAssociation (int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* RPCRT4_strdupA (char*) ; 
 int /*<<< orphan*/  RPCRT4_strdupAtoW (char*) ; 
 int /*<<< orphan*/  RPCRT4_strfree (void*) ; 
 scalar_t__ RPC_S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 

__attribute__((used)) static RPC_STATUS RPCRT4_CompleteBindingA(RpcBinding* Binding, LPCSTR NetworkAddr,
                                          LPCSTR Endpoint, LPCSTR NetworkOptions)
{
  RPC_STATUS status;

  TRACE("(RpcBinding == ^%p, NetworkAddr == %s, EndPoint == %s, NetworkOptions == %s)\n", Binding,
   debugstr_a(NetworkAddr), debugstr_a(Endpoint), debugstr_a(NetworkOptions));

  RPCRT4_strfree(Binding->NetworkAddr);
  Binding->NetworkAddr = RPCRT4_strdupA(NetworkAddr);
  RPCRT4_strfree(Binding->Endpoint);
  Binding->Endpoint = RPCRT4_strdupA(Endpoint);
  HeapFree(GetProcessHeap(), 0, Binding->NetworkOptions);
  Binding->NetworkOptions = RPCRT4_strdupAtoW(NetworkOptions);

  /* only attempt to get an association if the binding is complete */
  if (Endpoint && Endpoint[0] != '\0')
  {
    status = RPCRT4_GetAssociation(Binding->Protseq, Binding->NetworkAddr,
                                   Binding->Endpoint, Binding->NetworkOptions,
                                   &Binding->Assoc);
    if (status != RPC_S_OK)
        return status;
  }

  return RPC_S_OK;
}