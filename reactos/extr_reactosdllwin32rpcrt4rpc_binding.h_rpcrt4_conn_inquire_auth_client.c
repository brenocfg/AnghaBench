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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* inquire_auth_client ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ RpcConnection ;
typedef  int /*<<< orphan*/  RPC_WSTR ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  int /*<<< orphan*/  RPC_AUTHZ_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline RPC_STATUS rpcrt4_conn_inquire_auth_client(
    RpcConnection *conn, RPC_AUTHZ_HANDLE *privs, RPC_WSTR *server_princ_name,
    ULONG *authn_level, ULONG *authn_svc, ULONG *authz_svc, ULONG flags)
{
    return conn->ops->inquire_auth_client(conn, privs, server_princ_name, authn_level, authn_svc, authz_svc, flags);
}