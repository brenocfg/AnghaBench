#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_18__ {scalar_t__ numAddresses; int /*<<< orphan*/ * addresses; } ;
struct TYPE_13__ {int /*<<< orphan*/  dwAddr; } ;
struct TYPE_17__ {TYPE_1__ ipr; } ;
struct TYPE_16__ {TYPE_3__* source_addr; TYPE_3__* destination_addr; } ;
struct TYPE_15__ {int node_count; } ;
struct TYPE_14__ {int ncb_length; scalar_t__ ncb_buffer; } ;
typedef  scalar_t__ PUCHAR ;
typedef  TYPE_2__* PNCB ;
typedef  TYPE_3__* PFIND_NAME_HEADER ;
typedef  TYPE_4__* PFIND_NAME_BUFFER ;
typedef  TYPE_5__ NetBTAdapter ;
typedef  TYPE_6__ NBNameCacheEntry ;
typedef  int /*<<< orphan*/  FIND_NAME_HEADER ;
typedef  int /*<<< orphan*/  FIND_NAME_BUFFER ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  NRC_BADDR ; 
 int /*<<< orphan*/  NRC_BUFLEN ; 
 int /*<<< orphan*/  NRC_CMDTMO ; 
 int /*<<< orphan*/  NRC_ENVNOTDEF ; 
 int /*<<< orphan*/  NRC_GOODRET ; 
 int /*<<< orphan*/  NRC_INVADDRESS ; 
 int /*<<< orphan*/  NetBTInternalFindName (TYPE_5__*,TYPE_2__*,TYPE_6__ const**) ; 
 int /*<<< orphan*/  TRACE (char*,void*,...) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ min (int,scalar_t__) ; 

__attribute__((used)) static UCHAR NetBTFindName(void *adapt, PNCB ncb)
{
    NetBTAdapter *adapter = adapt;
    UCHAR ret;
    const NBNameCacheEntry *cacheEntry = NULL;
    PFIND_NAME_HEADER foundName;

    TRACE("adapt %p, NCB %p\n", adapt, ncb);

    if (!adapter) return NRC_ENVNOTDEF;
    if (!ncb) return NRC_INVADDRESS;
    if (!ncb->ncb_buffer) return NRC_BADDR;
    if (ncb->ncb_length < sizeof(FIND_NAME_HEADER)) return NRC_BUFLEN;

    foundName = (PFIND_NAME_HEADER)ncb->ncb_buffer;
    memset(foundName, 0, sizeof(FIND_NAME_HEADER));

    ret = NetBTInternalFindName(adapter, ncb, &cacheEntry);
    if (ret == NRC_GOODRET)
    {
        if (cacheEntry)
        {
            DWORD spaceFor = min((ncb->ncb_length - sizeof(FIND_NAME_HEADER)) /
             sizeof(FIND_NAME_BUFFER), cacheEntry->numAddresses);
            DWORD ndx;

            for (ndx = 0; ndx < spaceFor; ndx++)
            {
                PFIND_NAME_BUFFER findNameBuffer;

                findNameBuffer =
                 (PFIND_NAME_BUFFER)((PUCHAR)foundName +
                 sizeof(FIND_NAME_HEADER) + foundName->node_count *
                 sizeof(FIND_NAME_BUFFER));
                memset(findNameBuffer->destination_addr, 0, 2);
                memcpy(findNameBuffer->destination_addr + 2,
                 &adapter->ipr.dwAddr, sizeof(DWORD));
                memset(findNameBuffer->source_addr, 0, 2);
                memcpy(findNameBuffer->source_addr + 2,
                 &cacheEntry->addresses[ndx], sizeof(DWORD));
                foundName->node_count++;
            }
            if (spaceFor < cacheEntry->numAddresses)
                ret = NRC_BUFLEN;
        }
        else
            ret = NRC_CMDTMO;
    }
    TRACE("returning 0x%02x\n", ret);
    return ret;
}