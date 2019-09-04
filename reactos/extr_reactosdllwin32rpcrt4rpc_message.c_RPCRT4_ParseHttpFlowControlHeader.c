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
typedef  int /*<<< orphan*/  UUID ;
typedef  int ULONG ;
struct TYPE_4__ {int flags; int num_data_items; } ;
struct TYPE_5__ {TYPE_1__ http; } ;
typedef  TYPE_2__ RpcPktHdr ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 scalar_t__ GET_HTTP_PAYLOAD_FIELD_DATA (unsigned char*) ; 
 int READ_HTTP_PAYLOAD_FIELD_TYPE (unsigned char*) ; 
 unsigned char* RPCRT4_NextHttpHeaderField (unsigned char*) ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  RPC_S_PROTOCOL_ERROR ; 

RPC_STATUS RPCRT4_ParseHttpFlowControlHeader(RpcPktHdr *header,
                                             unsigned char *data, BOOL server,
                                             ULONG *bytes_transmitted,
                                             ULONG *flow_control_increment,
                                             UUID *pipe_uuid)
{
  ULONG type;
  if (header->http.flags != 0x2)
  {
    ERR("invalid flags 0x%x\n", header->http.flags);
    return RPC_S_PROTOCOL_ERROR;
  }
  if (header->http.num_data_items != 2)
  {
    ERR("invalid number of data items %d\n", header->http.num_data_items);
    return RPC_S_PROTOCOL_ERROR;
  }

  type = READ_HTTP_PAYLOAD_FIELD_TYPE(data);
  if (type != 0x0000000d)
  {
    ERR("invalid type for field 1: 0x%08x\n", type);
    return RPC_S_PROTOCOL_ERROR;
  }
  if (*(ULONG *)GET_HTTP_PAYLOAD_FIELD_DATA(data) != (server ? 0x3 : 0x0))
  {
    ERR("invalid type for 0xd field data: 0x%08x\n", *(ULONG *)GET_HTTP_PAYLOAD_FIELD_DATA(data));
    return RPC_S_PROTOCOL_ERROR;
  }
  data = RPCRT4_NextHttpHeaderField(data);

  type = READ_HTTP_PAYLOAD_FIELD_TYPE(data);
  if (type != 0x00000001)
  {
    ERR("invalid type for field 2: 0x%08x\n", type);
    return RPC_S_PROTOCOL_ERROR;
  }
  *bytes_transmitted = *(ULONG *)GET_HTTP_PAYLOAD_FIELD_DATA(data);
  *flow_control_increment = *(ULONG *)(GET_HTTP_PAYLOAD_FIELD_DATA(data) + 4);
  *pipe_uuid = *(UUID *)(GET_HTTP_PAYLOAD_FIELD_DATA(data) + 8);

  return RPC_S_OK;
}