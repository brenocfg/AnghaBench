#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {int Type; scalar_t__ Length; int /*<<< orphan*/  Address; } ;
struct TYPE_5__ {int Dr7; } ;
typedef  TYPE_1__* PKTRAP_FRAME ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int DR7_G0 ; 
 int DR7_G1 ; 
 int DR7_G2 ; 
 int DR7_G3 ; 
 int DR7_L0 ; 
 int DR7_L1 ; 
 int DR7_L2 ; 
 int DR7_L3 ; 
 int DR7_LEN0_MASK ; 
 int DR7_LEN1_MASK ; 
 int DR7_LEN2_MASK ; 
 int DR7_LEN3_MASK ; 
 int DR7_TYPE0_MASK ; 
 int DR7_TYPE1_MASK ; 
 int DR7_TYPE2_MASK ; 
 int DR7_TYPE3_MASK ; 
 int /*<<< orphan*/  FALSE ; 
#define  GDB_ZTYPE_ACCESS_WATCHPOINT 130 
#define  GDB_ZTYPE_HARDWARE_BREAKPOINT 129 
#define  GDB_ZTYPE_WRITE_WATCHPOINT 128 
 unsigned int GspHwBreakpointCount ; 
 TYPE_4__* GspHwBreakpoints ; 
 int /*<<< orphan*/  GspLoadHwBreakpoint (TYPE_1__*,unsigned int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GspLoadSwBreakpoint (unsigned int) ; 
 unsigned int GspSwBreakpointCount ; 
 int /*<<< orphan*/  I386_BP_TYPE_DATA_READWRITE ; 
 int /*<<< orphan*/  I386_BP_TYPE_DATA_WRITE ; 
 int /*<<< orphan*/  I386_BP_TYPE_EXECUTE ; 

__attribute__((used)) static void
GspLoadBreakpoints(PKTRAP_FRAME TrapFrame)
{
    unsigned Index;
    ULONG i386Type;

    DPRINT("GspLoadBreakpoints\n");
    DPRINT("DR7 on entry: 0x%08x\n", TrapFrame->Dr7);

    /* Remove all breakpoints */
    TrapFrame->Dr7 &= ~(DR7_L0 | DR7_L1 | DR7_L2 | DR7_L3 |
                        DR7_G0 | DR7_G1 | DR7_G2 | DR7_G3 |
                        DR7_TYPE0_MASK | DR7_LEN0_MASK |
                        DR7_TYPE1_MASK | DR7_LEN1_MASK |
                        DR7_TYPE2_MASK | DR7_LEN2_MASK |
                        DR7_TYPE3_MASK | DR7_LEN3_MASK);

    for (Index = 0; Index < GspHwBreakpointCount; Index++)
    {
        switch (GspHwBreakpoints[Index].Type)
        {
            case GDB_ZTYPE_HARDWARE_BREAKPOINT:
                i386Type = I386_BP_TYPE_EXECUTE;
                break;
            case GDB_ZTYPE_WRITE_WATCHPOINT:
                i386Type = I386_BP_TYPE_DATA_WRITE;
                break;
            case GDB_ZTYPE_ACCESS_WATCHPOINT:
                i386Type = I386_BP_TYPE_DATA_READWRITE;
                break;
            default:
                ASSERT(FALSE);
                i386Type = I386_BP_TYPE_EXECUTE;
                break;
        }

        GspLoadHwBreakpoint(TrapFrame, Index, GspHwBreakpoints[Index].Address,
                            GspHwBreakpoints[Index].Length - 1, i386Type);
    }

    for (Index = 0; Index < GspSwBreakpointCount; Index++)
    {
        DPRINT("Using real software breakpoint\n");
        GspLoadSwBreakpoint(Index);
    }

    DPRINT("Final DR7 value 0x%08x\n", TrapFrame->Dr7);
}