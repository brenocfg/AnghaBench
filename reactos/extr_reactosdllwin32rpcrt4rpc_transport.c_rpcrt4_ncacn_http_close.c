#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * servername; scalar_t__ cancel_event; int /*<<< orphan*/  async_data; int /*<<< orphan*/ * session; int /*<<< orphan*/ * app_info; int /*<<< orphan*/ * out_request; int /*<<< orphan*/ * in_request; int /*<<< orphan*/  timer_cancelled; } ;
typedef  TYPE_1__ RpcConnection_http ;
typedef  int /*<<< orphan*/  RpcConnection ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InternetCloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RpcHttpAsyncData_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 

__attribute__((used)) static int rpcrt4_ncacn_http_close(RpcConnection *Connection)
{
  RpcConnection_http *httpc = (RpcConnection_http *) Connection;

  TRACE("\n");

  SetEvent(httpc->timer_cancelled);
  if (httpc->in_request)
    InternetCloseHandle(httpc->in_request);
  httpc->in_request = NULL;
  if (httpc->out_request)
    InternetCloseHandle(httpc->out_request);
  httpc->out_request = NULL;
  if (httpc->app_info)
    InternetCloseHandle(httpc->app_info);
  httpc->app_info = NULL;
  if (httpc->session)
    InternetCloseHandle(httpc->session);
  httpc->session = NULL;
  RpcHttpAsyncData_Release(httpc->async_data);
  if (httpc->cancel_event)
    CloseHandle(httpc->cancel_event);
  HeapFree(GetProcessHeap(), 0, httpc->servername);
  httpc->servername = NULL;

  return 0;
}