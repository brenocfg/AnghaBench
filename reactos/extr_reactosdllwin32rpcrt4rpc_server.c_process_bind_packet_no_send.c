#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_25__ {int BufferLength; TYPE_3__* Buffer; } ;
struct TYPE_19__ {int /*<<< orphan*/  SyntaxGUID; } ;
struct TYPE_24__ {scalar_t__ MaxTransmissionSize; int /*<<< orphan*/  Endpoint; TYPE_13__* server_binding; int /*<<< orphan*/  NetworkOptions; int /*<<< orphan*/  NetworkAddr; TYPE_11__ ActiveInterface; } ;
struct TYPE_23__ {size_t num_syntaxes; TYPE_11__ abstract_syntax; int /*<<< orphan*/ * transfer_syntaxes; } ;
struct TYPE_22__ {unsigned int num_elements; scalar_t__ max_tsize; int /*<<< orphan*/  assoc_gid; } ;
struct TYPE_21__ {int /*<<< orphan*/  transfer_syntax; int /*<<< orphan*/  reason; void* result; } ;
struct TYPE_20__ {TYPE_10__* Assoc; } ;
struct TYPE_18__ {int /*<<< orphan*/  assoc_group_id; } ;
typedef  int /*<<< orphan*/  RpcServerInterface ;
typedef  TYPE_1__ RpcResult ;
typedef  int /*<<< orphan*/  RpcPktHdr ;
typedef  TYPE_2__ RpcPktBindHdr ;
typedef  TYPE_3__ RpcContextElement ;
typedef  TYPE_4__ RpcConnection ;
typedef  int /*<<< orphan*/  RpcAuthVerifier ;
typedef  scalar_t__ RPC_STATUS ;
typedef  TYPE_5__ RPC_MESSAGE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int,unsigned int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  NDR_LOCAL_DATA_REPRESENTATION ; 
 int /*<<< orphan*/  REASON_ABSTRACT_SYNTAX_NOT_SUPPORTED ; 
 int /*<<< orphan*/  REASON_NONE ; 
 int /*<<< orphan*/  REASON_TRANSFER_SYNTAXES_NOT_SUPPORTED ; 
 void* RESULT_ACCEPT ; 
 void* RESULT_PROVIDER_REJECTION ; 
 int /*<<< orphan*/ * RPCRT4_BuildBindAckHeader (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,TYPE_1__*) ; 
 scalar_t__ RPCRT4_MakeBinding (TYPE_13__**,TYPE_4__*) ; 
 scalar_t__ RPCRT4_ServerConnectionAuth (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,unsigned char**,scalar_t__*) ; 
 int /*<<< orphan*/ * RPCRT4_find_interface (int /*<<< orphan*/ *,TYPE_11__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPCRT4_release_server_interface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPC_MAX_PACKET_SIZE ; 
 scalar_t__ RPC_MIN_PACKET_SIZE ; 
 scalar_t__ RPC_S_INVALID_BOUND ; 
 scalar_t__ RPC_S_OK ; 
 scalar_t__ RPC_S_OUT_OF_RESOURCES ; 
 scalar_t__ RpcServerAssoc_GetAssociation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_10__**) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UuidIsNil (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rpcrt4_conn_get_name (TYPE_4__*) ; 

__attribute__((used)) static RPC_STATUS process_bind_packet_no_send(
    RpcConnection *conn, RpcPktBindHdr *hdr, RPC_MESSAGE *msg,
    unsigned char *auth_data, ULONG auth_length, RpcPktHdr **ack_response,
    unsigned char **auth_data_out, ULONG *auth_length_out)
{
  RPC_STATUS status;
  RpcContextElement *ctxt_elem;
  unsigned int i;
  RpcResult *results;

  /* validate data */
  for (i = 0, ctxt_elem = msg->Buffer;
       i < hdr->num_elements;
       i++, ctxt_elem = (RpcContextElement *)&ctxt_elem->transfer_syntaxes[ctxt_elem->num_syntaxes])
  {
      if (((char *)ctxt_elem - (char *)msg->Buffer) > msg->BufferLength ||
          ((char *)&ctxt_elem->transfer_syntaxes[ctxt_elem->num_syntaxes] - (char *)msg->Buffer) > msg->BufferLength)
      {
          ERR("inconsistent data in packet - packet length %d, num elements %d\n",
              msg->BufferLength, hdr->num_elements);
          return RPC_S_INVALID_BOUND;
      }
  }

  if (hdr->max_tsize < RPC_MIN_PACKET_SIZE ||
      !UuidIsNil(&conn->ActiveInterface.SyntaxGUID, &status) ||
      conn->server_binding)
  {
    TRACE("packet size less than min size, or active interface syntax guid non-null\n");

    return RPC_S_INVALID_BOUND;
  }

  results = HeapAlloc(GetProcessHeap(), 0,
                      hdr->num_elements * sizeof(*results));
  if (!results)
    return RPC_S_OUT_OF_RESOURCES;

  for (i = 0, ctxt_elem = (RpcContextElement *)msg->Buffer;
       i < hdr->num_elements;
       i++, ctxt_elem = (RpcContextElement *)&ctxt_elem->transfer_syntaxes[ctxt_elem->num_syntaxes])
  {
      RpcServerInterface* sif = NULL;
      unsigned int j;

      for (j = 0; !sif && j < ctxt_elem->num_syntaxes; j++)
      {
          sif = RPCRT4_find_interface(NULL, &ctxt_elem->abstract_syntax,
                                      &ctxt_elem->transfer_syntaxes[j], FALSE);
          if (sif)
              break;
      }
      if (sif)
      {
          RPCRT4_release_server_interface(sif);
          TRACE("accepting bind request on connection %p for %s\n", conn,
                debugstr_guid(&ctxt_elem->abstract_syntax.SyntaxGUID));
          results[i].result = RESULT_ACCEPT;
          results[i].reason = REASON_NONE;
          results[i].transfer_syntax = ctxt_elem->transfer_syntaxes[j];

          /* save the interface for later use */
          /* FIXME: save linked list */
          conn->ActiveInterface = ctxt_elem->abstract_syntax;
      }
      else if ((sif = RPCRT4_find_interface(NULL, &ctxt_elem->abstract_syntax,
                                            NULL, FALSE)) != NULL)
      {
          RPCRT4_release_server_interface(sif);
          TRACE("not accepting bind request on connection %p for %s - no transfer syntaxes supported\n",
                conn, debugstr_guid(&ctxt_elem->abstract_syntax.SyntaxGUID));
          results[i].result = RESULT_PROVIDER_REJECTION;
          results[i].reason = REASON_TRANSFER_SYNTAXES_NOT_SUPPORTED;
          memset(&results[i].transfer_syntax, 0, sizeof(results[i].transfer_syntax));
      }
      else
      {
          TRACE("not accepting bind request on connection %p for %s - abstract syntax not supported\n",
                conn, debugstr_guid(&ctxt_elem->abstract_syntax.SyntaxGUID));
          results[i].result = RESULT_PROVIDER_REJECTION;
          results[i].reason = REASON_ABSTRACT_SYNTAX_NOT_SUPPORTED;
          memset(&results[i].transfer_syntax, 0, sizeof(results[i].transfer_syntax));
      }
  }

  /* create temporary binding */
  status = RPCRT4_MakeBinding(&conn->server_binding, conn);
  if (status != RPC_S_OK)
  {
      HeapFree(GetProcessHeap(), 0, results);
      return status;
  }

  status = RpcServerAssoc_GetAssociation(rpcrt4_conn_get_name(conn),
                                         conn->NetworkAddr, conn->Endpoint,
                                         conn->NetworkOptions,
                                         hdr->assoc_gid,
                                         &conn->server_binding->Assoc);
  if (status != RPC_S_OK)
  {
      HeapFree(GetProcessHeap(), 0, results);
      return status;
  }

  if (auth_length)
  {
      status = RPCRT4_ServerConnectionAuth(conn, TRUE,
                                           (RpcAuthVerifier *)auth_data,
                                           auth_length, auth_data_out,
                                           auth_length_out);
      if (status != RPC_S_OK)
      {
          HeapFree(GetProcessHeap(), 0, results);
          return status;
      }
  }

  *ack_response = RPCRT4_BuildBindAckHeader(NDR_LOCAL_DATA_REPRESENTATION,
                                            RPC_MAX_PACKET_SIZE,
                                            RPC_MAX_PACKET_SIZE,
                                            conn->server_binding->Assoc->assoc_group_id,
                                            conn->Endpoint, hdr->num_elements,
                                            results);
  HeapFree(GetProcessHeap(), 0, results);

  if (*ack_response)
      conn->MaxTransmissionSize = hdr->max_tsize;
  else
      status = RPC_S_OUT_OF_RESOURCES;

  return status;
}