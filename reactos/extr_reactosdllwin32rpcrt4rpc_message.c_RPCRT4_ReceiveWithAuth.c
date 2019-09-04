#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_18__ {int ptype; scalar_t__ frag_len; scalar_t__ auth_len; unsigned short flags; } ;
struct TYPE_17__ {scalar_t__ BufferLength; int /*<<< orphan*/ * Buffer; } ;
struct TYPE_15__ {scalar_t__ alloc_hint; } ;
struct TYPE_14__ {scalar_t__ alloc_hint; } ;
struct TYPE_16__ {TYPE_7__ common; TYPE_2__ request; TYPE_1__ response; } ;
typedef  TYPE_3__ RpcPktHdr ;
typedef  int /*<<< orphan*/  RpcConnection ;
typedef  int /*<<< orphan*/  RpcAuthVerifier ;
typedef  scalar_t__ RPC_STATUS ;
typedef  TYPE_4__* PRPC_MESSAGE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 unsigned char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * I_RpcAllocate (scalar_t__) ; 
 int /*<<< orphan*/  I_RpcFree (int /*<<< orphan*/ *) ; 
 scalar_t__ I_RpcReAllocateBuffer (TYPE_4__*) ; 
#define  PKT_REQUEST 129 
#define  PKT_RESPONSE 128 
 int /*<<< orphan*/  RPCRT4_FreeHeader (TYPE_3__*) ; 
 scalar_t__ RPCRT4_GetHeaderSize (TYPE_3__*) ; 
 int /*<<< orphan*/  RPCRT4_SetThreadCurrentConnection (int /*<<< orphan*/ *) ; 
 scalar_t__ RPCRT4_receive_fragment (int /*<<< orphan*/ *,TYPE_3__**,void**) ; 
 unsigned int RPC_AUTH_VERIFIER_LEN (TYPE_7__*) ; 
 unsigned short RPC_FLG_FIRST ; 
 int RPC_FLG_LAST ; 
 scalar_t__ RPC_S_OK ; 
 scalar_t__ RPC_S_OUT_OF_RESOURCES ; 
 scalar_t__ RPC_S_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  SECURE_PACKET_RECEIVE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*,unsigned int,...) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  packet_does_auth_negotiation (TYPE_3__*) ; 
 scalar_t__ rpcrt4_conn_is_authorized (int /*<<< orphan*/ *) ; 
 scalar_t__ rpcrt4_conn_secure_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,scalar_t__,unsigned char*,scalar_t__,int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 

RPC_STATUS RPCRT4_ReceiveWithAuth(RpcConnection *Connection, RpcPktHdr **Header,
                                  PRPC_MESSAGE pMsg,
                                  unsigned char **auth_data_out,
                                  ULONG *auth_length_out)
{
  RPC_STATUS status;
  DWORD hdr_length;
  unsigned short first_flag;
  ULONG data_length;
  ULONG buffer_length;
  ULONG auth_length = 0;
  unsigned char *auth_data = NULL;
  RpcPktHdr *CurrentHeader = NULL;
  void *payload = NULL;

  *Header = NULL;
  pMsg->Buffer = NULL;
  if (auth_data_out) *auth_data_out = NULL;
  if (auth_length_out) *auth_length_out = 0;

  TRACE("(%p, %p, %p, %p)\n", Connection, Header, pMsg, auth_data_out);

  RPCRT4_SetThreadCurrentConnection(Connection);

  status = RPCRT4_receive_fragment(Connection, Header, &payload);
  if (status != RPC_S_OK) goto fail;

  hdr_length = RPCRT4_GetHeaderSize(*Header);

  /* read packet body */
  switch ((*Header)->common.ptype) {
  case PKT_RESPONSE:
    pMsg->BufferLength = (*Header)->response.alloc_hint;
    break;
  case PKT_REQUEST:
    pMsg->BufferLength = (*Header)->request.alloc_hint;
    break;
  default:
    pMsg->BufferLength = (*Header)->common.frag_len - hdr_length - RPC_AUTH_VERIFIER_LEN(&(*Header)->common);
  }

  TRACE("buffer length = %u\n", pMsg->BufferLength);

  pMsg->Buffer = I_RpcAllocate(pMsg->BufferLength);
  if (!pMsg->Buffer)
  {
    status = ERROR_OUTOFMEMORY;
    goto fail;
  }

  first_flag = RPC_FLG_FIRST;
  auth_length = (*Header)->common.auth_len;
  if (auth_length) {
    auth_data = HeapAlloc(GetProcessHeap(), 0, RPC_AUTH_VERIFIER_LEN(&(*Header)->common));
    if (!auth_data) {
      status = RPC_S_OUT_OF_RESOURCES;
      goto fail;
    }
  }
  CurrentHeader = *Header;
  buffer_length = 0;
  while (TRUE)
  {
    unsigned int header_auth_len = RPC_AUTH_VERIFIER_LEN(&CurrentHeader->common);

    /* verify header fields */

    if ((CurrentHeader->common.frag_len < hdr_length) ||
        (CurrentHeader->common.frag_len - hdr_length < header_auth_len)) {
      WARN("frag_len %d too small for hdr_length %d and auth_len %d\n",
        CurrentHeader->common.frag_len, hdr_length, CurrentHeader->common.auth_len);
      status = RPC_S_PROTOCOL_ERROR;
      goto fail;
    }

    if (CurrentHeader->common.auth_len != auth_length) {
      WARN("auth_len header field changed from %d to %d\n",
        auth_length, CurrentHeader->common.auth_len);
      status = RPC_S_PROTOCOL_ERROR;
      goto fail;
    }

    if ((CurrentHeader->common.flags & RPC_FLG_FIRST) != first_flag) {
      TRACE("invalid packet flags\n");
      status = RPC_S_PROTOCOL_ERROR;
      goto fail;
    }

    data_length = CurrentHeader->common.frag_len - hdr_length - header_auth_len;
    if (data_length + buffer_length > pMsg->BufferLength) {
      TRACE("allocation hint exceeded, new buffer length = %d\n",
        data_length + buffer_length);
      pMsg->BufferLength = data_length + buffer_length;
      status = I_RpcReAllocateBuffer(pMsg);
      if (status != RPC_S_OK) goto fail;
    }

    memcpy((unsigned char *)pMsg->Buffer + buffer_length, payload, data_length);

    if (header_auth_len) {
      if (header_auth_len < sizeof(RpcAuthVerifier) ||
          header_auth_len > RPC_AUTH_VERIFIER_LEN(&(*Header)->common)) {
        WARN("bad auth verifier length %d\n", header_auth_len);
        status = RPC_S_PROTOCOL_ERROR;
        goto fail;
      }

      /* FIXME: we should accumulate authentication data for the bind,
       * bind_ack, alter_context and alter_context_response if necessary.
       * however, the details of how this is done is very sketchy in the
       * DCE/RPC spec. for all other packet types that have authentication
       * verifier data then it is just duplicated in all the fragments */
      memcpy(auth_data, (unsigned char *)payload + data_length, header_auth_len);

      /* these packets are handled specially, not by the generic SecurePacket
       * function */
      if (!packet_does_auth_negotiation(*Header) && rpcrt4_conn_is_authorized(Connection))
      {
        status = rpcrt4_conn_secure_packet(Connection, SECURE_PACKET_RECEIVE,
            CurrentHeader, hdr_length,
            (unsigned char *)pMsg->Buffer + buffer_length, data_length,
            (RpcAuthVerifier *)auth_data,
            auth_data + sizeof(RpcAuthVerifier),
            header_auth_len - sizeof(RpcAuthVerifier));
        if (status != RPC_S_OK) goto fail;
      }
    }

    buffer_length += data_length;
    if (!(CurrentHeader->common.flags & RPC_FLG_LAST)) {
      TRACE("next header\n");

      if (*Header != CurrentHeader)
      {
          RPCRT4_FreeHeader(CurrentHeader);
          CurrentHeader = NULL;
      }
      HeapFree(GetProcessHeap(), 0, payload);
      payload = NULL;

      status = RPCRT4_receive_fragment(Connection, &CurrentHeader, &payload);
      if (status != RPC_S_OK) goto fail;

      first_flag = 0;
    } else {
      break;
    }
  }
  pMsg->BufferLength = buffer_length;

  /* success */
  status = RPC_S_OK;

fail:
  RPCRT4_SetThreadCurrentConnection(NULL);
  if (CurrentHeader != *Header)
    RPCRT4_FreeHeader(CurrentHeader);
  if (status != RPC_S_OK) {
    I_RpcFree(pMsg->Buffer);
    pMsg->Buffer = NULL;
    RPCRT4_FreeHeader(*Header);
    *Header = NULL;
  }
  if (auth_data_out && status == RPC_S_OK) {
    *auth_length_out = auth_length;
    *auth_data_out = auth_data;
  }
  else
    HeapFree(GetProcessHeap(), 0, auth_data);
  HeapFree(GetProcessHeap(), 0, payload);
  return status;
}