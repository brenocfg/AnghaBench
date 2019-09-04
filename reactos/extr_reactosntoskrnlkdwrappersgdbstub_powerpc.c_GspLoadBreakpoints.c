#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_8__ {int Type; int Address; scalar_t__ Length; } ;
struct TYPE_7__ {int Address; int Active; int /*<<< orphan*/  PrevContent; } ;
struct TYPE_6__ {int Dr7; } ;
typedef  TYPE_1__* PKTRAP_FRAME ;
typedef  int /*<<< orphan*/  PCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (void*) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*,int) ; 
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
 void* FALSE ; 
#define  GDB_ZTYPE_ACCESS_WATCHPOINT 130 
#define  GDB_ZTYPE_HARDWARE_BREAKPOINT 129 
#define  GDB_ZTYPE_WRITE_WATCHPOINT 128 
 unsigned int GspHwBreakpointCount ; 
 TYPE_5__* GspHwBreakpoints ; 
 int /*<<< orphan*/  GspLoadHwBreakpoint (TYPE_1__*,unsigned int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 void* GspMemoryError ; 
 int /*<<< orphan*/  GspReadMemSafe (int /*<<< orphan*/ ) ; 
 unsigned int GspSwBreakpointCount ; 
 TYPE_2__* GspSwBreakpoints ; 
 int /*<<< orphan*/  GspWriteMemSafe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I386_BP_TYPE_DATA_READWRITE ; 
 int /*<<< orphan*/  I386_BP_TYPE_DATA_WRITE ; 
 int /*<<< orphan*/  I386_BP_TYPE_EXECUTE ; 
 int /*<<< orphan*/  I386_OPCODE_INT3 ; 
 unsigned int MAX_HW_BREAKPOINTS ; 

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
      switch(GspHwBreakpoints[Index].Type)
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
      if (GspHwBreakpointCount + Index < MAX_HW_BREAKPOINTS)
        {
          DPRINT("Implementing software interrupt using hardware register\n");
          GspLoadHwBreakpoint(TrapFrame, GspHwBreakpointCount + Index,
                              GspSwBreakpoints[Index].Address, 0,
                              I386_BP_TYPE_EXECUTE);
          GspSwBreakpoints[Index].Active = FALSE;
        }
      else
        {
          DPRINT("Using real software breakpoint\n");
          GspMemoryError = FALSE;
          GspSwBreakpoints[Index].PrevContent = GspReadMemSafe((PCHAR) GspSwBreakpoints[Index].Address);
          if (! GspMemoryError)
            {
              GspWriteMemSafe((PCHAR) GspSwBreakpoints[Index].Address, I386_OPCODE_INT3);
            }
          GspSwBreakpoints[Index].Active = ! GspMemoryError;
          if (GspMemoryError)
            {
              DPRINT1("Failed to set software breakpoint at 0x%p\n",
                      GspSwBreakpoints[Index].Address);
            }
          else
            {
              DPRINT("Successfully set software breakpoint at 0x%p\n",
                     GspSwBreakpoints[Index].Address);
    DPRINT1("Successfully set software breakpoint at 0x%p\n", GspSwBreakpoints[Index].Address);
            }
        }
    }

  DPRINT("Final DR7 value 0x%08x\n", TrapFrame->Dr7);
}