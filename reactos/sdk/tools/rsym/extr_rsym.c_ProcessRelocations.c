#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_15__ {scalar_t__ SizeOfBlock; scalar_t__ VirtualAddress; } ;
struct TYPE_14__ {size_t NumberOfRvaAndSizes; TYPE_1__* DataDirectory; } ;
struct TYPE_13__ {int PointerToRawData; int VirtualAddress; scalar_t__ SizeOfRawData; } ;
struct TYPE_12__ {scalar_t__ VirtualAddress; int Size; } ;
typedef  TYPE_2__* PIMAGE_SECTION_HEADER ;
typedef  TYPE_3__* PIMAGE_OPTIONAL_HEADER ;
typedef  TYPE_4__* PIMAGE_BASE_RELOCATION ;

/* Variables and functions */
 TYPE_2__* FindSectionForRVA (scalar_t__,unsigned int,TYPE_2__*) ; 
 size_t IMAGE_DIRECTORY_ENTRY_BASERELOC ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 void* malloc (scalar_t__) ; 
 scalar_t__ memcmp (TYPE_4__*,TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
ProcessRelocations(ULONG *ProcessedRelocsLength, void **ProcessedRelocs,
                   void *RawData, PIMAGE_OPTIONAL_HEADER OptHeader,
                   unsigned NumberOfSections, PIMAGE_SECTION_HEADER SectionHeaders)
{
    PIMAGE_SECTION_HEADER RelocSectionHeader, TargetSectionHeader;
    PIMAGE_BASE_RELOCATION BaseReloc, End, AcceptedRelocs;
    int Found;

    if (OptHeader->NumberOfRvaAndSizes < IMAGE_DIRECTORY_ENTRY_BASERELOC ||
        OptHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress == 0)
    {
        /* No relocation entries */
        *ProcessedRelocsLength = 0;
        *ProcessedRelocs = NULL;
        return 0;
    }

    RelocSectionHeader = FindSectionForRVA(OptHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress,
                                           NumberOfSections, SectionHeaders);
    if (RelocSectionHeader == NULL)
    {
        fprintf(stderr, "Can't find section header for relocation data\n");
        return 1;
    }

    *ProcessedRelocs = malloc(RelocSectionHeader->SizeOfRawData);
    if (*ProcessedRelocs == NULL)
    {
        fprintf(stderr,
                "Failed to allocate %u bytes for relocations\n",
                (unsigned int)RelocSectionHeader->SizeOfRawData);
        return 1;
    }
    *ProcessedRelocsLength = 0;

    BaseReloc = (PIMAGE_BASE_RELOCATION) ((char *) RawData +
                                          RelocSectionHeader->PointerToRawData +
                                          (OptHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress -
                                           RelocSectionHeader->VirtualAddress));
    End = (PIMAGE_BASE_RELOCATION) ((char *) BaseReloc +
                                    OptHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size);

    while (BaseReloc < End && BaseReloc->SizeOfBlock > 0)
    {
        TargetSectionHeader = FindSectionForRVA(BaseReloc->VirtualAddress,
                                                NumberOfSections,
                                                SectionHeaders);
        if (TargetSectionHeader != NULL)
        {
            AcceptedRelocs = *ProcessedRelocs;
            Found = 0;
            while (AcceptedRelocs < (PIMAGE_BASE_RELOCATION) ((char *) *ProcessedRelocs +
                                                              *ProcessedRelocsLength)
                   && !Found)
            {
                Found = BaseReloc->SizeOfBlock == AcceptedRelocs->SizeOfBlock &&
                                                  memcmp(BaseReloc, AcceptedRelocs, AcceptedRelocs->SizeOfBlock) == 0;
                AcceptedRelocs = (PIMAGE_BASE_RELOCATION) ((char *) AcceptedRelocs +
                                                           AcceptedRelocs->SizeOfBlock);
            }
            if (!Found)
            {
                memcpy((char *) *ProcessedRelocs + *ProcessedRelocsLength,
                       BaseReloc,
                       BaseReloc->SizeOfBlock);
                *ProcessedRelocsLength += BaseReloc->SizeOfBlock;
            }
        }
        BaseReloc = (PIMAGE_BASE_RELOCATION)((char *) BaseReloc + BaseReloc->SizeOfBlock);
    }

    return 0;
}