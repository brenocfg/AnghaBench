#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
typedef  size_t UCHAR ;
struct TYPE_12__ {TYPE_2__* DebugInfo; } ;
struct TYPE_11__ {size_t tableSize; int /*<<< orphan*/  cs; TYPE_3__* table; } ;
struct TYPE_10__ {scalar_t__ id; int /*<<< orphan*/  transport; } ;
struct TYPE_7__ {size_t lana; void* data; int /*<<< orphan*/  ifIndex; } ;
struct TYPE_9__ {void* enabled; TYPE_6__ cs; int /*<<< orphan*/  cmdQueue; TYPE_1__ impl; int /*<<< orphan*/ * transport; scalar_t__ transport_id; } ;
struct TYPE_8__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/  NetBIOSTransport ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  size_t BOOL ;

/* Variables and functions */
 int ADAPTERS_INCR ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 size_t FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_6__*) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int MAX_LANA ; 
 int /*<<< orphan*/  NBCmdQueueCreate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,size_t,...) ; 
 void* TRUE ; 
 TYPE_5__ gNBTable ; 
 size_t gNumTransports ; 
 TYPE_4__* gTransports ; 
 int /*<<< orphan*/  nbResizeAdapterTable (size_t) ; 

BOOL NetBIOSRegisterAdapter(ULONG transport, DWORD ifIndex, void *data)
{
    BOOL ret;
    UCHAR i;

    TRACE(": transport 0x%08x, ifIndex 0x%08x, data %p\n", transport, ifIndex,
     data);
    for (i = 0; i < gNumTransports && gTransports[i].id != transport; i++)
        ;
    if ((i < gNumTransports) && gTransports[i].id == transport)
    {
        NetBIOSTransport *transportPtr = &gTransports[i].transport;

        TRACE(": found transport %p for id 0x%08x\n", transportPtr, transport);

        EnterCriticalSection(&gNBTable.cs);
        ret = FALSE;
        for (i = 0; i < gNBTable.tableSize &&
         gNBTable.table[i].transport != 0; i++)
            ;
        if (i == gNBTable.tableSize && gNBTable.tableSize < MAX_LANA + 1)
        {
            UCHAR newSize;

            if (gNBTable.tableSize < (MAX_LANA + 1) - ADAPTERS_INCR)
                newSize = gNBTable.tableSize + ADAPTERS_INCR;
            else
                newSize = MAX_LANA + 1;
            nbResizeAdapterTable(newSize);
        }
        if (i < gNBTable.tableSize && gNBTable.table[i].transport == 0)
        {
            TRACE(": registering as LANA %d\n", i);
            gNBTable.table[i].transport_id = transport;
            gNBTable.table[i].transport = transportPtr;
            gNBTable.table[i].impl.lana = i;
            gNBTable.table[i].impl.ifIndex = ifIndex;
            gNBTable.table[i].impl.data = data;
            gNBTable.table[i].cmdQueue = NBCmdQueueCreate(GetProcessHeap());
            InitializeCriticalSection(&gNBTable.table[i].cs);
            gNBTable.table[i].cs.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": NetBIOSAdapterTable.NetBIOSAdapter.cs");
            gNBTable.table[i].enabled = TRUE;
            ret = TRUE;
        }
        LeaveCriticalSection(&gNBTable.cs);
    }
    else
        ret = FALSE;
    TRACE("returning %d\n", ret);
    return ret;
}