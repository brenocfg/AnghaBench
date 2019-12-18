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
struct PeSectionHeader {scalar_t__ VirtualSize; scalar_t__ PointerToRawData; scalar_t__ VirtualAddress; int /*<<< orphan*/  Name; } ;
struct TYPE_2__ {scalar_t__ Machine; int NumberOfSections; size_t SizeOfOptionalHeader; } ;
struct PeHeader {TYPE_1__ FileHeader; int /*<<< orphan*/  Magic; } ;
struct DosFileHeader {size_t ExeHeader; int /*<<< orphan*/  Magic; } ;
typedef  size_t UINTN ;
typedef  int /*<<< orphan*/  EFI_STATUS ;
typedef  char CHAR8 ;

/* Variables and functions */
 scalar_t__ CompareMem (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  EFI_LOAD_ERROR ; 
 int /*<<< orphan*/  EFI_SUCCESS ; 
 scalar_t__ PE_HEADER_MACHINE_ARM64 ; 
 scalar_t__ PE_HEADER_MACHINE_I386 ; 
 scalar_t__ PE_HEADER_MACHINE_X64 ; 
 int strlena (char*) ; 

EFI_STATUS pe_memory_locate_sections(CHAR8 *base, CHAR8 **sections, UINTN *addrs, UINTN *offsets, UINTN *sizes) {
        struct DosFileHeader *dos;
        struct PeHeader *pe;
        UINTN i;
        UINTN offset;

        dos = (struct DosFileHeader *)base;

        if (CompareMem(dos->Magic, "MZ", 2) != 0)
                return EFI_LOAD_ERROR;

        pe = (struct PeHeader *)&base[dos->ExeHeader];
        if (CompareMem(pe->Magic, "PE\0\0", 4) != 0)
                return EFI_LOAD_ERROR;

        /* PE32+ Subsystem type */
        if (pe->FileHeader.Machine != PE_HEADER_MACHINE_X64 &&
            pe->FileHeader.Machine != PE_HEADER_MACHINE_ARM64 &&
            pe->FileHeader.Machine != PE_HEADER_MACHINE_I386)
                return EFI_LOAD_ERROR;

        if (pe->FileHeader.NumberOfSections > 96)
                return EFI_LOAD_ERROR;

        offset = dos->ExeHeader + sizeof(*pe) + pe->FileHeader.SizeOfOptionalHeader;

        for (i = 0; i < pe->FileHeader.NumberOfSections; i++) {
                struct PeSectionHeader *sect;
                UINTN j;

                sect = (struct PeSectionHeader *)&base[offset];
                for (j = 0; sections[j]; j++) {
                        if (CompareMem(sect->Name, sections[j], strlena(sections[j])) != 0)
                                continue;

                        if (addrs)
                                addrs[j] = (UINTN)sect->VirtualAddress;
                        if (offsets)
                                offsets[j] = (UINTN)sect->PointerToRawData;
                        if (sizes)
                                sizes[j] = (UINTN)sect->VirtualSize;
                }
                offset += sizeof(*sect);
        }

        return EFI_SUCCESS;
}