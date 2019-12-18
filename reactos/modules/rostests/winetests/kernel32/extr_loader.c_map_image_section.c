#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_19__ {scalar_t__ Magic; } ;
struct TYPE_25__ {TYPE_3__ OptionalHeader; } ;
struct TYPE_21__ {TYPE_4__* DataDirectory; } ;
struct TYPE_24__ {TYPE_5__ OptionalHeader; } ;
struct TYPE_23__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_17__ {int /*<<< orphan*/  LowPart; int /*<<< orphan*/  HighPart; } ;
struct TYPE_18__ {TYPE_1__ u; int /*<<< orphan*/  QuadPart; } ;
struct TYPE_22__ {int Attributes; TYPE_2__ Size; int /*<<< orphan*/ * BaseAddress; } ;
struct TYPE_20__ {scalar_t__ VirtualAddress; } ;
struct TYPE_16__ {int Flags; } ;
typedef  int SIZE_T ;
typedef  TYPE_6__ SECTION_BASIC_INFORMATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_7__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IMAGE_SECTION_HEADER ;
typedef  TYPE_8__ IMAGE_NT_HEADERS32 ;
typedef  TYPE_9__ IMAGE_NT_HEADERS ;
typedef  TYPE_10__ IMAGE_COR20_HEADER ;
typedef  int /*<<< orphan*/ * HMODULE ;
typedef  scalar_t__ HANDLE ;
typedef  int BOOL ;

/* Variables and functions */
 int COMIMAGE_FLAGS_ILONLY ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DONT_RESOLVE_DLL_REFERENCES ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 scalar_t__ ERROR_BAD_EXE_FORMAT ; 
 int FALSE ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ GetLastError () ; 
 size_t IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR ; 
 scalar_t__ IMAGE_NT_OPTIONAL_HDR32_MAGIC ; 
 scalar_t__ IMAGE_NT_OPTIONAL_HDR64_MAGIC ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/ * LoadLibraryExA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 int SECTION_MAP_READ ; 
 int SECTION_QUERY ; 
 int SEC_FILE ; 
 int SEC_IMAGE ; 
 int STANDARD_RIGHTS_REQUIRED ; 
 int /*<<< orphan*/  SectionBasicInformation ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  create_test_dll_sections (int /*<<< orphan*/ *,TYPE_9__ const*,int /*<<< orphan*/  const*,void const*,char*) ; 
 int /*<<< orphan*/  dos_header ; 
 scalar_t__ is_win64 ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  pNtCreateSection (scalar_t__*,int,int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  pNtQuerySection (scalar_t__,int /*<<< orphan*/ ,TYPE_6__*,int,int*) ; 
 int query_image_section (int,char*,TYPE_9__ const*,void const*) ; 

__attribute__((used)) static NTSTATUS map_image_section( const IMAGE_NT_HEADERS *nt_header, const IMAGE_SECTION_HEADER *sections,
                                   const void *section_data, int line )
{
    char dll_name[MAX_PATH];
    LARGE_INTEGER size;
    HANDLE file, map;
    NTSTATUS status;
    ULONG file_size;
    BOOL has_code;
    HMODULE mod;

    file_size = create_test_dll_sections( &dos_header, nt_header, sections, section_data, dll_name );

    file = CreateFileA(dll_name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
    ok(file != INVALID_HANDLE_VALUE, "CreateFile error %d\n", GetLastError());

    size.QuadPart = file_size;
    status = pNtCreateSection(&map, STANDARD_RIGHTS_REQUIRED | SECTION_MAP_READ | SECTION_QUERY,
                              NULL, &size, PAGE_READONLY, SEC_IMAGE, file );
    if (!status)
    {
        SECTION_BASIC_INFORMATION info;
        SIZE_T info_size = 0xdeadbeef;
        NTSTATUS ret = pNtQuerySection( map, SectionBasicInformation, &info, sizeof(info), &info_size );
        ok( !ret, "NtQuerySection failed err %x\n", ret );
        ok( info_size == sizeof(info), "NtQuerySection wrong size %lu\n", info_size );
        ok( info.Attributes == (SEC_IMAGE | SEC_FILE), "NtQuerySection wrong attr %x\n", info.Attributes );
        ok( info.BaseAddress == NULL, "NtQuerySection wrong base %p\n", info.BaseAddress );
        ok( info.Size.QuadPart == file_size, "NtQuerySection wrong size %x%08x / %08x\n",
            info.Size.u.HighPart, info.Size.u.LowPart, file_size );
        has_code = query_image_section( line, dll_name, nt_header, section_data );
        /* test loading dll of wrong 32/64 bitness */
        if (nt_header->OptionalHeader.Magic == (is_win64 ? IMAGE_NT_OPTIONAL_HDR32_MAGIC
                                                         : IMAGE_NT_OPTIONAL_HDR64_MAGIC))
        {
            SetLastError( 0xdeadbeef );
            mod = LoadLibraryExA( dll_name, 0, DONT_RESOLVE_DLL_REFERENCES );
            if (!has_code && nt_header->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC)
            {
                BOOL il_only = FALSE;
                if (((const IMAGE_NT_HEADERS32 *)nt_header)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress)
                {
                    const IMAGE_COR20_HEADER *cor_header = section_data;
                    il_only = (cor_header->Flags & COMIMAGE_FLAGS_ILONLY) != 0;
                }
                ok( mod != NULL || broken(il_only), /* <= win7 */
                    "%u: loading failed err %u\n", line, GetLastError() );
            }
            else
            {
                ok( !mod, "%u: loading succeeded\n", line );
                ok( GetLastError() == ERROR_BAD_EXE_FORMAT, "%u: wrong error %u\n", line, GetLastError() );
            }
            if (mod) FreeLibrary( mod );
        }
    }
    if (map) CloseHandle( map );
    CloseHandle( file );
    DeleteFileA( dll_name );
    return status;
}