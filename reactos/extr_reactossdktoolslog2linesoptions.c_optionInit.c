#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  buildrev; int /*<<< orphan*/  range; int /*<<< orphan*/  rev; } ;

/* Variables and functions */
 char const* CMD_7Z ; 
 int /*<<< orphan*/  DEF_RANGE ; 
 int /*<<< orphan*/  LINESIZE ; 
 int /*<<< orphan*/  SOURCES_ENV ; 
 int /*<<< orphan*/  getRevision (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  getTBRevision (int /*<<< orphan*/ ) ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2l_dbg (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_7z ; 
 int /*<<< orphan*/  opt_Pipe ; 
 int /*<<< orphan*/  opt_SourcesPath ; 
 int /*<<< orphan*/  opt_dir ; 
 int /*<<< orphan*/  opt_help ; 
 int /*<<< orphan*/  opt_logFile ; 
 char* opt_mod ; 
 int /*<<< orphan*/  opt_scanned ; 
 TYPE_1__ revinfo ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  usage (int) ; 

int optionInit(int argc, const char **argv)
{
    int i;
    char *s;

    opt_mod = "a";
    strcpy(opt_dir, "");
    strcpy(opt_logFile, "");
    strcpy(opt_7z, CMD_7Z);
    strcpy(opt_SourcesPath, "");
    if ((s = getenv(SOURCES_ENV)))
        strcpy(opt_SourcesPath, s);
    revinfo.rev = getRevision(NULL, 1);
    revinfo.range = DEF_RANGE;
    revinfo.buildrev = getTBRevision(opt_dir);
    l2l_dbg(1, "Trunk build revision: %d\n", revinfo.buildrev);

    strcpy(opt_scanned, "");

    //The user introduced "log2lines.exe" or "log2lines.exe /?"
    //Let's help the user
    if ((argc == 1) ||
        ((argc == 2) && (argv[1][0] == '/') && (argv[1][1] == '?')))
    {
        opt_help++;
        usage(1);
        return -1;
    }

    for (i = 1; i < argc; i++)
    {

        if ((argv[i][0] == '-') && (i+1 < argc))
        {
            //Because these arguments can contain spaces we cant use getopt(), a known bug:
            switch (argv[i][1])
            {
            case 'd':
                strcpy(opt_dir, argv[i+1]);
                break;
            case 'L':
                opt_mod = "w";
                //fall through
            case 'l':
                strcpy(opt_logFile, argv[i+1]);
                break;
            case 'P':
                if (!opt_Pipe)
                    opt_Pipe = malloc(LINESIZE);
                strcpy(opt_Pipe, argv[i+1]);
                break;
            case 'z':
                strcpy(opt_7z, argv[i+1]);
                break;
            }
        }

        strcat(opt_scanned, argv[i]);
        strcat(opt_scanned, " ");
    }

    l2l_dbg(4,"opt_scanned=[%s]\n",opt_scanned);

    return 0;
}