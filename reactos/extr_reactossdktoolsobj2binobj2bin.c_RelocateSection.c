#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_8__ {int PointerToRawData; int PointerToRelocations; unsigned int NumberOfRelocations; unsigned int VirtualAddress; unsigned int SizeOfRawData; } ;
struct TYPE_7__ {unsigned int VirtualAddress; int Type; size_t SymbolTableIndex; } ;
struct TYPE_6__ {int /*<<< orphan*/  Value; } ;
typedef  TYPE_1__* PIMAGE_SYMBOL ;
typedef  TYPE_2__* PIMAGE_RELOCATION ;
typedef  TYPE_3__ IMAGE_SECTION_HEADER ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
#define  IMAGE_REL_I386_ABSOLUTE 129 
#define  IMAGE_REL_I386_DIR32 128 
 int /*<<< orphan*/  printf (char*,int,unsigned int) ; 

__attribute__((used)) static
void
RelocateSection(
    char *pData,
    IMAGE_SECTION_HEADER *pSectionHeader,
    PIMAGE_SYMBOL pSymbols,
    unsigned int iOffset)
{
    unsigned int i, nOffset;
    PIMAGE_RELOCATION pReloc;
    char *pSection;
    WORD *p16;
    DWORD *p32;

    pSection = pData + pSectionHeader->PointerToRawData;

    /* Calculate pointer to relocation table */
    pReloc = (PIMAGE_RELOCATION)(pData + pSectionHeader->PointerToRelocations);

    /* Loop all relocations */
    for (i = 0; i < pSectionHeader->NumberOfRelocations; i++)
    {
        nOffset = pReloc->VirtualAddress - pSectionHeader->VirtualAddress;

        if (nOffset > pSectionHeader->SizeOfRawData) continue;

        switch (pReloc->Type)
        {
            case IMAGE_REL_I386_ABSOLUTE:
            case 16:
                p16 = (void*)(pSection + nOffset);
                *p16 += (WORD)(pSymbols[pReloc->SymbolTableIndex].Value + iOffset);
                break;

            case IMAGE_REL_I386_DIR32:
                p32 = (void*)(pSection + nOffset);
                *p32 += (DWORD)(pSymbols[pReloc->SymbolTableIndex].Value + iOffset);
                break;

            default:
                printf("Unknown relocation type %u, address 0x%x\n",
                       pReloc->Type, (unsigned)pReloc->VirtualAddress);
        }

        pReloc++;
    }
}