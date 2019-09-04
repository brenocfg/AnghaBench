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
typedef  int ULONG ;
struct TYPE_3__ {int Length; char* Next; char* CiePointer; int PcBegin; int PcRange; int AugLength; char* AugData; char* Instructions; } ;
typedef  TYPE_1__* PDW2FDE ;

/* Variables and functions */
 int /*<<< orphan*/  DwDecodeUleb128 (int*,char*) ; 

unsigned long
DwDecodeFde(PDW2FDE Fde, char *pc)
{
    Fde->Length = *(ULONG*)pc;
    Fde->Next = pc + 4 + Fde->Length;
    Fde->CiePointer = pc + 4 - *(ULONG*)(pc + 4);
    Fde->PcBegin = *(ULONG*)(pc + 8);
    Fde->PcRange = *(ULONG*)(pc + 12);
    pc += 16;
    pc += DwDecodeUleb128(&Fde->AugLength, pc);
    Fde->AugData = pc;
    Fde->Instructions = Fde->AugData + Fde->AugLength;

    return Fde->Length + 4;
}