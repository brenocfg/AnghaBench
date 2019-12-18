#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  achDllName ;
struct TYPE_7__ {scalar_t__ bVersionIncluded; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ EXPORT ;

/* Variables and functions */
 scalar_t__ ARCH_AMD64 ; 
 scalar_t__ ARCH_ARM ; 
 scalar_t__ ARCH_IA64 ; 
 scalar_t__ ARCH_PPC ; 
 scalar_t__ ARCH_X86 ; 
 int /*<<< orphan*/  OutputHeader_asmstub (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  OutputHeader_def (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  OutputHeader_stub (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutputLine_asmstub (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  OutputLine_def (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  OutputLine_stub (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* ParseFile (char*,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ftell (int /*<<< orphan*/ *) ; 
 int gbImportLib ; 
 int gbMSComp ; 
 int gbNotPrivateNoWarn ; 
 int gbTracing ; 
 scalar_t__ giArch ; 
 char* gpszUnderscore ; 
 int /*<<< orphan*/  guOsVersion ; 
 char* malloc (size_t) ; 
 char* pszArchString ; 
 char* pszArchString2 ; 
 char* pszDllName ; 
 char* pszSourceFileName ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stderr ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncasecmp (char*,char const*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char *argv[])
{
    size_t nFileSize;
    char *pszSource, *pszDefFileName = NULL, *pszStubFileName = NULL, *pszLibStubName = NULL;
    const char* pszVersionOption = "--version=0x";
    char achDllName[40];
    FILE *file;
    unsigned cExports = 0, i;
    EXPORT *pexports;

    if (argc < 2)
    {
        usage();
        return -1;
    }

    /* Read options */
    for (i = 1; i < (unsigned)argc && *argv[i] == '-'; i++)
    {
        if ((strcasecmp(argv[i], "--help") == 0) ||
            (strcasecmp(argv[i], "-h") == 0))
        {
            usage();
            return 0;
        }
        else if (argv[i][1] == 'd' && argv[i][2] == '=')
        {
            pszDefFileName = argv[i] + 3;
        }
        else if (argv[i][1] == 'l' && argv[i][2] == '=')
        {
            pszLibStubName = argv[i] + 3;
        }
        else if (argv[i][1] == 's' && argv[i][2] == '=')
        {
            pszStubFileName = argv[i] + 3;
        }
        else if (argv[i][1] == 'n' && argv[i][2] == '=')
        {
            pszDllName = argv[i] + 3;
        }
        else if (strncasecmp(argv[i], pszVersionOption, strlen(pszVersionOption)) == 0)
        {
            guOsVersion = strtoul(argv[i] + strlen(pszVersionOption), NULL, 16);
        }
        else if (strcasecmp(argv[i], "--implib") == 0)
        {
            gbImportLib = 1;
        }
        else if (strcasecmp(argv[i], "--ms") == 0)
        {
            gbMSComp = 1;
        }
        else if (strcasecmp(argv[i], "--no-private-warnings") == 0)
        {
            gbNotPrivateNoWarn = 1;
        }
        else if (strcasecmp(argv[i], "--with-tracing") == 0)
        {
            if (!pszStubFileName)
            {
                fprintf(stderr, "Error: cannot use --with-tracing without -s option.\n");
                return -1;
            }
            gbTracing = 1;
        }
        else if (argv[i][1] == 'a' && argv[i][2] == '=')
        {
            pszArchString = argv[i] + 3;
        }
        else
        {
            fprintf(stderr, "Unrecognized option: %s\n", argv[i]);
            return -1;
        }
    }

    if (strcasecmp(pszArchString, "i386") == 0)
    {
        giArch = ARCH_X86;
        gpszUnderscore = "_";
    }
    else if (strcasecmp(pszArchString, "x86_64") == 0) giArch = ARCH_AMD64;
    else if (strcasecmp(pszArchString, "ia64") == 0) giArch = ARCH_IA64;
    else if (strcasecmp(pszArchString, "arm") == 0) giArch = ARCH_ARM;
    else if (strcasecmp(pszArchString, "ppc") == 0) giArch = ARCH_PPC;

    if ((giArch == ARCH_AMD64) || (giArch == ARCH_IA64))
    {
        pszArchString2 = "win64";
    }
    else
        pszArchString2 = "win32";

    /* Set a default dll name */
    if (!pszDllName)
    {
        char *p1, *p2;
        size_t len;

        p1 = strrchr(argv[i], '\\');
        if (!p1) p1 = strrchr(argv[i], '/');
        p2 = p1 = p1 ? p1 + 1 : argv[i];

        /* walk up to '.' */
        while (*p2 != '.' && *p2 != 0) p2++;
        len = p2 - p1;
        if (len >= sizeof(achDllName) - 5)
        {
            fprintf(stderr, "name too long: %s\n", p1);
            return -2;
        }

        strncpy(achDllName, p1, len);
        strncpy(achDllName + len, ".dll", sizeof(achDllName) - len);
        pszDllName = achDllName;
    }

    /* Open input file */
    pszSourceFileName = argv[i];
    file = fopen(pszSourceFileName, "r");
    if (!file)
    {
        fprintf(stderr, "error: could not open file %s\n", pszSourceFileName);
        return -3;
    }

    /* Get file size */
    fseek(file, 0, SEEK_END);
    nFileSize = ftell(file);
    rewind(file);

    /* Allocate memory buffer */
    pszSource = malloc(nFileSize + 1);
    if (!pszSource)
    {
        fclose(file);
        return -4;
    }

    /* Load input file into memory */
    nFileSize = fread(pszSource, 1, nFileSize, file);
    fclose(file);

    /* Zero terminate the source */
    pszSource[nFileSize] = '\0';

    pexports = ParseFile(pszSource, file, &cExports);
    if (pexports == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for export data!\n");
        return -1;
    }

    if (pszDefFileName)
    {
        /* Open output file */
        file = fopen(pszDefFileName, "w");
        if (!file)
        {
            fprintf(stderr, "error: could not open output file %s\n", argv[i + 1]);
            return -5;
        }

        OutputHeader_def(file, pszDllName);

        for (i = 0; i < cExports; i++)
        {
            if (pexports[i].bVersionIncluded)
                 OutputLine_def(file, &pexports[i]);
        }

        fclose(file);
    }

    if (pszStubFileName)
    {
        /* Open output file */
        file = fopen(pszStubFileName, "w");
        if (!file)
        {
            fprintf(stderr, "error: could not open output file %s\n", argv[i + 1]);
            return -5;
        }

        OutputHeader_stub(file);

        for (i = 0; i < cExports; i++)
        {
            if (pexports[i].bVersionIncluded)
                OutputLine_stub(file, &pexports[i]);
        }

        fclose(file);
    }

    if (pszLibStubName)
    {
        /* Open output file */
        file = fopen(pszLibStubName, "w");
        if (!file)
        {
            fprintf(stderr, "error: could not open output file %s\n", argv[i + 1]);
            return -5;
        }

        OutputHeader_asmstub(file, pszDllName);

        for (i = 0; i < cExports; i++)
        {
            if (pexports[i].bVersionIncluded)
                OutputLine_asmstub(file, &pexports[i]);
        }

        fprintf(file, "\n    END\n");
        fclose(file);
    }

    free(pexports);

    return 0;
}