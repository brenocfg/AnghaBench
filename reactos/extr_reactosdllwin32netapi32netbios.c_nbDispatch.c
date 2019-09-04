#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int UCHAR ;
struct TYPE_24__ {int /*<<< orphan*/  data; } ;
struct TYPE_26__ {int /*<<< orphan*/  cmdQueue; TYPE_2__ impl; TYPE_1__* transport; } ;
struct TYPE_25__ {int ncb_command; } ;
struct TYPE_23__ {int (* findName ) (int /*<<< orphan*/ ,TYPE_3__*) ;} ;
typedef  TYPE_3__* PNCB ;
typedef  TYPE_4__ NetBIOSAdapter ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,TYPE_3__*,int) ; 
 int NBCmdQueueAdd (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  NBCmdQueueComplete (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
#define  NCBASTAT 136 
#define  NCBCALL 135 
#define  NCBCHAINSEND 134 
#define  NCBCHAINSENDNA 133 
#define  NCBFINDNAME 132 
#define  NCBHANGUP 131 
#define  NCBRECV 130 
 int NCBRESET ; 
#define  NCBSEND 129 
#define  NCBSENDNA 128 
 int NRC_BRIDGE ; 
 int NRC_GOODRET ; 
 int NRC_ILLCMD ; 
 int NRC_INVADDRESS ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int nbAStat (TYPE_4__*,TYPE_3__*) ; 
 int nbCall (TYPE_4__*,TYPE_3__*) ; 
 int nbHangup (TYPE_4__*,TYPE_3__*) ; 
 int nbRecv (TYPE_4__*,TYPE_3__*) ; 
 int nbReset (TYPE_4__*,TYPE_3__*) ; 
 int nbSend (TYPE_4__*,TYPE_3__*) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static UCHAR nbDispatch(NetBIOSAdapter *adapter, PNCB ncb)
{
    UCHAR ret, cmd;

    TRACE(": adapter %p, ncb %p\n", adapter, ncb);

    if (!adapter) return NRC_BRIDGE;
    if (!ncb) return NRC_INVADDRESS;

    cmd = ncb->ncb_command & 0x7f;
    if (cmd == NCBRESET)
        ret = nbReset(adapter, ncb);
    else
    {
        ret = NBCmdQueueAdd(adapter->cmdQueue, ncb);
        if (ret == NRC_GOODRET)
        {
            switch (cmd)
            {
                case NCBCALL:
                    ret = nbCall(adapter, ncb);
                    break;

                /* WinNT doesn't chain sends, it always sends immediately.
                 * Doubt there's any real significance to the NA variants.
                 */
                case NCBSEND:
                case NCBSENDNA:
                case NCBCHAINSEND:
                case NCBCHAINSENDNA:
                    ret = nbSend(adapter, ncb);
                    break;

                case NCBRECV:
                    ret = nbRecv(adapter, ncb);
                    break;

                case NCBHANGUP:
                    ret = nbHangup(adapter, ncb);
                    break;

                case NCBASTAT:
                    ret = nbAStat(adapter, ncb);
                    break;

                case NCBFINDNAME:
                    if (adapter->transport->findName)
                        ret = adapter->transport->findName(adapter->impl.data,
                         ncb);
                    else
                        ret = NRC_ILLCMD;
                    break;

                default:
                    FIXME("(%p): command code 0x%02x\n", ncb, ncb->ncb_command);
                    ret = NRC_ILLCMD;
            }
            NBCmdQueueComplete(adapter->cmdQueue, ncb, ret);
        }
    }
    TRACE("returning 0x%02x\n", ret);
    return ret;
}