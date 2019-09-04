#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  RpcConnection ;

/* Variables and functions */

__attribute__((used)) static int rpcrt4_conn_np_wait_for_incoming_data(RpcConnection *Connection)
{
    /* FIXME: implement when named pipe writes use overlapped I/O */
    return -1;
}