#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UUID ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_9__ {unsigned short opnum; scalar_t__ context_id; int /*<<< orphan*/  alloc_hint; } ;
struct TYPE_7__ {int frag_len; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {TYPE_3__ request; TYPE_1__ common; } ;
typedef  TYPE_2__ RpcPktHdr ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PKT_REQUEST ; 
 int /*<<< orphan*/  RPCRT4_BuildCommonHeader (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_FLG_OBJECT_UUID ; 
 int /*<<< orphan*/  UuidIsNil (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static RpcPktHdr *RPCRT4_BuildRequestHeader(ULONG DataRepresentation,
                                     ULONG BufferLength,
                                     unsigned short ProcNum,
                                     UUID *ObjectUuid)
{
  RpcPktHdr *header;
  BOOL has_object;
  RPC_STATUS status;

  has_object = (ObjectUuid != NULL && !UuidIsNil(ObjectUuid, &status));
  header = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                     sizeof(header->request) + (has_object ? sizeof(UUID) : 0));
  if (header == NULL) {
    return NULL;
  }

  RPCRT4_BuildCommonHeader(header, PKT_REQUEST, DataRepresentation);
  header->common.frag_len = sizeof(header->request);
  header->request.alloc_hint = BufferLength;
  header->request.context_id = 0;
  header->request.opnum = ProcNum;
  if (has_object) {
    header->common.flags |= RPC_FLG_OBJECT_UUID;
    header->common.frag_len += sizeof(UUID);
    memcpy(&header->request + 1, ObjectUuid, sizeof(UUID));
  }

  return header;
}