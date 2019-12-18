#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ULONG ;
typedef  char* PCHAR ;
typedef  int INT ;
typedef  char CHAR ;

/* Variables and functions */
 int BuildType ; 
 int DoParsing () ; 
 int FallbackDriver ; 
 int NoLogo ; 
 int /*<<< orphan*/  PrintUsage () ; 
 int SanityCheck ; 
 int SourceOnly ; 
 int UnicodeFile ; 
 int Verbose ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int gSubVersion ; 
 int gVersion ; 
 int /*<<< orphan*/  gfpInput ; 
 char* gpszFileName ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

INT
main(INT argc,
     PCHAR* argv)
{
    int i;
    ULONG ErrorCode, FailureCode;
    CHAR Option;
    PCHAR OpenFlags;
    CHAR BuildOptions[16] = {0};

    /* Loop for parameter */
    for (i = 1; i < argc; ++i)
    {
        if (argv[i][0] != '/' && argv[i][0] != '-')
            break;

        if (argv[i][1] && !argv[i][2])
            Option = argv[i][1];
        else
            Option = 0;

        /* Check supported options */
        switch (Option)
        {
            /* ASCII File */
            case 'A':
            case 'a':
                UnicodeFile = 0;
                break;

            /* UNICODE File */
            case 'U':
            case 'u':
                UnicodeFile = 1;
                break;

            /* Verbose */
            case 'V':
            case 'v':
                Verbose = 1;
                break;

            /* No logo */
            case 'N':
            case 'n':
                NoLogo = 1;
                break;

            /* Fallback driver */
            case 'K':
            case 'k':
                FallbackDriver = 1;
                break;

            /* Sanity Check */
            case 'W':
            case 'w':
                SanityCheck = 1;
                break;

            /* Itanium */
            case 'I':
            case 'i':
                BuildType = 1;
                break;

            /* X86 */
            case 'X':
            case 'x':
                BuildType = 0;
                break;

            /* AMD64 */
            case 'M':
            case 'm':
                BuildType = 2;
                break;

            /* WOW64 */
            case 'O':
            case 'o':
                BuildType = 3;
                break;

            /* Source only */
            case 'S':
            case 's':
                SourceOnly = 1;
                break;

            default:
                /* If you got here, the options are invalid or missing */
                PrintUsage();
                break;
        }
    }

    /* Do we have no options? */
    if (i == argc) PrintUsage();

    /* Should we announce ourselves? */
    if (!NoLogo)
    {
        /* This is who we are */
        printf("\nKbdTool v%d.%02d - convert keyboard text file to C file or a keyboard layout DLL\n\n",
               gVersion, gSubVersion);
    }

    /* Save the file name */
    gpszFileName = argv[i];

    /* Open either as binary or text */
    OpenFlags = "rb";
    if (!UnicodeFile) OpenFlags = "rt";

    /* Open a handle to the file */
    gfpInput = fopen(gpszFileName, OpenFlags);
    if (!gfpInput)
    {
        /* Couldn't open it */
        printf("Unable to open '%s' for read.\n", gpszFileName);
        exit(1);
    }

    /* Should we print out what we're doing? */
    if (!NoLogo)
    {
        /* Are we only building the source files? */
        if (SourceOnly)
        {
            /* Then there's no target architecture */
            strcpy(BuildOptions, "source files");
        }
        else
        {
            /* Take a look at the target architecture*/
            switch (BuildType)
            {
                /* Print the appropriate message depending on what was chosen */
                case 0:
                    strcpy(BuildOptions, "i386/x86");
                    break;
                case 1:
                    strcpy(BuildOptions, "ia64");
                    break;
                case 2:
                    strcpy(BuildOptions, "amd64/x64");
                    break;
                case 3:
                    strcpy(BuildOptions, "wow64");
                    break;
                default:
                    strcpy(BuildOptions, "unknown purpose");
                    break;
            }
        }

        /* Now inform the user */
        printf("Compiling layout information from '%s' for %s.\n", gpszFileName, BuildOptions);
    }

    /* Now parse the keywords */
    FailureCode = DoParsing();

    /* Should we build? */
    if (!(SourceOnly) && !(FallbackDriver)) ErrorCode = 0;//DoBuild();

    /* Did everything work? */
    if (FailureCode == 0)
    {
        /* Tell the user, if he cares */
        if (!NoLogo) printf("All tasks completed successfully.\n");
    }
    else
    {
        /* Print the failure code */
        printf("\n     %13d\n", FailureCode);
    }

    /* Return the error code */
    return ErrorCode;
}