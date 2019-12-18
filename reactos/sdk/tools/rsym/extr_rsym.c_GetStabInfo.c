#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG ;
struct TYPE_6__ {size_t NumberOfSections; } ;
struct TYPE_5__ {scalar_t__* Name; size_t SizeOfRawData; int PointerToRawData; } ;
typedef  TYPE_1__* PIMAGE_SECTION_HEADER ;
typedef  TYPE_2__* PIMAGE_FILE_HEADER ;

/* Variables and functions */
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
GetStabInfo(void *FileData, PIMAGE_FILE_HEADER PEFileHeader,
            PIMAGE_SECTION_HEADER PESectionHeaders,
            ULONG *StabSymbolsLength, void **StabSymbolsBase,
            ULONG *StabStringsLength, void **StabStringsBase)
{
    ULONG Idx;

    /* Load .stab and .stabstr sections if available */
    *StabSymbolsBase = NULL;
    *StabSymbolsLength = 0;
    *StabStringsBase = NULL;
    *StabStringsLength = 0;

    for (Idx = 0; Idx < PEFileHeader->NumberOfSections; Idx++)
    {
        /* printf("section: '%.08s'\n", PESectionHeaders[Idx].Name); */
        if ((strncmp((char *) PESectionHeaders[Idx].Name, ".stab", 5) == 0)
            && (PESectionHeaders[Idx].Name[5] == 0))
        {
            /* printf(".stab section found. Size %d\n", PESectionHeaders[Idx].SizeOfRawData); */

            *StabSymbolsLength = PESectionHeaders[Idx].SizeOfRawData;
            *StabSymbolsBase = (void *)((char *) FileData + PESectionHeaders[Idx].PointerToRawData);
        }

        if (strncmp((char *) PESectionHeaders[Idx].Name, ".stabstr", 8) == 0)
        {
            /* printf(".stabstr section found. Size %d\n", PESectionHeaders[Idx].SizeOfRawData); */

            *StabStringsLength = PESectionHeaders[Idx].SizeOfRawData;
            *StabStringsBase = (void *)((char *) FileData + PESectionHeaders[Idx].PointerToRawData);
        }
    }

    return 0;
}