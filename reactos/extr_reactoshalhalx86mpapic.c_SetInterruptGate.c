#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  void* USHORT ;
typedef  int ULONG_PTR ;
typedef  int ULONG ;
struct TYPE_6__ {scalar_t__ IDT; } ;
struct TYPE_5__ {void* ExtendedOffset; int /*<<< orphan*/  Access; int /*<<< orphan*/  Selector; void* Offset; } ;
struct TYPE_4__ {int Present; int /*<<< orphan*/  Value; int /*<<< orphan*/  SegmentType; scalar_t__ SystemSegmentFlag; scalar_t__ Dpl; scalar_t__ Reserved; } ;
typedef  TYPE_1__ KIDT_ACCESS ;
typedef  TYPE_2__ KIDTENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  I386_INTERRUPT_GATE ; 
 int /*<<< orphan*/  KGDT_R0_CODE ; 
 TYPE_3__* KeGetPcr () ; 

VOID 
SetInterruptGate(ULONG index, ULONG_PTR address)
{
#ifdef _M_AMD64
  KIDTENTRY64 *idt;

  idt = &KeGetPcr()->IdtBase[index];

  idt->OffsetLow = address & 0xffff;
  idt->Selector = KGDT_64_R0_CODE;
  idt->IstIndex = 0;
  idt->Reserved0 = 0;
  idt->Type = 0x0e;
  idt->Dpl = 0;
  idt->Present = 1;
  idt->OffsetMiddle = (address >> 16) & 0xffff;
  idt->OffsetHigh = address >> 32;
  idt->Reserved1 = 0;
  idt->Alignment = 0;
#else
  KIDTENTRY *idt;
  KIDT_ACCESS Access;

  /* Set the IDT Access Bits */
  Access.Reserved = 0;
  Access.Present = 1;
  Access.Dpl = 0; /* Kernel-Mode */
  Access.SystemSegmentFlag = 0;
  Access.SegmentType = I386_INTERRUPT_GATE;
  
  idt = (KIDTENTRY*)((ULONG)KeGetPcr()->IDT + index * sizeof(KIDTENTRY));
  idt->Offset = (USHORT)(address & 0xffff);
  idt->Selector = KGDT_R0_CODE;
  idt->Access = Access.Value;
  idt->ExtendedOffset = (USHORT)(address >> 16);
#endif
}