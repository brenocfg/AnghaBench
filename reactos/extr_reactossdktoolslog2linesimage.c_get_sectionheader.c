#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_9__ {int /*<<< orphan*/  offset_errors; } ;
struct TYPE_8__ {scalar_t__ e_magic; long e_lfanew; } ;
struct TYPE_7__ {int SizeOfOptionalHeader; } ;
struct TYPE_6__ {size_t ImageBase; } ;
typedef  int /*<<< orphan*/ * PIMAGE_SECTION_HEADER ;
typedef  TYPE_1__* PIMAGE_OPTIONAL_HEADER ;
typedef  TYPE_2__* PIMAGE_FILE_HEADER ;
typedef  TYPE_3__* PIMAGE_DOS_HEADER ;

/* Variables and functions */
 scalar_t__ IMAGE_DOS_MAGIC ; 
 int /*<<< orphan*/ * find_rossym_section (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2l_dbg (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__ summ ; 

PIMAGE_SECTION_HEADER
get_sectionheader(const void *FileData)
{
    PIMAGE_DOS_HEADER PEDosHeader;
    PIMAGE_FILE_HEADER PEFileHeader;
    PIMAGE_OPTIONAL_HEADER PEOptHeader;
    PIMAGE_SECTION_HEADER PESectionHeaders;
    PIMAGE_SECTION_HEADER PERosSymSectionHeader;
    size_t ImageBase;

    /* Check if MZ header exists */
    PEDosHeader = (PIMAGE_DOS_HEADER)FileData;
    if (PEDosHeader->e_magic != IMAGE_DOS_MAGIC || PEDosHeader->e_lfanew == 0L)
    {
        l2l_dbg(0, "Input file is not a PE image.\n");
        summ.offset_errors++;
        return NULL;
    }

    /* Locate PE file header */
    /* sizeof(ULONG) = sizeof(MAGIC) */
    PEFileHeader = (PIMAGE_FILE_HEADER)((char *)FileData + PEDosHeader->e_lfanew + sizeof(ULONG));

    /* Locate optional header */
    PEOptHeader = (PIMAGE_OPTIONAL_HEADER)(PEFileHeader + 1);
    ImageBase = PEOptHeader->ImageBase;

    /* Locate PE section headers */
    PESectionHeaders = (PIMAGE_SECTION_HEADER)((char *)PEOptHeader + PEFileHeader->SizeOfOptionalHeader);

    /* find rossym section */
    PERosSymSectionHeader = find_rossym_section(PEFileHeader, PESectionHeaders);
    if (!PERosSymSectionHeader)
    {
        l2l_dbg(0, "Couldn't find rossym section in executable\n");
        summ.offset_errors++;
        return NULL;
    }

    return PERosSymSectionHeader;
}