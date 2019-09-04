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
typedef  void* ULONG ;
struct TYPE_3__ {int Length; char* Next; char Version; char* AugString; int AugStringLength; char* AugData; char* Instructions; int /*<<< orphan*/  AugLength; int /*<<< orphan*/  ReturnAddressRegister; int /*<<< orphan*/  DataAlign; int /*<<< orphan*/  CodeAlign; void* CieId; } ;
typedef  TYPE_1__* PDW2CIE ;

/* Variables and functions */
 int /*<<< orphan*/  DwDecodeSleb128 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  DwDecodeUleb128 (int /*<<< orphan*/ *,char*) ; 
 int strlen (char*) ; 

unsigned long
DwDecodeCie(PDW2CIE Cie, char *pc)
{
    Cie->Length = *(ULONG*)pc;
    Cie->Next = pc + 4 + Cie->Length;
    Cie->CieId = *(ULONG*)(pc + 4);
    Cie->Version = pc[8];
    Cie->AugString = pc + 9;
    Cie->AugStringLength = strlen(Cie->AugString);
    pc = Cie->AugString + Cie->AugStringLength + 1;
    pc += DwDecodeUleb128(&Cie->CodeAlign, pc);
    pc += DwDecodeSleb128(&Cie->DataAlign, pc);
    pc += DwDecodeUleb128(&Cie->ReturnAddressRegister, pc);
    pc += DwDecodeUleb128(&Cie->AugLength, pc);
    Cie->AugData = pc;
    pc += Cie->AugLength;
    Cie->Instructions = pc;

    return Cie->Length + 4;
}