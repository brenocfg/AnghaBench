#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* ops; int /*<<< orphan*/  server; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* open_connection_client ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ RpcConnection ;
typedef  int /*<<< orphan*/  RPC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

RPC_STATUS RPCRT4_OpenClientConnection(RpcConnection* Connection)
{
  TRACE("(Connection == ^%p)\n", Connection);

  assert(!Connection->server);
  return Connection->ops->open_connection_client(Connection);
}