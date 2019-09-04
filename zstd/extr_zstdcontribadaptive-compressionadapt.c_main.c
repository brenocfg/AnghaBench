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

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*) ; 
 scalar_t__ ZSTD_maxCLevel () ; 
 int compressFilename (char const*,char const*) ; 
 int compressFilenames (char const**,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  free (char const**) ; 
 scalar_t__ g_compressionLevel ; 
 int /*<<< orphan*/  g_displayLevel ; 
 int g_forceCompressionLevel ; 
 scalar_t__ g_maxCLevel ; 
 scalar_t__ g_minCLevel ; 
 int /*<<< orphan*/  g_useProgressBar ; 
 int /*<<< orphan*/  help (char const*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ readU32FromChar (char const**) ; 
 char* stdinmark ; 
 char* stdoutmark ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 

int main(int argCount, const char* argv[])
{
    const char* outFilename = NULL;
    const char** filenameTable = (const char**)malloc(argCount*sizeof(const char*));
    unsigned filenameIdx = 0;
    unsigned forceStdout = 0;
    unsigned providedInitialCLevel = 0;
    int ret = 0;
    int argNum;
    filenameTable[0] = stdinmark;
    g_maxCLevel = ZSTD_maxCLevel();

    if (filenameTable == NULL) {
        DISPLAY("Error: could not allocate sapce for filename table.\n");
        return 1;
    }

    for (argNum=1; argNum<argCount; argNum++) {
        const char* argument = argv[argNum];

        /* output filename designated with "-o" */
        if (argument[0]=='-' && strlen(argument) > 1) {
            switch (argument[1]) {
                case 'o':
                    argument += 2;
                    outFilename = argument;
                    break;
                case 'i':
                    argument += 2;
                    g_compressionLevel = readU32FromChar(&argument);
                    providedInitialCLevel = 1;
                    break;
                case 'h':
                    help(argv[0]);
                    goto _main_exit;
                case 'p':
                    g_useProgressBar = 0;
                    break;
                case 'c':
                    forceStdout = 1;
                    outFilename = stdoutmark;
                    break;
                case 'f':
                    g_forceCompressionLevel = 1;
                    break;
                case 'q':
                    g_useProgressBar = 0;
                    g_displayLevel = 0;
                    break;
                case 'l':
                    argument += 2;
                    g_minCLevel = readU32FromChar(&argument);
                    break;
                case 'u':
                    argument += 2;
                    g_maxCLevel = readU32FromChar(&argument);
                    break;
                default:
                    DISPLAY("Error: invalid argument provided\n");
                    ret = 1;
                    goto _main_exit;
            }
            continue;
        }

        /* regular files to be compressed */
        filenameTable[filenameIdx++] = argument;
    }

    /* check initial, max, and min compression levels */
    {
        unsigned const minMaxInconsistent = g_minCLevel > g_maxCLevel;
        unsigned const initialNotInRange = g_minCLevel > g_compressionLevel || g_maxCLevel < g_compressionLevel;
        if (minMaxInconsistent || (initialNotInRange && providedInitialCLevel)) {
            DISPLAY("Error: provided compression level parameters are invalid\n");
            ret = 1;
            goto _main_exit;
        }
        else if (initialNotInRange) {
            g_compressionLevel = g_minCLevel;
        }
    }

    /* error checking with number of files */
    if (filenameIdx > 1 && (outFilename != NULL && strcmp(outFilename, stdoutmark))) {
        DISPLAY("Error: multiple input files provided, cannot use specified output file\n");
        ret = 1;
        goto _main_exit;
    }

    /* compress files */
    if (filenameIdx <= 1) {
        ret |= compressFilename(filenameTable[0], outFilename);
    }
    else {
        ret |= compressFilenames(filenameTable, filenameIdx, forceStdout);
    }
_main_exit:
    free(filenameTable);
    return ret;
}