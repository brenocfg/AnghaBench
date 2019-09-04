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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  TimeStamp ;
struct TYPE_7__ {unsigned int auth_type; int /*<<< orphan*/  auth_context_id; int /*<<< orphan*/  auth_level; } ;
struct TYPE_6__ {int /*<<< orphan*/ * AuthInfo; int /*<<< orphan*/  auth_context_id; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ RpcConnection ;
typedef  TYPE_2__ RpcAuthVerifier ;
typedef  scalar_t__ RPC_STATUS ;
typedef  int /*<<< orphan*/  CredHandle ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteSecurityContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (char*,unsigned int) ; 
 int /*<<< orphan*/  FreeCredentialsHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 unsigned char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 scalar_t__ RPCRT4_ServerGetRegisteredAuthInfo (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ RPC_S_OK ; 
 scalar_t__ RPC_S_OUT_OF_RESOURCES ; 
 scalar_t__ RPC_S_PROTOCOL_ERROR ; 
 scalar_t__ RPC_S_SEC_PKG_ERROR ; 
 scalar_t__ RpcAuthInfo_Create (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  RpcAuthInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SecInvalidateHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ SecIsValidHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ rpcrt4_conn_authorize (TYPE_1__*,scalar_t__,unsigned char*,int,unsigned char*,unsigned int*) ; 

RPC_STATUS RPCRT4_ServerConnectionAuth(RpcConnection* conn,
                                       BOOL start,
                                       RpcAuthVerifier *auth_data_in,
                                       ULONG auth_length_in,
                                       unsigned char **auth_data_out,
                                       ULONG *auth_length_out)
{
    unsigned char *out_buffer;
    unsigned int out_size;
    RPC_STATUS status;

    if (start)
    {
        /* remove any existing authentication information */
        if (conn->AuthInfo)
        {
            RpcAuthInfo_Release(conn->AuthInfo);
            conn->AuthInfo = NULL;
        }
        if (SecIsValidHandle(&conn->ctx))
        {
            DeleteSecurityContext(&conn->ctx);
            SecInvalidateHandle(&conn->ctx);
        }
        if (auth_length_in >= sizeof(RpcAuthVerifier))
        {
            CredHandle cred;
            TimeStamp exp;
            ULONG max_token;

            status = RPCRT4_ServerGetRegisteredAuthInfo(
                auth_data_in->auth_type, &cred, &exp, &max_token);
            if (status != RPC_S_OK)
            {
                ERR("unknown authentication service %u\n", auth_data_in->auth_type);
                return status;
            }

            status = RpcAuthInfo_Create(auth_data_in->auth_level,
                                        auth_data_in->auth_type, cred, exp,
                                        max_token, NULL, &conn->AuthInfo);
            if (status != RPC_S_OK)
            {
                FreeCredentialsHandle(&cred);
                return status;
            }

            /* FIXME: should auth_data_in->auth_context_id be checked in the !start case? */
            conn->auth_context_id = auth_data_in->auth_context_id;
        }
    }

    if (auth_length_in < sizeof(RpcAuthVerifier))
        return RPC_S_OK;

    if (!conn->AuthInfo)
        /* should have filled in authentication info by now */
        return RPC_S_PROTOCOL_ERROR;

    status = rpcrt4_conn_authorize(
        conn, start, (unsigned char *)(auth_data_in + 1),
        auth_length_in - sizeof(RpcAuthVerifier), NULL, &out_size);
    if (status) return status;

    out_buffer = HeapAlloc(GetProcessHeap(), 0, out_size);
    if (!out_buffer) return RPC_S_OUT_OF_RESOURCES;

    status = rpcrt4_conn_authorize(
        conn, start, (unsigned char *)(auth_data_in + 1),
        auth_length_in - sizeof(RpcAuthVerifier), out_buffer, &out_size);
    if (status != RPC_S_OK)
    {
        HeapFree(GetProcessHeap(), 0, out_buffer);
        return status;
    }

    if (out_size && !auth_length_out)
    {
        ERR("expected authentication to be complete but SSP returned data of "
            "%u bytes to be sent back to client\n", out_size);
        HeapFree(GetProcessHeap(), 0, out_buffer);
        return RPC_S_SEC_PKG_ERROR;
    }
    else
    {
        *auth_data_out = out_buffer;
        *auth_length_out = out_size;
    }

    return status;
}