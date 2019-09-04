#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ ULONG ;
struct TYPE_2__ {scalar_t__ Length; scalar_t__ Address; scalar_t__ Type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,size_t,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 scalar_t__ GDB_ZTYPE_HARDWARE_BREAKPOINT ; 
 scalar_t__ GDB_ZTYPE_READ_WATCHPOINT ; 
 size_t GspHwBreakpointCount ; 
 TYPE_1__* GspHwBreakpoints ; 
 int /*<<< orphan*/  GspOutBuffer ; 
 size_t MAX_HW_BREAKPOINTS ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
GspSetHwBreakpoint(ULONG Type, ULONG_PTR Address, ULONG Length)
{
  DPRINT("GspSetHwBreakpoint(%lu, 0x%p, %lu)\n", Type, Address, Length);

  if (GDB_ZTYPE_READ_WATCHPOINT == Type)
    {
      DPRINT1("Read watchpoint not supported\n");
      strcpy(GspOutBuffer, "E22");
    }
  else if (GDB_ZTYPE_HARDWARE_BREAKPOINT == Type && 1 != Length)
    {
      DPRINT1("Invalid length %lu for hardware breakpoint\n", Length);
      strcpy(GspOutBuffer, "E22");
    }
  else if (1 != Length && 2 != Length && 4 != Length)
    {
      DPRINT1("Invalid length %lu for GDB Z type %lu\n", Length, Type);
      strcpy(GspOutBuffer, "E22");
    }
  else if (0 != (Address & (Length - 1)))
    {
      DPRINT1("Invalid alignment for address 0x%p and length %d\n",
              Address, Length);
      strcpy(GspOutBuffer, "E22");
    }
  else if (MAX_HW_BREAKPOINTS == GspHwBreakpointCount)
    {
      DPRINT1("Trying to set too many hardware breakpoints\n");
      strcpy(GspOutBuffer, "E22");
    }
  else
    {
      DPRINT("Stored at index %u\n", GspHwBreakpointCount);
      GspHwBreakpoints[GspHwBreakpointCount].Type = Type;
      GspHwBreakpoints[GspHwBreakpointCount].Address = Address;
      GspHwBreakpoints[GspHwBreakpointCount].Length = Length;
      GspHwBreakpointCount++;
      strcpy(GspOutBuffer, "OK");
    }
}