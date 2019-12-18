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
 int /*<<< orphan*/  DEF_OPT_DIR ; 
 int /*<<< orphan*/  LINESIZE ; 
 int /*<<< orphan*/  PATH_STR ; 
 int getopt (int,char** const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2l_dbg (int,char*,...) ; 
 scalar_t__* malloc (int /*<<< orphan*/ ) ; 
 scalar_t__* opt_7z ; 
 int /*<<< orphan*/  opt_Mark ; 
 scalar_t__* opt_Revision ; 
 int /*<<< orphan*/  opt_Revision_check ; 
 int /*<<< orphan*/  opt_Source ; 
 scalar_t__* opt_SourcesPath ; 
 int /*<<< orphan*/  opt_SrcPlus ; 
 int /*<<< orphan*/  opt_Twice ; 
 int /*<<< orphan*/  opt_buffered ; 
 scalar_t__ opt_console ; 
 scalar_t__* opt_dir ; 
 int /*<<< orphan*/  opt_exit ; 
 int /*<<< orphan*/  opt_force ; 
 int /*<<< orphan*/  opt_help ; 
 int /*<<< orphan*/  opt_mark ; 
 int /*<<< orphan*/  opt_raw ; 
 int /*<<< orphan*/  opt_redo ; 
 scalar_t__ opt_stats ; 
 int /*<<< orphan*/  opt_twice ; 
 int /*<<< orphan*/  opt_undo ; 
 int /*<<< orphan*/  opt_verbose ; 
 scalar_t__* optarg ; 
 int /*<<< orphan*/  optchars ; 
 int sscanf (scalar_t__*,char*,scalar_t__*,...) ; 
 int /*<<< orphan*/  strcat (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (scalar_t__*,char*) ; 
 int /*<<< orphan*/  strcpy (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  usage (int) ; 

int optionParse(int argc, const char **argv)
{
    int i;
    int optCount = 0;
    int opt;

    while (-1 != (opt = getopt(argc, (char **const)argv, optchars)))
    {
        switch (opt)
        {
        case 'b':
            opt_buffered++;
            break;
        case 'c':
            opt_console++;
            break;
        case 'd':
            optCount++;
            //just count, see optionInit()
            break;
        case 'f':
            opt_force++;
            break;
        case 'h':
            opt_help++;
            usage(1);
            return -1;
            break;
        case 'F':
            opt_exit++;
            opt_force++;
            break;
        case 'l':
            optCount++;
            //just count, see optionInit()
            break;
        case 'm':
            opt_mark++;
            break;
        case 'M':
            opt_Mark++;
            break;
        case 'r':
            opt_raw++;
            break;
        case 'P':
            optCount++;
            //just count, see optionInit()
            break;
        case 'R':
            optCount++;
            if (!opt_Revision)
                opt_Revision = malloc(LINESIZE);
            sscanf(optarg, "%s", opt_Revision);
            if (strcmp(opt_Revision, "check") == 0)
                opt_Revision_check ++;
            break;
        case 's':
            opt_stats++;
            break;
        case 'S':
            optCount++;
            i = sscanf(optarg, "%d+%d,%s", &opt_Source, &opt_SrcPlus, opt_SourcesPath);
            if (i == 1)
                sscanf(optarg, "%*d,%s", opt_SourcesPath);
            l2l_dbg(3, "Sources option parse result: %d+%d,\"%s\"\n", opt_Source, opt_SrcPlus, opt_SourcesPath);
            if (opt_Source)
            {
                /* need to retranslate for source info: */
                opt_undo++;
                opt_redo++;
                opt_Revision_check ++;
            }
            break;
        case 't':
            opt_twice++;
            break;
        case 'T':
            opt_twice++;
            opt_Twice++;
            break;
        case 'u':
            opt_undo++;
            break;
        case 'U':
            opt_undo++;
            opt_redo++;
            break;
        case 'v':
            opt_verbose++;
            break;
        case 'z':
            optCount++;
            strcpy(opt_7z, optarg);
            break;
        default:
            usage(0);
            return -2;
            break;
        }
        optCount++;
    }
    if(opt_console)
    {
        l2l_dbg(2, "Note: use 's' command in console mode. Statistics option disabled\n");
        opt_stats = 0;
    }
    if (opt_SourcesPath[0])
    {
        strcat(opt_SourcesPath, PATH_STR);
    }
    if (!opt_dir[0])
    {
        strcpy(opt_dir, opt_SourcesPath);
        strcat(opt_dir, DEF_OPT_DIR);
    }

    return optCount;
}