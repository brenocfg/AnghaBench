#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_15__ {scalar_t__ dwType; int /*<<< orphan*/  bPhysAddr; int /*<<< orphan*/  dwPhysAddrLen; int /*<<< orphan*/  dwIndex; } ;
struct TYPE_11__ {int /*<<< orphan*/  dwIndex; } ;
struct TYPE_14__ {int /*<<< orphan*/  recv_success; int /*<<< orphan*/  xmit_success; TYPE_1__ ipr; } ;
struct TYPE_13__ {int rev_major; int adapter_type; int max_sess_pkt_size; int /*<<< orphan*/  recv_success; int /*<<< orphan*/  xmit_success; int /*<<< orphan*/  adapter_address; } ;
struct TYPE_12__ {int ncb_length; char* ncb_callname; int /*<<< orphan*/  ncb_buffer; } ;
typedef  TYPE_2__* PNCB ;
typedef  TYPE_3__* PADAPTER_STATUS ;
typedef  TYPE_4__ NetBTAdapter ;
typedef  TYPE_5__ MIB_IFROW ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  ADAPTER_STATUS ;

/* Variables and functions */
 scalar_t__ GetIfEntry (TYPE_5__*) ; 
 scalar_t__ MIB_IF_TYPE_TOKENRING ; 
 scalar_t__ NO_ERROR ; 
 int /*<<< orphan*/  NRC_BADDR ; 
 int /*<<< orphan*/  NRC_BRIDGE ; 
 int /*<<< orphan*/  NRC_BUFLEN ; 
 int /*<<< orphan*/  NRC_ENVNOTDEF ; 
 int /*<<< orphan*/  NRC_GOODRET ; 
 int /*<<< orphan*/  NRC_INVADDRESS ; 
 int /*<<< orphan*/  NetBTAstatRemote (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  TRACE (char*,void*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static UCHAR NetBTAstat(void *adapt, PNCB ncb)
{
    NetBTAdapter *adapter = adapt;
    UCHAR ret;

    TRACE("adapt %p, NCB %p\n", adapt, ncb);

    if (!adapter) return NRC_ENVNOTDEF;
    if (!ncb) return NRC_INVADDRESS;
    if (!ncb->ncb_buffer) return NRC_BADDR;
    if (ncb->ncb_length < sizeof(ADAPTER_STATUS)) return NRC_BUFLEN;

    if (ncb->ncb_callname[0] == '*')
    {
        DWORD physAddrLen;
        MIB_IFROW ifRow;
        PADAPTER_STATUS astat = (PADAPTER_STATUS)ncb->ncb_buffer;
  
        memset(astat, 0, sizeof(ADAPTER_STATUS));
        astat->rev_major = 3;
        ifRow.dwIndex = adapter->ipr.dwIndex;
        if (GetIfEntry(&ifRow) != NO_ERROR)
            ret = NRC_BRIDGE;
        else
        {
            physAddrLen = min(ifRow.dwPhysAddrLen, 6);
            if (physAddrLen > 0)
                memcpy(astat->adapter_address, ifRow.bPhysAddr, physAddrLen);
            /* doubt anyone cares, but why not.. */
            if (ifRow.dwType == MIB_IF_TYPE_TOKENRING)
                astat->adapter_type = 0xff;
            else
                astat->adapter_type = 0xfe; /* for Ethernet */
            astat->max_sess_pkt_size = 0xffff;
            astat->xmit_success = adapter->xmit_success;
            astat->recv_success = adapter->recv_success;
            ret = NRC_GOODRET;
        }
    }
    else
        ret = NetBTAstatRemote(adapter, ncb);
    TRACE("returning 0x%02x\n", ret);
    return ret;
}