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
typedef  int /*<<< orphan*/  RpcConnection ;
typedef  scalar_t__ RPC_STATUS ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 unsigned char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  NDR_LOCAL_DATA_REPRESENTATION ; 
 int /*<<< orphan*/ * RPCRT4_BuildAuthHeader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPCRT4_FreeHeader (int /*<<< orphan*/ *) ; 
 scalar_t__ RPCRT4_SendWithAuth (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 scalar_t__ RPC_S_OUT_OF_RESOURCES ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rpcrt4_conn_authorize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,unsigned int*) ; 

RPC_STATUS RPCRT4_ClientConnectionAuth(RpcConnection* conn, BYTE *challenge,
                                       ULONG count)
{
  RpcPktHdr *resp_hdr;
  RPC_STATUS status;
  unsigned char *out_buffer;
  unsigned int out_len = 0;

  TRACE("challenge %s, %d bytes\n", challenge, count);

  status = rpcrt4_conn_authorize(conn, FALSE, challenge, count, NULL, &out_len);
  if (status) return status;
  out_buffer = HeapAlloc(GetProcessHeap(), 0, out_len);
  if (!out_buffer) return RPC_S_OUT_OF_RESOURCES;
  status = rpcrt4_conn_authorize(conn, FALSE, challenge, count, out_buffer, &out_len);
  if (status) return status;

  resp_hdr = RPCRT4_BuildAuthHeader(NDR_LOCAL_DATA_REPRESENTATION);

  if (resp_hdr)
    status = RPCRT4_SendWithAuth(conn, resp_hdr, NULL, 0, out_buffer, out_len);
  else
    status = RPC_S_OUT_OF_RESOURCES;

  HeapFree(GetProcessHeap(), 0, out_buffer);
  RPCRT4_FreeHeader(resp_hdr);

  return status;
}