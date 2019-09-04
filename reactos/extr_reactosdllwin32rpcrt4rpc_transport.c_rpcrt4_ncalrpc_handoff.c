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
struct TYPE_5__ {int /*<<< orphan*/  NetworkAddr; int /*<<< orphan*/  Endpoint; } ;
typedef  int /*<<< orphan*/  RpcConnection_np ;
typedef  TYPE_1__ RpcConnection ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetComputerNameA (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ MAX_COMPUTERNAME_LENGTH ; 
 int /*<<< orphan*/  RPC_S_OUT_OF_RESOURCES ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcrt4_conn_create_pipe (TYPE_1__*) ; 
 int /*<<< orphan*/  rpcrt4_conn_np_handoff (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static RPC_STATUS rpcrt4_ncalrpc_handoff(RpcConnection *old_conn, RpcConnection *new_conn)
{
  DWORD len = MAX_COMPUTERNAME_LENGTH + 1;
  RPC_STATUS status;

  TRACE("%s\n", old_conn->Endpoint);

  rpcrt4_conn_np_handoff((RpcConnection_np *)old_conn, (RpcConnection_np *)new_conn);
  status = rpcrt4_conn_create_pipe(old_conn);

  /* Store the local computer name as the NetworkAddr for ncalrpc. */
  new_conn->NetworkAddr = HeapAlloc(GetProcessHeap(), 0, len);
  if (!GetComputerNameA(new_conn->NetworkAddr, &len))
  {
    ERR("Failed to retrieve the computer name, error %u\n", GetLastError());
    return RPC_S_OUT_OF_RESOURCES;
  }

  return status;
}