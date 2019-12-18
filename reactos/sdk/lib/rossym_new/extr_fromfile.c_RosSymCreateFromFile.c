#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  scalar_t__ ULONG ;
struct TYPE_23__ {int MaximumLength; TYPE_4__* Buffer; void* Length; } ;
struct TYPE_20__ {unsigned int PointerToSymbolTable; unsigned int NumberOfSymbols; int NumberOfSections; } ;
struct TYPE_19__ {int /*<<< orphan*/  BaseOfData; int /*<<< orphan*/  BaseOfCode; int /*<<< orphan*/  SizeOfImage; int /*<<< orphan*/  ImageBase; } ;
struct TYPE_22__ {char* Name; TYPE_2__ FileHeader; TYPE_1__ OptionalHeader; scalar_t__ e_lfanew; } ;
struct TYPE_21__ {unsigned int nsections; int /*<<< orphan*/  loadsection; int /*<<< orphan*/  datastart; int /*<<< orphan*/  codestart; int /*<<< orphan*/  imagesize; int /*<<< orphan*/  loadbase; int /*<<< orphan*/  imagebase; TYPE_4__* sect; int /*<<< orphan*/  e8; int /*<<< orphan*/  e4; int /*<<< orphan*/  e2; int /*<<< orphan*/  fd; } ;
typedef  TYPE_3__ Pe ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PROSSYM_INFO ;
typedef  TYPE_4__* PIMAGE_SECTION_HEADER ;
typedef  scalar_t__ PCSZ ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IMAGE_SECTION_HEADER ;
typedef  TYPE_4__ IMAGE_NT_HEADERS ;
typedef  TYPE_4__ IMAGE_DOS_HEADER ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_7__ ANSI_STRING ;

/* Variables and functions */
 TYPE_7__* ANSI_NAME_STRING (TYPE_4__*) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  FALSE ; 
 void* GetStrnlen (TYPE_4__*,int) ; 
 scalar_t__ IMAGE_FIRST_SECTION (TYPE_4__*) ; 
 int IMAGE_SIZEOF_SHORT_NAME ; 
 int MAXIMUM_DWARF_NAME_SIZE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROSSYM_IS_VALID_DOS_HEADER (TYPE_4__*) ; 
 int /*<<< orphan*/  ROSSYM_IS_VALID_NT_HEADERS (TYPE_4__*) ; 
 void* RosSymAllocMem (int) ; 
 int /*<<< orphan*/  RosSymFreeMem (TYPE_4__*) ; 
 int /*<<< orphan*/  RosSymReadFile (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  RosSymSeekFile (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  RosSymStatus ; 
 int /*<<< orphan*/  RtlCreateUnicodeStringFromAsciiz (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  RtlFreeAnsiString (TYPE_7__*) ; 
 int /*<<< orphan*/  RtlFreeUnicodeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlUnicodeStringToInteger (int /*<<< orphan*/ *,int,scalar_t__*) ; 
 unsigned int SYMBOL_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dwarfopen (TYPE_3__*) ; 
 int /*<<< orphan*/  loaddisksection ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  peget2 ; 
 int /*<<< orphan*/  peget4 ; 
 int /*<<< orphan*/  peget8 ; 
 int /*<<< orphan*/  werrstr (char*,...) ; 

BOOLEAN
RosSymCreateFromFile(PVOID FileContext, PROSSYM_INFO *RosSymInfo)
{
    IMAGE_DOS_HEADER DosHeader;
    IMAGE_NT_HEADERS NtHeaders;
    PIMAGE_SECTION_HEADER SectionHeaders;
    unsigned SectionIndex;
    unsigned SymbolTable, NumSymbols;

    /* Load DOS header */
    if (! RosSymSeekFile(FileContext, 0))
    {
        werrstr("Could not rewind file\n");
        return FALSE;
    }
    if (! RosSymReadFile(FileContext, &DosHeader, sizeof(IMAGE_DOS_HEADER)))
    {
        werrstr("Failed to read DOS header %x\n", RosSymStatus);
        return FALSE;
    }
    if (! ROSSYM_IS_VALID_DOS_HEADER(&DosHeader))
    {
        werrstr("Image doesn't have a valid DOS header\n");
        return FALSE;
    }

    /* Load NT headers */
    if (! RosSymSeekFile(FileContext, DosHeader.e_lfanew))
    {
        werrstr("Failed seeking to NT headers\n");
        return FALSE;
    }
    if (! RosSymReadFile(FileContext, &NtHeaders, sizeof(IMAGE_NT_HEADERS)))
    {
        werrstr("Failed to read NT headers\n");
        return FALSE;
    }
    if (! ROSSYM_IS_VALID_NT_HEADERS(&NtHeaders))
    {
        werrstr("Image doesn't have a valid PE header\n");
        return FALSE;
    }

    SymbolTable = NtHeaders.FileHeader.PointerToSymbolTable;
    NumSymbols = NtHeaders.FileHeader.NumberOfSymbols;

    if (!NumSymbols)
    {
        werrstr("Image doesn't have debug symbols\n");
        return FALSE;
    }

    DPRINT("SymbolTable %x NumSymbols %x\n", SymbolTable, NumSymbols);

    /* Load section headers */
    if (! RosSymSeekFile(FileContext, (char *) IMAGE_FIRST_SECTION(&NtHeaders) -
                         (char *) &NtHeaders + DosHeader.e_lfanew))
    {
        werrstr("Failed seeking to section headers\n");
        return FALSE;
    }
    DPRINT("Alloc section headers\n");
    SectionHeaders = RosSymAllocMem(NtHeaders.FileHeader.NumberOfSections
                                    * sizeof(IMAGE_SECTION_HEADER));
    if (NULL == SectionHeaders)
    {
        werrstr("Failed to allocate memory for %u section headers\n",
                NtHeaders.FileHeader.NumberOfSections);
        return FALSE;
    }
    if (! RosSymReadFile(FileContext, SectionHeaders,
                         NtHeaders.FileHeader.NumberOfSections
                         * sizeof(IMAGE_SECTION_HEADER)))
    {
        RosSymFreeMem(SectionHeaders);
        werrstr("Failed to read section headers\n");
        return FALSE;
    }

    // Convert names to ANSI_STRINGs
    for (SectionIndex = 0; SectionIndex < NtHeaders.FileHeader.NumberOfSections;
         SectionIndex++) 
    {
        ANSI_STRING astr;
        if (SectionHeaders[SectionIndex].Name[0] != '/') {
            DPRINT("Short name string %d, %s\n", SectionIndex, SectionHeaders[SectionIndex].Name);
            astr.Buffer = RosSymAllocMem(IMAGE_SIZEOF_SHORT_NAME);
            memcpy(astr.Buffer, SectionHeaders[SectionIndex].Name, IMAGE_SIZEOF_SHORT_NAME);
            astr.MaximumLength = IMAGE_SIZEOF_SHORT_NAME;
            astr.Length = GetStrnlen(astr.Buffer, IMAGE_SIZEOF_SHORT_NAME);
        } else {
            UNICODE_STRING intConv;
            NTSTATUS Status;
            ULONG StringOffset;

            if (!RtlCreateUnicodeStringFromAsciiz(&intConv, (PCSZ)SectionHeaders[SectionIndex].Name + 1))
                goto freeall;
            Status = RtlUnicodeStringToInteger(&intConv, 10, &StringOffset);
            RtlFreeUnicodeString(&intConv);
            if (!NT_SUCCESS(Status)) goto freeall;
            if (!RosSymSeekFile(FileContext, SymbolTable + NumSymbols * SYMBOL_SIZE + StringOffset))
                goto freeall;
            astr.Buffer = RosSymAllocMem(MAXIMUM_DWARF_NAME_SIZE);
            if (!RosSymReadFile(FileContext, astr.Buffer, MAXIMUM_DWARF_NAME_SIZE))
                goto freeall;
            astr.Length = GetStrnlen(astr.Buffer, MAXIMUM_DWARF_NAME_SIZE);
            astr.MaximumLength = MAXIMUM_DWARF_NAME_SIZE;		  
            DPRINT("Long name %d, %s\n", SectionIndex, astr.Buffer);
        }
        *ANSI_NAME_STRING(&SectionHeaders[SectionIndex]) = astr;
    }

    DPRINT("Done with sections\n");
    Pe *pe = RosSymAllocMem(sizeof(*pe));
    pe->fd = FileContext;
    pe->e2 = peget2;
    pe->e4 = peget4;
    pe->e8 = peget8;
    pe->nsections = NtHeaders.FileHeader.NumberOfSections;
    pe->sect = SectionHeaders;
    pe->imagebase = pe->loadbase = NtHeaders.OptionalHeader.ImageBase;
    pe->imagesize = NtHeaders.OptionalHeader.SizeOfImage;
    pe->codestart = NtHeaders.OptionalHeader.BaseOfCode;
    pe->datastart = NtHeaders.OptionalHeader.BaseOfData;
    pe->loadsection = loaddisksection;
    *RosSymInfo = dwarfopen(pe);

    return TRUE;

freeall:
    for (SectionIndex = 0; SectionIndex < NtHeaders.FileHeader.NumberOfSections;
         SectionIndex++)
        RtlFreeAnsiString(ANSI_NAME_STRING(&SectionHeaders[SectionIndex]));
    RosSymFreeMem(SectionHeaders);

    return FALSE;
}