#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  elfhdr ;
struct TYPE_14__ {scalar_t__ e_magic; long e_lfanew; } ;
struct TYPE_13__ {int SizeOfOptionalHeader; unsigned int NumberOfSections; } ;
struct TYPE_11__ {scalar_t__ SizeOfImage; int /*<<< orphan*/  SectionAlignment; } ;
struct TYPE_12__ {TYPE_3__ OptionalHeader; TYPE_5__ FileHeader; } ;
struct TYPE_9__ {scalar_t__ VirtualSize; } ;
struct TYPE_10__ {int Characteristics; scalar_t__ SizeOfRawData; scalar_t__ PointerToRawData; scalar_t__ VirtualAddress; TYPE_1__ Misc; } ;
typedef  int /*<<< orphan*/  PSYMBOLFILE_HEADER ;
typedef  TYPE_2__* PIMAGE_SECTION_HEADER ;
typedef  TYPE_3__* PIMAGE_OPTIONAL_HEADER ;
typedef  TYPE_4__* PIMAGE_NT_HEADERS ;
typedef  TYPE_5__* PIMAGE_FILE_HEADER ;
typedef  TYPE_6__* PIMAGE_DOS_HEADER ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ IMAGE_DOS_MAGIC ; 
 int IMAGE_SCN_CNT_INITIALIZED_DATA ; 
 int IMAGE_SCN_MEM_DISCARDABLE ; 
 int IMAGE_SCN_MEM_PURGEABLE ; 
 scalar_t__ IsDebugSection (TYPE_2__*) ; 
 scalar_t__ ROUND_UP (scalar_t__,int /*<<< orphan*/ ) ; 
 char* convert_path (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  fwrite (void*,int,size_t,int /*<<< orphan*/ *) ; 
 void* load_file (char*,size_t*) ; 
 int /*<<< orphan*/  memcmp (TYPE_6__*,char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char* argv[])
{
    unsigned int i;
    PSYMBOLFILE_HEADER SymbolFileHeader;
    PIMAGE_NT_HEADERS NtHeaders;
    PIMAGE_DOS_HEADER DosHeader;
    PIMAGE_FILE_HEADER FileHeader;
    PIMAGE_OPTIONAL_HEADER OptionalHeader;
    PIMAGE_SECTION_HEADER SectionHeaders, LastSection;
    char* path1;
    char* path2;
    FILE* out;
    size_t FileSize;
    void *FileData;
    char elfhdr[] = { '\377', 'E', 'L', 'F' };

    if (argc != 3)
    {
        fprintf(stderr, "Usage: rsym <exefile> <symfile>\n");
        exit(1);
    }

    path1 = convert_path(argv[1]);
    path2 = convert_path(argv[2]);

    /* Load the input file into memory */
    FileData = load_file( path1, &FileSize);
    if ( !FileData )
    {
        fprintf(stderr, "An error occured loading '%s'\n", path1);
        exit(1);
    }

    /* Check if MZ header exists  */
    DosHeader = (PIMAGE_DOS_HEADER) FileData;
    if (DosHeader->e_magic != IMAGE_DOS_MAGIC || DosHeader->e_lfanew == 0L)
    {
        /* Ignore elf */
        if (!memcmp(DosHeader, elfhdr, sizeof(elfhdr)))
            exit(0);
        perror("Input file is not a PE image.\n");
        free(FileData);
        exit(1);
    }

    /* Locate the headers */
    NtHeaders = (PIMAGE_NT_HEADERS)((char*)FileData + DosHeader->e_lfanew);
    FileHeader = &NtHeaders->FileHeader;
    OptionalHeader = &NtHeaders->OptionalHeader;

    /* Locate PE section headers  */
    SectionHeaders = (PIMAGE_SECTION_HEADER)((char*)OptionalHeader +
                                             FileHeader->SizeOfOptionalHeader);

    /* Loop all sections */
    for (i = 0; i < FileHeader->NumberOfSections; i++)
    {
        /* Check if this is a debug section */
        if (IsDebugSection(&SectionHeaders[i]))
        {
            /* Make sure we have the correct characteristics */
            SectionHeaders[i].Characteristics |= IMAGE_SCN_CNT_INITIALIZED_DATA;
            SectionHeaders[i].Characteristics &= ~(IMAGE_SCN_MEM_PURGEABLE | IMAGE_SCN_MEM_DISCARDABLE);
        }
    }

    /* Get a pointer to the last section header */
    LastSection = &SectionHeaders[FileHeader->NumberOfSections - 1];

    /* Set the size of the last section to cover the rest of the PE */
    LastSection->SizeOfRawData = FileSize - LastSection->PointerToRawData;

    /* Check if the virtual section size is smaller than the raw data */
    if (LastSection->Misc.VirtualSize < LastSection->SizeOfRawData)
    {
        /* Make sure the virtual size of the section cover the raw data */
        LastSection->Misc.VirtualSize = ROUND_UP(LastSection->SizeOfRawData,
                                                 OptionalHeader->SectionAlignment);

        /* Fix up image size */
        OptionalHeader->SizeOfImage = LastSection->VirtualAddress +
                                      LastSection->Misc.VirtualSize;
    }

    /* Open the output file */
    out = fopen(path2, "wb");
    if (out == NULL)
    {
        perror("Cannot open output file");
        free(FileData);
        exit(1);
    }

    /* Write the output file */
    fwrite(FileData, 1, FileSize, out);
    fclose(out);
    free(FileData);

    return 0;
}