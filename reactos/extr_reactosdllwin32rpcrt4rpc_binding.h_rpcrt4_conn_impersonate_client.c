#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* impersonate_client ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ RpcConnection ;
typedef  int /*<<< orphan*/  RPC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static inline RPC_STATUS rpcrt4_conn_impersonate_client(
    RpcConnection *conn)
{
    return conn->ops->impersonate_client(conn);
}