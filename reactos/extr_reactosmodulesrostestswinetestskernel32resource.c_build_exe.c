#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_8__** sect_in; } ;
typedef  TYPE_4__ sec_build ;
typedef  int /*<<< orphan*/  sec ;
struct TYPE_11__ {size_t VirtualSize; } ;
struct TYPE_17__ {size_t VirtualAddress; size_t SizeOfRawData; size_t PointerToRawData; TYPE_2__ Misc; } ;
struct TYPE_16__ {int e_lfanew; int /*<<< orphan*/  e_magic; } ;
struct TYPE_12__ {int NumberOfSections; int SizeOfOptionalHeader; int Characteristics; int /*<<< orphan*/  Machine; } ;
struct TYPE_14__ {int MajorLinkerVersion; int BaseOfCode; int ImageBase; int MajorOperatingSystemVersion; int MajorImageVersion; int MajorSubsystemVersion; int SizeOfHeaders; int SizeOfImage; int SectionAlignment; int FileAlignment; TYPE_1__* DataDirectory; int /*<<< orphan*/  Subsystem; int /*<<< orphan*/  Magic; } ;
struct TYPE_15__ {TYPE_3__ FileHeader; TYPE_5__ OptionalHeader; int /*<<< orphan*/  Signature; } ;
struct TYPE_10__ {int Size; int /*<<< orphan*/  VirtualAddress; } ;
typedef  int /*<<< orphan*/  IMAGE_SECTION_HEADER ;
typedef  TYPE_5__ IMAGE_OPTIONAL_HEADER ;
typedef  TYPE_6__ IMAGE_NT_HEADERS ;
typedef  TYPE_7__ IMAGE_DOS_HEADER ;
typedef  scalar_t__ HANDLE ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  IMAGE_DOS_SIGNATURE ; 
 int IMAGE_FILE_DLL ; 
 int IMAGE_FILE_EXECUTABLE_IMAGE ; 
 int /*<<< orphan*/  IMAGE_FILE_MACHINE_I386 ; 
 size_t IMAGE_FILE_RESOURCE_DIRECTORY ; 
 int /*<<< orphan*/  IMAGE_NT_OPTIONAL_HDR_MAGIC ; 
 int /*<<< orphan*/  IMAGE_NT_SIGNATURE ; 
 int /*<<< orphan*/  IMAGE_SUBSYSTEM_WINDOWS_CUI ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,int /*<<< orphan*/ *,size_t,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filename ; 
 size_t max_sections ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_8__*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 size_t min (int,size_t) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int page_size ; 
 int /*<<< orphan*/  rva_rsrc_start ; 

__attribute__((used)) static int build_exe( const sec_build* sec_descr )
{
    IMAGE_DOS_HEADER *dos;
    IMAGE_NT_HEADERS *nt;
    IMAGE_SECTION_HEADER *sec;
    IMAGE_OPTIONAL_HEADER *opt;
    HANDLE file;
    DWORD written, i, file_size;
    BYTE page[page_size];

    memset( page, 0, sizeof page );

    dos = (void*) page;
    dos->e_magic = IMAGE_DOS_SIGNATURE;
    dos->e_lfanew = sizeof *dos;

    nt = (void*) &dos[1];

    nt->Signature = IMAGE_NT_SIGNATURE;
    nt->FileHeader.Machine = IMAGE_FILE_MACHINE_I386;
    nt->FileHeader.NumberOfSections = 0;
    nt->FileHeader.SizeOfOptionalHeader = sizeof nt->OptionalHeader;
    nt->FileHeader.Characteristics = IMAGE_FILE_EXECUTABLE_IMAGE | IMAGE_FILE_DLL;

    opt = &nt->OptionalHeader;

    opt->Magic = IMAGE_NT_OPTIONAL_HDR_MAGIC;
    opt->MajorLinkerVersion = 1;
    opt->BaseOfCode = 0x10;
    opt->ImageBase = 0x10000000;
    opt->MajorOperatingSystemVersion = 4;
    opt->MajorImageVersion = 1;
    opt->MajorSubsystemVersion = 4;
    opt->SizeOfHeaders = sizeof *dos + sizeof *nt + sizeof *sec * 2;
    opt->SizeOfImage = page_size;
    opt->Subsystem = IMAGE_SUBSYSTEM_WINDOWS_CUI;

    /* if SectionAlignment and File alignment are not specified */
    /* UpdateResource fails trying to create a huge temporary file */
    opt->SectionAlignment = page_size;
    opt->FileAlignment = page_size;

    opt->DataDirectory[IMAGE_FILE_RESOURCE_DIRECTORY].VirtualAddress = rva_rsrc_start;
    opt->DataDirectory[IMAGE_FILE_RESOURCE_DIRECTORY].Size = page_size;

    sec = (void*) &nt[1];

    file_size = 0;
    for ( i = 0; i < max_sections; i++ )
        if ( sec_descr->sect_in[i] )
        {
            DWORD virt_end_of_section = sec_descr->sect_in[i]->Misc.VirtualSize +
                sec_descr->sect_in[i]->VirtualAddress;
            DWORD phys_end_of_section = sec_descr->sect_in[i]->SizeOfRawData +
                sec_descr->sect_in[i]->PointerToRawData;
            memcpy( sec + nt->FileHeader.NumberOfSections, sec_descr->sect_in[i],
                    sizeof(sec[0]) );
            nt->FileHeader.NumberOfSections++;
            if ( opt->SizeOfImage < virt_end_of_section )
                opt->SizeOfImage = virt_end_of_section;
            if ( file_size < phys_end_of_section )
                file_size = phys_end_of_section;
        }

    file = CreateFileA(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
    ok (file != INVALID_HANDLE_VALUE, "failed to create file\n");

    /* write out the header */
    WriteFile( file, page, sizeof page, &written, NULL );

    /* write out zeroed pages for sections */
    memset( page, 0, sizeof page );
    for ( i = page_size; i < file_size; i += page_size )
    {
	DWORD size = min(page_size, file_size - i);
        WriteFile( file, page, size, &written, NULL );
    }

    CloseHandle( file );

    return 0;
}