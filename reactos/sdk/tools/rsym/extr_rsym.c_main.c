#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  elfhdr ;
typedef  scalar_t__ ULONG ;
struct TYPE_16__ {scalar_t__ e_magic; long e_lfanew; } ;
struct TYPE_15__ {int SizeOfOptionalHeader; } ;
struct TYPE_14__ {scalar_t__ ImageBase; } ;
struct TYPE_13__ {int SymbolsOffset; int StringsOffset; scalar_t__ StringsLength; scalar_t__ SymbolsLength; } ;
typedef  int /*<<< orphan*/  SYMBOLFILE_HEADER ;
typedef  int /*<<< orphan*/  ROSSYM_ENTRY ;
typedef  TYPE_1__* PSYMBOLFILE_HEADER ;
typedef  void* PROSSYM_ENTRY ;
typedef  scalar_t__ PIMAGE_SECTION_HEADER ;
typedef  TYPE_2__* PIMAGE_OPTIONAL_HEADER ;
typedef  TYPE_3__* PIMAGE_FILE_HEADER ;
typedef  TYPE_4__* PIMAGE_DOS_HEADER ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ ConvertCoffs (scalar_t__*,void**,scalar_t__*,void*,scalar_t__,void*,scalar_t__,void*,scalar_t__,TYPE_3__*,scalar_t__) ; 
 scalar_t__ ConvertDbgHelp (void*,int,char*,scalar_t__*,void**,scalar_t__*,void**) ; 
 scalar_t__ ConvertStabs (scalar_t__*,void**,scalar_t__*,void*,scalar_t__,void*,scalar_t__,void*,scalar_t__,TYPE_3__*,scalar_t__) ; 
 scalar_t__ CreateOutputFile (int /*<<< orphan*/ *,void*,TYPE_4__*,TYPE_3__*,TYPE_2__*,scalar_t__,scalar_t__,void*) ; 
 int E_SYMNMLEN ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetCoffInfo (void*,TYPE_3__*,scalar_t__,scalar_t__*,void**,scalar_t__*,void**) ; 
 scalar_t__ GetStabInfo (void*,TYPE_3__*,scalar_t__,scalar_t__*,void**,scalar_t__*,void**) ; 
 scalar_t__ IMAGE_DOS_MAGIC ; 
 scalar_t__ MergeStabsAndCoffs (scalar_t__*,void**,scalar_t__,void*,scalar_t__,void*) ; 
 int /*<<< orphan*/  SymCleanup (void*) ; 
 int /*<<< orphan*/  SymInitialize (void*,char*,int /*<<< orphan*/ ) ; 
 int SymLoadModule (void*,void*,char*,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  SymSetOptions (int) ; 
 int /*<<< orphan*/  SymUnloadModule (void*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 char* convert_path (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 void* fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* load_file (char*,size_t*) ; 
 void* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcmp (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,void*,scalar_t__) ; 
 int /*<<< orphan*/  memset (void*,char,scalar_t__) ; 
 int /*<<< orphan*/  perror (char*) ; 
 void* realloc (void*,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strdup (char*) ; 

int main(int argc, char* argv[])
{
    PSYMBOLFILE_HEADER SymbolFileHeader;
    PIMAGE_DOS_HEADER PEDosHeader;
    PIMAGE_FILE_HEADER PEFileHeader;
    PIMAGE_OPTIONAL_HEADER PEOptHeader;
    PIMAGE_SECTION_HEADER PESectionHeaders;
    ULONG ImageBase;
    void *StabBase;
    ULONG StabsLength;
    void *StabStringBase;
    ULONG StabStringsLength;
    void *CoffBase = NULL;
    ULONG CoffsLength;
    void *CoffStringBase = NULL;
    ULONG CoffStringsLength;
    char* path1;
    char* path2;
    FILE* out;
    void *StringBase = NULL;
    ULONG StringsLength = 0;
    ULONG StabSymbolsCount = 0;
    PROSSYM_ENTRY StabSymbols = NULL;
    ULONG CoffSymbolsCount = 0;
    PROSSYM_ENTRY CoffSymbols = NULL;
    ULONG MergedSymbolsCount = 0;
    PROSSYM_ENTRY MergedSymbols = NULL;
    size_t FileSize;
    void *FileData;
    ULONG RosSymLength;
    void *RosSymSection;
    DWORD module_base;
    void *file;
    char elfhdr[4] = { '\177', 'E', 'L', 'F' };
    BOOLEAN UseDbgHelp = FALSE;
    int arg, argstate = 0;
    char *SourcePath = NULL;

    for (arg = 1; arg < argc; arg++)
    {
        switch (argstate)
        {
            default:
                argstate = -1;
                break;

            case 0:
                if (!strcmp(argv[arg], "-s"))
                {
                    argstate = 1;
                }
                else
                {
                    argstate = 2;
                    path1 = convert_path(argv[arg]);
                }
            break;

            case 1:
                free(SourcePath);
                SourcePath = strdup(argv[arg]);
                argstate = 0;
                break;

            case 2:
                path2 = convert_path(argv[arg]);
                argstate = 3;
                break;
        }
    }

    if (argstate != 3)
    {
        fprintf(stderr, "Usage: rsym [-s <sources>] <input> <output>\n");
        exit(1);
    }

    FileData = load_file(path1, &FileSize);
    if (!FileData)
    {
        fprintf(stderr, "An error occured loading '%s'\n", path1);
        exit(1);
    }

    file = fopen(path1, "rb");

    /* Check if MZ header exists  */
    PEDosHeader = (PIMAGE_DOS_HEADER) FileData;
    if (PEDosHeader->e_magic != IMAGE_DOS_MAGIC ||
        PEDosHeader->e_lfanew == 0L)
    {
        /* Ignore elf */
        if (!memcmp(PEDosHeader, elfhdr, sizeof(elfhdr)))
            exit(0);
        perror("Input file is not a PE image.\n");
        free(FileData);
        exit(1);
    }

    /* Locate PE file header  */
    /* sizeof(ULONG) = sizeof(MAGIC) */
    PEFileHeader = (PIMAGE_FILE_HEADER)((char *) FileData + PEDosHeader->e_lfanew + sizeof(ULONG));

    /* Locate optional header */
    assert(sizeof(ULONG) == 4);
    PEOptHeader = (PIMAGE_OPTIONAL_HEADER)(PEFileHeader + 1);
    ImageBase = PEOptHeader->ImageBase;

    /* Locate PE section headers  */
    PESectionHeaders = (PIMAGE_SECTION_HEADER)((char *) PEOptHeader + PEFileHeader->SizeOfOptionalHeader);

    if (GetStabInfo(FileData,
                    PEFileHeader,
                    PESectionHeaders,
                    &StabsLength,
                    &StabBase,
                    &StabStringsLength,
                    &StabStringBase))
    {
        free(FileData);
        exit(1);
    }

    if (StabsLength == 0)
    {
        // SYMOPT_AUTO_PUBLICS
        // SYMOPT_FAVOR_COMPRESSED
        // SYMOPT_LOAD_ANYTHING
        // SYMOPT_LOAD_LINES
        SymSetOptions(0x10000 | 0x800000 | 0x40 | 0x10);
        SymInitialize(FileData, ".", 0);

        module_base = SymLoadModule(FileData, file, path1, path1, 0, FileSize) & 0xffffffff;

        if (ConvertDbgHelp(FileData,
                           module_base,
                           SourcePath,
                           &StabSymbolsCount,
                           &StabSymbols,
                           &StringsLength,
                           &StringBase))
        {
            free(FileData);
            exit(1);
        }

        UseDbgHelp = TRUE;
        SymUnloadModule(FileData, module_base);
        SymCleanup(FileData);
    }

    if (GetCoffInfo(FileData,
                    PEFileHeader,
                    PESectionHeaders,
                    &CoffsLength,
                    &CoffBase,
                    &CoffStringsLength,
                    &CoffStringBase))
    {
        free(FileData);
        exit(1);
    }

    if (!UseDbgHelp)
    {
        StringBase = malloc(1 + StringsLength + CoffStringsLength +
                            (CoffsLength / sizeof(ROSSYM_ENTRY)) * (E_SYMNMLEN + 1));
        if (StringBase == NULL)
        {
            free(FileData);
            fprintf(stderr, "Failed to allocate memory for strings table\n");
            exit(1);
        }
        /* Make offset 0 into an empty string */
        *((char *) StringBase) = '\0';
        StringsLength = 1;

        if (ConvertStabs(&StabSymbolsCount,
                         &StabSymbols,
                         &StringsLength,
                         StringBase,
                         StabsLength,
                         StabBase,
                         StabStringsLength,
                         StabStringBase,
                         ImageBase,
                         PEFileHeader,
                         PESectionHeaders))
        {
            free(StringBase);
            free(FileData);
            fprintf(stderr, "Failed to allocate memory for strings table\n");
            exit(1);
        }
    }
    else
    {
        StringBase = realloc(StringBase, StringsLength + CoffStringsLength);
        if (!StringBase)
        {
            free(FileData);
            fprintf(stderr, "Failed to allocate memory for strings table\n");
            exit(1);
        }
    }

    if (ConvertCoffs(&CoffSymbolsCount,
                     &CoffSymbols,
                     &StringsLength,
                     StringBase,
                     CoffsLength,
                     CoffBase,
                     CoffStringsLength,
                     CoffStringBase,
                     ImageBase,
                     PEFileHeader,
                     PESectionHeaders))
    {
        if (StabSymbols)
        {
            free(StabSymbols);
        }
        free(StringBase);
        free(FileData);
        exit(1);
    }

    if (MergeStabsAndCoffs(&MergedSymbolsCount,
                           &MergedSymbols,
                           StabSymbolsCount,
                           StabSymbols,
                           CoffSymbolsCount,
                           CoffSymbols))
    {
        if (CoffSymbols)
        {
            free(CoffSymbols);
        }
        if (StabSymbols)
        {
            free(StabSymbols);
        }
        free(StringBase);
        free(FileData);
        exit(1);
    }

    if (CoffSymbols)
    {
        free(CoffSymbols);
    }
    if (StabSymbols)
    {
        free(StabSymbols);
    }
    if (MergedSymbolsCount == 0)
    {
        RosSymLength = 0;
        RosSymSection = NULL;
    }
    else
    {
        RosSymLength = sizeof(SYMBOLFILE_HEADER) +
                       MergedSymbolsCount * sizeof(ROSSYM_ENTRY) +
                       StringsLength;

        RosSymSection = malloc(RosSymLength);
        if (RosSymSection == NULL)
        {
            free(MergedSymbols);
            free(StringBase);
            free(FileData);
            fprintf(stderr, "Unable to allocate memory for .rossym section\n");
            exit(1);
        }
        memset(RosSymSection, '\0', RosSymLength);

        SymbolFileHeader = (PSYMBOLFILE_HEADER)RosSymSection;
        SymbolFileHeader->SymbolsOffset = sizeof(SYMBOLFILE_HEADER);
        SymbolFileHeader->SymbolsLength = MergedSymbolsCount * sizeof(ROSSYM_ENTRY);
        SymbolFileHeader->StringsOffset = SymbolFileHeader->SymbolsOffset +
                                          SymbolFileHeader->SymbolsLength;
        SymbolFileHeader->StringsLength = StringsLength;

        memcpy((char *) RosSymSection + SymbolFileHeader->SymbolsOffset,
               MergedSymbols,
               SymbolFileHeader->SymbolsLength);

        memcpy((char *) RosSymSection + SymbolFileHeader->StringsOffset,
               StringBase,
               SymbolFileHeader->StringsLength);

        free(MergedSymbols);
    }

    free(StringBase);
    out = fopen(path2, "wb");
    if (out == NULL)
    {
        perror("Cannot open output file");
        free(RosSymSection);
        free(FileData);
        exit(1);
    }

    if (CreateOutputFile(out,
                         FileData,
                         PEDosHeader,
                         PEFileHeader,
                         PEOptHeader,
                         PESectionHeaders,
                         RosSymLength,
                         RosSymSection))
    {
        fclose(out);
        if (RosSymSection)
        {
            free(RosSymSection);
        }
        free(FileData);
        exit(1);
    }

    fclose(out);
    if (RosSymSection)
    {
        free(RosSymSection);
    }
    free(FileData);

    return 0;
}