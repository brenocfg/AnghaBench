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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  RpcPktHdr ;
typedef  int /*<<< orphan*/  RpcPktBindHdr ;
typedef  int /*<<< orphan*/  RpcConnection ;
typedef  scalar_t__ RPC_STATUS ;
typedef  int /*<<< orphan*/  RPC_MESSAGE ;

/* Variables and functions */
 scalar_t__ ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  RPCRT4_FreeHeader (int /*<<< orphan*/ *) ; 
 scalar_t__ RPCRT4_SendWithAuth (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ RPC_S_OK ; 
 int /*<<< orphan*/ * handle_bind_error (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ process_bind_packet_no_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,unsigned char**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static RPC_STATUS process_bind_packet(RpcConnection *conn, RpcPktBindHdr *hdr,
                                      RPC_MESSAGE *msg,
                                      unsigned char *auth_data,
                                      ULONG auth_length)
{
    RPC_STATUS status;
    RpcPktHdr *response = NULL;
    unsigned char *auth_data_out = NULL;
    ULONG auth_length_out = 0;

    status = process_bind_packet_no_send(conn, hdr, msg, auth_data, auth_length,
                                         &response, &auth_data_out,
                                         &auth_length_out);
    if (status != RPC_S_OK)
        response = handle_bind_error(conn, status);
    if (response)
        status = RPCRT4_SendWithAuth(conn, response, NULL, 0, auth_data_out, auth_length_out);
    else
        status = ERROR_OUTOFMEMORY;
    RPCRT4_FreeHeader(response);

    return status;
}