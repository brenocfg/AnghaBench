#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* ULONG_PTR ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {int Dr7; void* Dr3; void* Dr2; void* Dr1; void* Dr0; } ;
typedef  TYPE_1__* PKTRAP_FRAME ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,void*,...) ; 
 int DR7_GLOBAL_ENABLE (unsigned int) ; 
 int DR7_LEN (unsigned int,int /*<<< orphan*/ ) ; 
 int DR7_TYPE (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
GspLoadHwBreakpoint(PKTRAP_FRAME TrapFrame, unsigned BpIndex,
                    ULONG_PTR Address, ULONG Length, ULONG Type)
{
    DPRINT("GspLoadHwBreakpoint(0x%p, %d, 0x%p, %d)\n",
           TrapFrame, BpIndex, Address, Type);

    /* Set the DR7_Gx bit to globally enable the breakpoint */
    TrapFrame->Dr7 |= DR7_GLOBAL_ENABLE(BpIndex) |
                      DR7_LEN(BpIndex, Length) |
                      DR7_TYPE(BpIndex, Type);

    switch (BpIndex)
    {
        case 0:
            DPRINT("Setting DR0 to 0x%p\n", Address);
            TrapFrame->Dr0 = Address;
            break;

        case 1:
            DPRINT("Setting DR1 to 0x%p\n", Address);
            TrapFrame->Dr1 = Address;
            break;

        case 2:
            DPRINT("Setting DR2 to 0x%p\n", Address);
            TrapFrame->Dr2 = Address;
            break;

        case 3:
            DPRINT("Setting DR3 to 0x%p\n", Address);
            TrapFrame->Dr3 = Address;
            break;
    }
}