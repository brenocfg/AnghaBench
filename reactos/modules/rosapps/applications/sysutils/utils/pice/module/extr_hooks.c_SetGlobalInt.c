#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct IdtEntry {int HiOffset; int LoOffset; int /*<<< orphan*/  SegSel; } ;
typedef  void* USHORT ;
typedef  int ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 

ULONG SetGlobalInt(ULONG dwInt,ULONG NewIntHandler)
{
    ULONG idt[2];
    ULONG OldIntHandler;
    struct IdtEntry* pidt;
    struct IdtEntry oldidt;

    ENTER_FUNC();

	// get linear location of IDT
	__asm__("sidt %0":"=m" (idt));

	// get pointer to idte for int 3
	pidt=((struct IdtEntry*)((idt[1]<<16)|((idt[0]>>16)&0x0000FFFF)))+dwInt;

	oldidt=*pidt;

    // set new handler address
	pidt->HiOffset=(USHORT)(((ULONG)NewIntHandler)>>16);
	pidt->LoOffset=(USHORT)(((ULONG)NewIntHandler)&0x0000FFFF);

    DPRINT((0,"new INT(%0.2x) handler = %0.4x:%x\n",dwInt,pidt->SegSel,(pidt->HiOffset<<16)|(pidt->LoOffset&0x0000FFFF)));

	OldIntHandler=(oldidt.HiOffset<<16)|(oldidt.LoOffset&0x0000FFFF);

    DPRINT((0,"old INT(%0.2x) handler = %0.4x:%x\n",dwInt,pidt->SegSel,OldIntHandler));

    LEAVE_FUNC();

	return OldIntHandler;
}