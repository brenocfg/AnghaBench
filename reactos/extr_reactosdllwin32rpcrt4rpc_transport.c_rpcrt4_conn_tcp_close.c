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
struct TYPE_2__ {int sock; int /*<<< orphan*/  cancel_event; int /*<<< orphan*/  sock_event; } ;
typedef  TYPE_1__ RpcConnection_tcp ;
typedef  int /*<<< orphan*/  RpcConnection ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  closesocket (int) ; 

__attribute__((used)) static int rpcrt4_conn_tcp_close(RpcConnection *conn)
{
    RpcConnection_tcp *connection = (RpcConnection_tcp *) conn;

    TRACE("%d\n", connection->sock);

    if (connection->sock != -1)
        closesocket(connection->sock);
    connection->sock = -1;
    CloseHandle(connection->sock_event);
    CloseHandle(connection->cancel_event);
    return 0;
}