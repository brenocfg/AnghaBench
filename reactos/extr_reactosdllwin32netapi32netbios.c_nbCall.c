#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UCHAR ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
struct TYPE_13__ {size_t sessionsLen; TYPE_3__* sessions; TYPE_2__ impl; TYPE_1__* transport; int /*<<< orphan*/  cs; } ;
struct TYPE_12__ {size_t ncb_lsn; int /*<<< orphan*/  ncb_callname; int /*<<< orphan*/  ncb_name; } ;
struct TYPE_11__ {scalar_t__ state; scalar_t__ inUse; int /*<<< orphan*/  data; int /*<<< orphan*/  remote_name; int /*<<< orphan*/  local_name; } ;
struct TYPE_9__ {size_t (* call ) (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_4__* PNCB ;
typedef  TYPE_5__ NetBIOSAdapter ;

/* Variables and functions */
 scalar_t__ CALL_PENDING ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NCBNAMSZ ; 
 size_t NRC_BRIDGE ; 
 size_t NRC_ENVNOTDEF ; 
 size_t NRC_GOODRET ; 
 size_t NRC_ILLCMD ; 
 size_t NRC_INVADDRESS ; 
 size_t NRC_LOCTFUL ; 
 scalar_t__ SESSION_ESTABLISHED ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t stub1 (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UCHAR nbCall(NetBIOSAdapter *adapter, PNCB ncb)
{
    UCHAR ret, i;

    TRACE(": adapter %p, NCB %p\n", adapter, ncb);

    if (!adapter) return NRC_BRIDGE;
    if (adapter->sessionsLen == 0) return NRC_ENVNOTDEF;
    if (!adapter->transport->call) return NRC_ILLCMD;
    if (!ncb) return NRC_INVADDRESS;

    EnterCriticalSection(&adapter->cs);
    for (i = 0; i < adapter->sessionsLen && adapter->sessions[i].inUse; i++)
        ;
    if (i < adapter->sessionsLen)
    {
        adapter->sessions[i].inUse = TRUE;
        adapter->sessions[i].state = CALL_PENDING;
        memcpy(adapter->sessions[i].local_name, ncb->ncb_name, NCBNAMSZ);
        memcpy(adapter->sessions[i].remote_name, ncb->ncb_callname, NCBNAMSZ);
        ret = NRC_GOODRET;
    }
    else
        ret = NRC_LOCTFUL;
    LeaveCriticalSection(&adapter->cs);

    if (ret == NRC_GOODRET)
    {
        ret = adapter->transport->call(adapter->impl.data, ncb,
         &adapter->sessions[i].data);
        if (ret == NRC_GOODRET)
        {
            ncb->ncb_lsn = i;
            adapter->sessions[i].state = SESSION_ESTABLISHED;
        }
        else
        {
            adapter->sessions[i].inUse = FALSE;
            adapter->sessions[i].state = 0;
        }
    }
    TRACE("returning 0x%02x\n", ret);
    return ret;
}