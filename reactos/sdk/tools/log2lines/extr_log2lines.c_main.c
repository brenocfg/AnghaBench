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
typedef  int /*<<< orphan*/  REVINFO ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  LINESIZE ; 
 int /*<<< orphan*/  PCLOSE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POPEN (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cache ; 
 scalar_t__ check_directory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clearLastLine () ; 
 int /*<<< orphan*/  conIn ; 
 int /*<<< orphan*/  conOut ; 
 int /*<<< orphan*/  create_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbgIn ; 
 int /*<<< orphan*/  dbgOut ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ isOffset (char const*) ; 
 int /*<<< orphan*/  l2l_dbg (int,char*,...) ; 
 int /*<<< orphan*/  list_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ logFile ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * opt_Pipe ; 
 int /*<<< orphan*/ * opt_Revision ; 
 scalar_t__ opt_exit ; 
 int /*<<< orphan*/  opt_force ; 
 int optionInit (int,char const**) ; 
 int optionParse (int,char const**) ; 
 int /*<<< orphan*/  read_cache () ; 
 int /*<<< orphan*/  report (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revinfo ; 
 scalar_t__ set_LogFile (scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  sources ; 
 int /*<<< orphan*/  stat_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  summ ; 
 int /*<<< orphan*/  translate_files (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  translate_line (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int updateSvnlog () ; 

int
main(int argc, const char **argv)
{
    int res = 0;
    int optInit = 0;
    int optCount = 0;

    dbgIn = stdin;
    conOut = stdout;
    (void)conIn;
    (void)dbgOut;

    memset(&cache, 0, sizeof(LIST));
    memset(&sources, 0, sizeof(LIST));
    stat_clear(&summ);
    memset(&revinfo, 0, sizeof(REVINFO));
    clearLastLine();

    optInit = optionInit(argc, argv);
    optCount = optionParse(argc, argv);

    if (optCount < 0 || optInit < 0)
    {
        res = optCount;
        goto cleanup;
    }

    argc -= optCount;

    if (opt_Revision && (strcmp(opt_Revision, "update") == 0))
    {
        res = updateSvnlog();
        goto cleanup;
    }

    if (check_directory(opt_force))
    {
        res = 3;
        goto cleanup;
    }

    create_cache(opt_force, 0);
    if (opt_exit)
    {
        res = 0;
        goto cleanup;
    }

    read_cache();
    l2l_dbg(4, "Cache read complete\n");

    if (set_LogFile(&logFile))
    {
        res = 2;
        goto cleanup;
    }
    l2l_dbg(4, "opt_logFile processed\n");

    if (opt_Pipe)
    {
        l2l_dbg(3, "Command line: \"%s\"\n",opt_Pipe);

        if (!(dbgIn = POPEN(opt_Pipe, "r")))
        {
            dbgIn = stdin; //restore
            l2l_dbg(0, "Could not popen '%s' (%s)\n", opt_Pipe, strerror(errno));
            free(opt_Pipe);
            opt_Pipe = NULL;
        }
    }
    l2l_dbg(4, "opt_Pipe processed\n");

    if (argc > 1)
    {   // translate {<exefile> <offset>}
        int i = 1;
        const char *exefile = NULL;
        const char *offset = NULL;
        char Line[LINESIZE + 1];
        char PathBuffer[LINESIZE + 1];
        char LineOutBuffer[LINESIZE + 1];

        // TODO: Re-use one translate_files(), instead of repeated translate_line().
        while (i < argc)
        {
            offset = argv[optCount + i++];
            if (isOffset(offset))
            {
                if (exefile)
                {
                    l2l_dbg(2, "translating %s %s\n", exefile, offset);

                    snprintf(Line, LINESIZE, "<%s:%s>\n", exefile, offset);
                    translate_line(conOut, Line, PathBuffer, LineOutBuffer);
                    report(conOut);
                }
                else
                {
                    l2l_dbg(0, "<exefile> expected\n");
                    res = 3;
                    break;
                }
            }
            else
            {
                // Not an offset so must be an exefile:
                exefile = offset;
            }
        }
    }
    else
    {   // translate logging from stdin
        translate_files(dbgIn, conOut);
    }

    if (logFile)
        fclose(logFile);

    if (opt_Pipe)
        PCLOSE(dbgIn);

cleanup:
    // See optionParse().
    if (opt_Revision)
    {
        free(opt_Revision);
        opt_Revision = NULL;
    }

    // See optionInit().
    if (opt_Pipe)
    {
        free(opt_Pipe);
        opt_Pipe = NULL;
    }

    list_clear(&sources);
    list_clear(&cache);

    return res;
}