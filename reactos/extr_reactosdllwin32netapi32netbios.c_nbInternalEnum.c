#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UCHAR ;
struct TYPE_8__ {size_t tableSize; int /*<<< orphan*/  cs; int /*<<< orphan*/  enumerated; TYPE_2__* table; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* enumerate ) () ;} ;
struct TYPE_7__ {TYPE_1__ transport; } ;
struct TYPE_6__ {scalar_t__ transport; scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__ gNBTable ; 
 size_t gNumTransports ; 
 TYPE_3__* gTransports ; 
 int /*<<< orphan*/  nbShutdownAdapter (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void nbInternalEnum(void)
{
    UCHAR i;

    EnterCriticalSection(&gNBTable.cs);
    TRACE("before mark\n");
    /* mark: */
    for (i = 0; i < gNBTable.tableSize; i++)
        if (gNBTable.table[i].enabled && gNBTable.table[i].transport != 0)
            gNBTable.table[i].enabled = FALSE;

    TRACE("marked, before store, %d transports\n", gNumTransports);
    /* store adapters: */
    for (i = 0; i < gNumTransports; i++)
        if (gTransports[i].transport.enumerate)
            gTransports[i].transport.enumerate();

    TRACE("before sweep\n");
    /* sweep: */
    for (i = 0; i < gNBTable.tableSize; i++)
        if (!gNBTable.table[i].enabled && gNBTable.table[i].transport != 0)
            nbShutdownAdapter(&gNBTable.table[i]);
    gNBTable.enumerated = TRUE;
    LeaveCriticalSection(&gNBTable.cs);
}