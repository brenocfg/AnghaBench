#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_8__ {int idx; int p; TYPE_2__* psh; } ;
struct TYPE_13__ {int FilePtr; int HeaderSize; int Symbols; char* Strings; int AllSections; int UsedSections; int* UseSection; int NewSectionHeaderSize; TYPE_1__ eh_frame; TYPE_2__* NewSectionHeaders; TYPE_2__* SectionHeaders; TYPE_3__* OptionalHeader; TYPE_4__* FileHeader; int /*<<< orphan*/  ImageBase; TYPE_5__* DosHeader; scalar_t__ cbInFileSize; } ;
struct TYPE_12__ {scalar_t__ e_magic; long e_lfanew; } ;
struct TYPE_11__ {scalar_t__ Machine; int SizeOfOptionalHeader; int PointerToSymbolTable; int NumberOfSymbols; int NumberOfSections; } ;
struct TYPE_10__ {int CheckSum; int FileAlignment; int /*<<< orphan*/  ImageBase; } ;
struct TYPE_9__ {int PointerToRawData; int SizeOfRawData; int Characteristics; scalar_t__ Name; } ;
typedef  TYPE_2__* PIMAGE_SECTION_HEADER ;
typedef  TYPE_3__* PIMAGE_OPTIONAL_HEADER64 ;
typedef  TYPE_4__* PIMAGE_FILE_HEADER ;
typedef  TYPE_5__* PIMAGE_DOS_HEADER ;
typedef  TYPE_6__* PFILE_INFO ;
typedef  int /*<<< orphan*/  IMAGE_SECTION_HEADER ;
typedef  int /*<<< orphan*/  IMAGE_FILE_HEADER ;
typedef  int DWORD ;

/* Variables and functions */
 int CalculateChecksum (int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ IMAGE_DOS_MAGIC ; 
 scalar_t__ IMAGE_FILE_MACHINE_AMD64 ; 
 int ROUND_UP (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 unsigned long strtoul (char*,int /*<<< orphan*/ ,int) ; 

int
ParsePEHeaders(PFILE_INFO File)
{
    DWORD OldChecksum, Checksum;
    ULONG Alignment, CurrentPos;
    int i, j;

    /* Check if MZ header exists  */
    File->DosHeader = (PIMAGE_DOS_HEADER)File->FilePtr;
    if ((File->DosHeader->e_magic != IMAGE_DOS_MAGIC) || 
        (File->DosHeader->e_lfanew == 0L))
    {
        perror("Input file is not a PE image.\n");
        return -1;
    }

    /* Locate PE file header  */
    File->FileHeader = (PIMAGE_FILE_HEADER)(File->FilePtr + 
                               File->DosHeader->e_lfanew + sizeof(ULONG));

    /* Check for x64 image */
    if (File->FileHeader->Machine != IMAGE_FILE_MACHINE_AMD64)
    {
        perror("Input file is not an x64 image.\n");
        return -1;
    }

    /* Locate optional header */
    File->OptionalHeader = (PIMAGE_OPTIONAL_HEADER64)(File->FileHeader + 1);

    /* Check if checksum is correct */
    OldChecksum = File->OptionalHeader->CheckSum;
    File->OptionalHeader->CheckSum = 0;
    Checksum = CalculateChecksum(0, File->FilePtr, File->cbInFileSize);
    Checksum += File->cbInFileSize;
    if ((Checksum & 0xffff) != (OldChecksum & 0xffff))
    {
        fprintf(stderr, "Input file has incorrect PE checksum: 0x%lx (calculated: 0x%lx)\n",
            OldChecksum, Checksum);
//        return 0;
    }

    /* Locate PE section headers  */
    File->SectionHeaders = (PIMAGE_SECTION_HEADER)((char*)File->OptionalHeader
                           + File->FileHeader->SizeOfOptionalHeader);

    File->HeaderSize = File->DosHeader->e_lfanew
                       + sizeof(ULONG)
                       + sizeof(IMAGE_FILE_HEADER)
                       + File->FileHeader->SizeOfOptionalHeader;

    if (!File->FileHeader->PointerToSymbolTable)
    {
        fprintf(stderr, "No symbol table.\n");
        return -1;
    }

    /* Create some shortcuts */
    File->ImageBase = File->OptionalHeader->ImageBase;
    File->Symbols = File->FilePtr + File->FileHeader->PointerToSymbolTable;
    File->Strings = (char*)File->Symbols + File->FileHeader->NumberOfSymbols * 18;

    /* Check section names */
    File->AllSections = File->FileHeader->NumberOfSections;
    Alignment = File->OptionalHeader->FileAlignment;
    File->NewSectionHeaders = malloc((File->AllSections+2) * sizeof(IMAGE_SECTION_HEADER));
    File->UsedSections = 0;
    File->eh_frame.idx = -1;

    /* Allocate array of chars, specifiying whether to copy the section */
    File->UseSection = malloc(File->AllSections);

    for (i = 0; i < File->AllSections; i++)
    {
        char *pName = (char*)File->SectionHeaders[i].Name;
        File->UseSection[i] = 1;

        /* Check for long name */
        if (pName[0] == '/')
        {
            unsigned long index = strtoul(pName+1, 0, 10);
            pName = File->Strings + index;
            
            // Hack, simply remove all sections with long names
            File->UseSection[i] = 0;
        }

        /* Chek if we have the eh_frame section */
        if (strcmp(pName, ".eh_frame") == 0)
        {
            File->eh_frame.psh = &File->SectionHeaders[i];
            File->eh_frame.idx = i;
            File->eh_frame.p = File->FilePtr + File->eh_frame.psh->PointerToRawData;
        }
        
        /* Increase number of used sections */
        if (File->UseSection[i])
            File->UsedSections = i+1;

    }

    /* This is the actual size of the new section headers */
    File->NewSectionHeaderSize = 
        (File->UsedSections+2) * sizeof(IMAGE_SECTION_HEADER);

    /* Calculate the position to start writing the sections to */
    CurrentPos = File->HeaderSize + File->NewSectionHeaderSize;
    CurrentPos = ROUND_UP(CurrentPos, Alignment);

    /* Create new section headers */
    for (i = 0, j = 0; i < File->UsedSections; i++)
    {
        /* Copy section header */
        File->NewSectionHeaders[j] = File->SectionHeaders[i];

        /* Shall we strip the section? */
        if (File->UseSection[i] == 0)
        {
            /* Make it a bss section */
            File->NewSectionHeaders[j].PointerToRawData = 0;
            File->NewSectionHeaders[j].SizeOfRawData = 0;
            File->NewSectionHeaders[j].Characteristics = 0xC0500080;
        }

        /* Fix Offset into File */
        File->NewSectionHeaders[j].PointerToRawData =
              File->NewSectionHeaders[j].PointerToRawData ? CurrentPos : 0;
        CurrentPos += File->NewSectionHeaders[j].SizeOfRawData;
        j++;
    }

    if (File->eh_frame.idx == -1)
    {
        //fprintf(stderr, "No .eh_frame section found\n");
        return 0;
    }

    return 1;
}