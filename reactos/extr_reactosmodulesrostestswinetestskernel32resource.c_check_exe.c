#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ length; size_t rsrc_section; int NumberOfNamedEntries; int NumberOfIdEntries; TYPE_1__** sect_out; } ;
typedef  TYPE_4__ sec_verify ;
struct TYPE_21__ {int e_lfanew; } ;
struct TYPE_14__ {scalar_t__ NumberOfSections; } ;
struct TYPE_19__ {TYPE_3__* DataDirectory; } ;
struct TYPE_20__ {TYPE_2__ FileHeader; TYPE_7__ OptionalHeader; } ;
struct TYPE_18__ {scalar_t__ Characteristics; int MajorVersion; scalar_t__ MinorVersion; int NumberOfNamedEntries; int NumberOfIdEntries; int /*<<< orphan*/  TimeDateStamp; } ;
struct TYPE_17__ {int VirtualAddress; scalar_t__ SizeOfRawData; scalar_t__ PointerToRawData; scalar_t__ Characteristics; int /*<<< orphan*/  Name; } ;
struct TYPE_15__ {int VirtualAddress; } ;
struct TYPE_13__ {int VirtualAddress; scalar_t__ SizeOfRawData; scalar_t__ PointerToRawData; scalar_t__ Characteristics; int /*<<< orphan*/  Name; } ;
typedef  TYPE_5__ IMAGE_SECTION_HEADER ;
typedef  TYPE_6__ IMAGE_RESOURCE_DIRECTORY ;
typedef  TYPE_7__ IMAGE_OPTIONAL_HEADER ;
typedef  TYPE_8__ IMAGE_NT_HEADERS ;
typedef  TYPE_9__ IMAGE_DOS_HEADER ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFileA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateFileMappingA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_MAP_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ GetFileSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ GetTickCount () ; 
 size_t IMAGE_FILE_RESOURCE_DIRECTORY ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 TYPE_9__* MapViewOfFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 int /*<<< orphan*/  UnmapViewOfFile (TYPE_9__*) ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  filename ; 
 int max_sections ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void check_exe( const sec_verify *verify )
{
    int i;
    IMAGE_DOS_HEADER *dos;
    IMAGE_NT_HEADERS *nt;
    IMAGE_OPTIONAL_HEADER *opt;
    IMAGE_SECTION_HEADER *sec;
    IMAGE_RESOURCE_DIRECTORY *dir;
    HANDLE file, mapping;
    DWORD length, sec_count = 0;

    file = CreateFileA(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, 0);
    ok (file != INVALID_HANDLE_VALUE, "failed to create file (%d)\n", GetLastError());

    length = GetFileSize( file, NULL );
    ok( length >= verify->length, "file size wrong\n");

    mapping = CreateFileMappingA( file, NULL, PAGE_READONLY, 0, 0, NULL );
    ok (mapping != NULL, "failed to create file\n");

    dos = MapViewOfFile( mapping, FILE_MAP_READ, 0, 0, length );
    ok( dos != NULL, "failed to map file\n");

    if (!dos)
        goto end;

    nt = (void*) ((BYTE*) dos + dos->e_lfanew);
    opt = &nt->OptionalHeader;
    sec = (void*) &nt[1];

    for(i = 0; i < max_sections; i++)
        if (verify->sect_out[i])
        {
            ok( !memcmp(&verify->sect_out[i]->Name, &sec[sec_count].Name, 8), "section %d name wrong\n", sec_count);
            ok( verify->sect_out[i]->VirtualAddress == sec[sec_count].VirtualAddress, "section %d vaddr wrong\n", sec_count);
            ok( verify->sect_out[i]->SizeOfRawData <= sec[sec_count].SizeOfRawData, "section %d SizeOfRawData wrong (%d vs %d)\n", sec_count, verify->sect_out[i]->SizeOfRawData ,sec[sec_count].SizeOfRawData);
            ok( verify->sect_out[i]->PointerToRawData == sec[sec_count].PointerToRawData, "section %d PointerToRawData wrong\n", sec_count);
            ok( verify->sect_out[i]->Characteristics == sec[sec_count].Characteristics , "section %d characteristics wrong\n", sec_count);
            sec_count++;
        }

    ok( nt->FileHeader.NumberOfSections == sec_count, "number of sections wrong\n" );

    if (verify->rsrc_section >= 0 && verify->rsrc_section < nt->FileHeader.NumberOfSections)
    {
        dir = (void*) ((BYTE*) dos + sec[verify->rsrc_section].VirtualAddress);

        ok( dir->Characteristics == 0, "Characteristics wrong\n");
        ok( dir->TimeDateStamp == 0 || abs( dir->TimeDateStamp - GetTickCount() ) < 1000 /* nt4 */,
            "TimeDateStamp wrong %u\n", dir->TimeDateStamp);
        ok( dir->MajorVersion == 4, "MajorVersion wrong\n");
        ok( dir->MinorVersion == 0, "MinorVersion wrong\n");

        ok( dir->NumberOfNamedEntries == verify->NumberOfNamedEntries, "NumberOfNamedEntries should be %d instead of %d\n",
                verify->NumberOfNamedEntries, dir->NumberOfNamedEntries);
        ok( dir->NumberOfIdEntries == verify->NumberOfIdEntries, "NumberOfIdEntries should be %d instead of %d\n",
                verify->NumberOfIdEntries, dir->NumberOfIdEntries);

        ok(opt->DataDirectory[IMAGE_FILE_RESOURCE_DIRECTORY].VirtualAddress == sec[verify->rsrc_section].VirtualAddress,
                "VirtualAddress in optional header should be %d instead of %d\n",
                sec[verify->rsrc_section].VirtualAddress, opt->DataDirectory[IMAGE_FILE_RESOURCE_DIRECTORY].VirtualAddress);
    }

end:
    UnmapViewOfFile( dos );

    CloseHandle( mapping );

    CloseHandle( file );
}