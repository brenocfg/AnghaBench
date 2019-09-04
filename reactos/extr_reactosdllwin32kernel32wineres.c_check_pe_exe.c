#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  VirtualAddress; } ;
struct TYPE_6__ {scalar_t__ Magic; TYPE_5__* DataDirectory; } ;
struct TYPE_9__ {TYPE_1__ OptionalHeader; } ;
struct TYPE_7__ {TYPE_5__* DataDirectory; } ;
struct TYPE_8__ {TYPE_2__ OptionalHeader; } ;
typedef  int /*<<< orphan*/  QUEUEDUPDATES ;
typedef  int /*<<< orphan*/  IMAGE_SECTION_HEADER ;
typedef  TYPE_3__ IMAGE_NT_HEADERS64 ;
typedef  TYPE_4__ IMAGE_NT_HEADERS32 ;
typedef  TYPE_5__ IMAGE_DATA_DIRECTORY ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileMappingW (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_MAP_READ ; 
 int /*<<< orphan*/  GetFileSize (scalar_t__,int /*<<< orphan*/ *) ; 
 size_t IMAGE_DIRECTORY_ENTRY_RESOURCE ; 
 scalar_t__ IMAGE_NT_OPTIONAL_HDR64_MAGIC ; 
 void* MapViewOfFile (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UnmapViewOfFile (void*) ; 
 scalar_t__ get_nt_header (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_section_header (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL check_pe_exe( HANDLE file, QUEUEDUPDATES *updates )
{
    const IMAGE_NT_HEADERS32 *nt;
    const IMAGE_NT_HEADERS64 *nt64;
    const IMAGE_SECTION_HEADER *sec;
    const IMAGE_DATA_DIRECTORY *dd;
    BOOL ret = FALSE;
    HANDLE mapping;
    DWORD mapping_size, num_sections = 0;
    void *base = NULL;

    mapping_size = GetFileSize( file, NULL );

    mapping = CreateFileMappingW( file, NULL, PAGE_READONLY, 0, 0, NULL );
    if (!mapping)
        goto done;

    base = MapViewOfFile( mapping, FILE_MAP_READ, 0, 0, mapping_size );
    if (!base)
        goto done;

    nt = (IMAGE_NT_HEADERS32 *)get_nt_header( base, mapping_size );
    if (!nt)
        goto done;

    nt64 = (IMAGE_NT_HEADERS64*)nt;
    dd = &nt->OptionalHeader.DataDirectory[0];
    if (nt->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
        dd = &nt64->OptionalHeader.DataDirectory[0];

    TRACE("resources: %08x %08x\n",
          dd[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress,
          dd[IMAGE_DIRECTORY_ENTRY_RESOURCE].Size);

    sec = get_section_header( base, mapping_size, &num_sections );
    if (!sec)
        goto done;

    ret = TRUE;

done:
    if (base)
        UnmapViewOfFile( base );
    if (mapping)
        CloseHandle( mapping );

    return ret;
}