#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
typedef  size_t UCHAR ;
struct TYPE_4__ {size_t tableSize; int /*<<< orphan*/  cs; TYPE_1__* table; scalar_t__ enumerating; } ;
struct TYPE_3__ {scalar_t__ transport_id; int /*<<< orphan*/  impl; } ;
typedef  int /*<<< orphan*/  (* NetBIOSEnumAdaptersCallback ) (size_t,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,void*) ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_TRANSPORTS ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int /*<<< orphan*/  (*) (size_t,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,void*),void*) ; 
 scalar_t__ TRUE ; 
 TYPE_2__ gNBTable ; 
 scalar_t__ memcmp (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nbInternalEnum () ; 

void NetBIOSEnumAdapters(ULONG transport, NetBIOSEnumAdaptersCallback cb,
 void *closure)
{
    TRACE("transport 0x%08x, callback %p, closure %p\n", transport, cb,
     closure);
    if (cb)
    {
        BOOL enumAll = memcmp(&transport, ALL_TRANSPORTS, sizeof(ULONG)) == 0;
        UCHAR i, numLANAs = 0;

        EnterCriticalSection(&gNBTable.cs);
        if (!gNBTable.enumerating)
        {
            gNBTable.enumerating = TRUE;
            nbInternalEnum();
            gNBTable.enumerating = FALSE;
        }
        for (i = 0; i < gNBTable.tableSize; i++)
            if (enumAll || gNBTable.table[i].transport_id == transport)
                numLANAs++;
        if (numLANAs > 0)
        {
            UCHAR lanaIndex = 0;

            for (i = 0; i < gNBTable.tableSize; i++)
                if (gNBTable.table[i].transport_id != 0 &&
                 (enumAll || gNBTable.table[i].transport_id == transport))
                    cb(numLANAs, lanaIndex++, gNBTable.table[i].transport_id,
                     &gNBTable.table[i].impl, closure);
        }
        LeaveCriticalSection(&gNBTable.cs);
    }
}