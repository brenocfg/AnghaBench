#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_5__ {TYPE_1__* AuthInfo; } ;
struct TYPE_4__ {scalar_t__ AuthnSvc; scalar_t__ AuthnLevel; int /*<<< orphan*/  server_principal_name; } ;
typedef  TYPE_2__ RpcConnection ;
typedef  int /*<<< orphan*/  RPC_WSTR ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  int /*<<< orphan*/ * RPC_AUTHZ_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  RPCRT4_strdupW (int /*<<< orphan*/ ) ; 
 scalar_t__ RPC_C_AUTHZ_NONE ; 
 int /*<<< orphan*/  RPC_S_BINDING_HAS_NO_AUTH ; 
 int /*<<< orphan*/  RPC_S_OK ; 

RPC_STATUS RPCRT4_default_inquire_auth_client(
    RpcConnection *conn, RPC_AUTHZ_HANDLE *privs, RPC_WSTR *server_princ_name,
    ULONG *authn_level, ULONG *authn_svc, ULONG *authz_svc, ULONG flags)
{
    if (!conn->AuthInfo) return RPC_S_BINDING_HAS_NO_AUTH;

    if (privs)
    {
        FIXME("privs not implemented\n");
        *privs = NULL;
    }
    if (server_princ_name)
    {
        *server_princ_name = RPCRT4_strdupW(conn->AuthInfo->server_principal_name);
        if (!*server_princ_name) return ERROR_OUTOFMEMORY;
    }
    if (authn_level) *authn_level = conn->AuthInfo->AuthnLevel;
    if (authn_svc) *authn_svc = conn->AuthInfo->AuthnSvc;
    if (authz_svc)
    {
        FIXME("authorization service not implemented\n");
        *authz_svc = RPC_C_AUTHZ_NONE;
    }
    if (flags)
        FIXME("flags 0x%x not implemented\n", flags);

    return RPC_S_OK;
}