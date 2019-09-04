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
struct TYPE_3__ {scalar_t__ PointerToSymbolTable; int NumberOfSymbols; } ;
typedef  int /*<<< orphan*/  PIMAGE_SECTION_HEADER ;
typedef  TYPE_1__* PIMAGE_FILE_HEADER ;
typedef  int /*<<< orphan*/  COFF_SYMENT ;

/* Variables and functions */

__attribute__((used)) static int
GetCoffInfo(void *FileData, PIMAGE_FILE_HEADER PEFileHeader,
            PIMAGE_SECTION_HEADER PESectionHeaders,
            ULONG *CoffSymbolsLength, void **CoffSymbolsBase,
            ULONG *CoffStringsLength, void **CoffStringsBase)
{

    if (PEFileHeader->PointerToSymbolTable == 0 || PEFileHeader->NumberOfSymbols == 0)
    {
        /* No COFF symbol table */
        *CoffSymbolsLength = 0;
        *CoffStringsLength = 0;
    }
    else
    {
        *CoffSymbolsLength = PEFileHeader->NumberOfSymbols * sizeof(COFF_SYMENT);
        *CoffSymbolsBase = (void *)((char *) FileData + PEFileHeader->PointerToSymbolTable);
        *CoffStringsLength = *((ULONG *) ((char *) *CoffSymbolsBase + *CoffSymbolsLength));
        *CoffStringsBase = (void *)((char *) *CoffSymbolsBase + *CoffSymbolsLength);
    }

    return 0;
}