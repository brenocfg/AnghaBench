#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_11__ {scalar_t__ e_magic; long e_lfanew; } ;
struct TYPE_10__ {int SizeOfOptionalHeader; } ;
struct TYPE_9__ {size_t ImageBase; } ;
struct TYPE_8__ {int PointerToRawData; } ;
typedef  TYPE_1__* PIMAGE_SECTION_HEADER ;
typedef  TYPE_2__* PIMAGE_OPTIONAL_HEADER ;
typedef  TYPE_3__* PIMAGE_FILE_HEADER ;
typedef  TYPE_4__* PIMAGE_DOS_HEADER ;

/* Variables and functions */
 scalar_t__ IMAGE_DOS_MAGIC ; 
 int find_and_print_offset (char*,size_t) ; 
 TYPE_1__* find_rossym_section (TYPE_3__*,TYPE_1__*) ; 
 size_t fixup_offset (size_t,size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 

int
process_data ( const void* FileData, size_t offset )
{
	PIMAGE_DOS_HEADER PEDosHeader;
	PIMAGE_FILE_HEADER PEFileHeader;
	PIMAGE_OPTIONAL_HEADER PEOptHeader;
	PIMAGE_SECTION_HEADER PESectionHeaders;
	PIMAGE_SECTION_HEADER PERosSymSectionHeader;
	size_t ImageBase;
	int res;

	/* Check if MZ header exists  */
	PEDosHeader = (PIMAGE_DOS_HEADER)FileData;
	if (PEDosHeader->e_magic != IMAGE_DOS_MAGIC || PEDosHeader->e_lfanew == 0L)
	{
		perror("Input file is not a PE image.\n");
		return 1;
	}

	/* Locate PE file header  */
	/* sizeof(ULONG) = sizeof(MAGIC) */
	PEFileHeader = (PIMAGE_FILE_HEADER)((char *)FileData + PEDosHeader->e_lfanew + sizeof(ULONG));

	/* Locate optional header */
	PEOptHeader = (PIMAGE_OPTIONAL_HEADER)(PEFileHeader + 1);
	ImageBase = PEOptHeader->ImageBase;

	/* Locate PE section headers  */
	PESectionHeaders = (PIMAGE_SECTION_HEADER)((char *) PEOptHeader + PEFileHeader->SizeOfOptionalHeader);

	/* make sure offset is what we want */
	offset = fixup_offset ( ImageBase, offset );

	/* find rossym section */
	PERosSymSectionHeader = find_rossym_section (
		PEFileHeader, PESectionHeaders );
	if ( !PERosSymSectionHeader )
	{
		fprintf ( stderr, "Couldn't find rossym section in executable\n" );
		return 1;
	}
	res = find_and_print_offset ( (char*)FileData + PERosSymSectionHeader->PointerToRawData,
		offset );
	if ( res )
		printf ( "??:0\n" );
	return res;
}