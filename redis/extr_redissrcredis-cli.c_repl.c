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
typedef  char* sds ;
struct TYPE_2__ {int interactive; char* prompt; int eval_ldb; scalar_t__ output; scalar_t__ eval_ldb_sync; scalar_t__ eval_ldb_end; int /*<<< orphan*/  hostport; int /*<<< orphan*/  hostip; scalar_t__ eval; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_FORCE ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ERANGE ; 
 scalar_t__ OUTPUT_RAW ; 
 scalar_t__ OUTPUT_STANDARD ; 
 int /*<<< orphan*/  REDIS_CLI_HISTFILE_DEFAULT ; 
 int /*<<< orphan*/  REDIS_CLI_HISTFILE_ENV ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  cliConnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cliInitHelp () ; 
 int /*<<< orphan*/  cliIntegrateHelp () ; 
 int /*<<< orphan*/  cliLoadPreferences () ; 
 int /*<<< orphan*/  cliReadReply (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cliRefreshPrompt () ; 
 int /*<<< orphan*/  cliSetPreferences (char**,int,int) ; 
 char** cliSplitArgs (char*,int*) ; 
 int /*<<< orphan*/  completionCallback ; 
 TYPE_1__ config ; 
 scalar_t__ context ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeHintsCallback ; 
 char* getDotfilePath (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hintsCallback ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  issueCommandRepeat (int,char**,long) ; 
 char* linenoise (char*) ; 
 int /*<<< orphan*/  linenoiseClearScreen () ; 
 int /*<<< orphan*/  linenoiseFree (char*) ; 
 int /*<<< orphan*/  linenoiseHistoryAdd (char*) ; 
 int /*<<< orphan*/  linenoiseHistoryLoad (char*) ; 
 int /*<<< orphan*/  linenoiseHistorySave (char*) ; 
 int /*<<< orphan*/  linenoiseSetCompletionCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linenoiseSetFreeHintsCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linenoiseSetHintsCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linenoiseSetMultiLine (int) ; 
 long long mstime () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfreesplitres (char**,int) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static void repl(void) {
    sds historyfile = NULL;
    int history = 0;
    char *line;
    int argc;
    sds *argv;

    /* Initialize the help and, if possible, use the COMMAND command in order
     * to retrieve missing entries. */
    cliInitHelp();
    cliIntegrateHelp();

    config.interactive = 1;
    linenoiseSetMultiLine(1);
    linenoiseSetCompletionCallback(completionCallback);
    linenoiseSetHintsCallback(hintsCallback);
    linenoiseSetFreeHintsCallback(freeHintsCallback);

    /* Only use history and load the rc file when stdin is a tty. */
    if (isatty(fileno(stdin))) {
        historyfile = getDotfilePath(REDIS_CLI_HISTFILE_ENV,REDIS_CLI_HISTFILE_DEFAULT);
        //keep in-memory history always regardless if history file can be determined
        history = 1;
        if (historyfile != NULL) {
            linenoiseHistoryLoad(historyfile);
        }
        cliLoadPreferences();
    }

    cliRefreshPrompt();
    while((line = linenoise(context ? config.prompt : "not connected> ")) != NULL) {
        if (line[0] != '\0') {
            long repeat = 1;
            int skipargs = 0;
            char *endptr = NULL;

            argv = cliSplitArgs(line,&argc);

            /* check if we have a repeat command option and
             * need to skip the first arg */
            if (argv && argc > 0) {
                errno = 0;
                repeat = strtol(argv[0], &endptr, 10);
                if (argc > 1 && *endptr == '\0') {
                    if (errno == ERANGE || errno == EINVAL || repeat <= 0) {
                        fputs("Invalid redis-cli repeat command option value.\n", stdout);
                        sdsfreesplitres(argv, argc);
                        linenoiseFree(line);
                        continue;
                    }
                    skipargs = 1;
                } else {
                    repeat = 1;
                }
            }

            /* Won't save auth command in history file */
            if (!(argv && argc > 0 && !strcasecmp(argv[0+skipargs], "auth"))) {
                if (history) linenoiseHistoryAdd(line);
                if (historyfile) linenoiseHistorySave(historyfile);
            }

            if (argv == NULL) {
                printf("Invalid argument(s)\n");
                linenoiseFree(line);
                continue;
            } else if (argc > 0) {
                if (strcasecmp(argv[0],"quit") == 0 ||
                    strcasecmp(argv[0],"exit") == 0)
                {
                    exit(0);
                } else if (argv[0][0] == ':') {
                    cliSetPreferences(argv,argc,1);
                    sdsfreesplitres(argv,argc);
                    linenoiseFree(line);
                    continue;
                } else if (strcasecmp(argv[0],"restart") == 0) {
                    if (config.eval) {
                        config.eval_ldb = 1;
                        config.output = OUTPUT_RAW;
                        return; /* Return to evalMode to restart the session. */
                    } else {
                        printf("Use 'restart' only in Lua debugging mode.");
                    }
                } else if (argc == 3 && !strcasecmp(argv[0],"connect")) {
                    sdsfree(config.hostip);
                    config.hostip = sdsnew(argv[1]);
                    config.hostport = atoi(argv[2]);
                    cliRefreshPrompt();
                    cliConnect(CC_FORCE);
                } else if (argc == 1 && !strcasecmp(argv[0],"clear")) {
                    linenoiseClearScreen();
                } else {
                    long long start_time = mstime(), elapsed;

                    issueCommandRepeat(argc-skipargs, argv+skipargs, repeat);

                    /* If our debugging session ended, show the EVAL final
                     * reply. */
                    if (config.eval_ldb_end) {
                        config.eval_ldb_end = 0;
                        cliReadReply(0);
                        printf("\n(Lua debugging session ended%s)\n\n",
                            config.eval_ldb_sync ? "" :
                            " -- dataset changes rolled back");
                    }

                    elapsed = mstime()-start_time;
                    if (elapsed >= 500 &&
                        config.output == OUTPUT_STANDARD)
                    {
                        printf("(%.2fs)\n",(double)elapsed/1000);
                    }
                }
            }
            /* Free the argument vector */
            sdsfreesplitres(argv,argc);
        }
        /* linenoise() returns malloc-ed lines like readline() */
        linenoiseFree(line);
    }
    exit(0);
}