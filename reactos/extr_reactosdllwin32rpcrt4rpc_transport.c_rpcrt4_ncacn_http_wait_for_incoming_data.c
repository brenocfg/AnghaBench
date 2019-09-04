#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dwBufferLength; } ;
struct TYPE_7__ {TYPE_1__ inet_buffers; } ;
struct TYPE_6__ {int /*<<< orphan*/  cancel_event; TYPE_3__* async_data; int /*<<< orphan*/  out_request; } ;
typedef  TYPE_2__ RpcConnection_http ;
typedef  int /*<<< orphan*/  RpcConnection ;
typedef  scalar_t__ RPC_STATUS ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  IRF_ASYNC ; 
 int /*<<< orphan*/  InternetQueryDataAvailable (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RPC_S_OK ; 
 int /*<<< orphan*/  prepare_async_request (TYPE_3__*) ; 
 scalar_t__ wait_async_request (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpcrt4_ncacn_http_wait_for_incoming_data(RpcConnection *Connection)
{
  RpcConnection_http *httpc = (RpcConnection_http *) Connection;
  BOOL ret;
  RPC_STATUS status;

  prepare_async_request(httpc->async_data);
  ret = InternetQueryDataAvailable(httpc->out_request,
    &httpc->async_data->inet_buffers.dwBufferLength, IRF_ASYNC, 0);
  status = wait_async_request(httpc->async_data, ret, httpc->cancel_event);
  return status == RPC_S_OK ? 0 : -1;
}