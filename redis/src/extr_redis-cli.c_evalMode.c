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
typedef  int /*<<< orphan*/  redisReply ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int eval_ldb; char* eval; int /*<<< orphan*/  prompt; scalar_t__ eval_ldb_sync; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CC_FORCE ; 
 int REDIS_OK ; 
 int /*<<< orphan*/  cliConnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cliReadReply (int /*<<< orphan*/ ) ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freeReplyObject (int /*<<< orphan*/ *) ; 
 int issueCommand (int,char**) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * redisCommand (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  repl () ; 
 char* sdscatlen (char*,char*,size_t) ; 
 char* sdscatprintf (char*,char*,int) ; 
 char* sdsempty () ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 char* sdsnew (char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 char** zmalloc (int) ; 

__attribute__((used)) static int evalMode(int argc, char **argv) {
    sds script = NULL;
    FILE *fp;
    char buf[1024];
    size_t nread;
    char **argv2;
    int j, got_comma, keys;
    int retval = REDIS_OK;

    while(1) {
        if (config.eval_ldb) {
            printf(
            "Lua debugging session started, please use:\n"
            "quit    -- End the session.\n"
            "restart -- Restart the script in debug mode again.\n"
            "help    -- Show Lua script debugging commands.\n\n"
            );
        }

        sdsfree(script);
        script = sdsempty();
        got_comma = 0;
        keys = 0;

        /* Load the script from the file, as an sds string. */
        fp = fopen(config.eval,"r");
        if (!fp) {
            fprintf(stderr,
                "Can't open file '%s': %s\n", config.eval, strerror(errno));
            exit(1);
        }
        while((nread = fread(buf,1,sizeof(buf),fp)) != 0) {
            script = sdscatlen(script,buf,nread);
        }
        fclose(fp);

        /* If we are debugging a script, enable the Lua debugger. */
        if (config.eval_ldb) {
            redisReply *reply = redisCommand(context,
                    config.eval_ldb_sync ?
                    "SCRIPT DEBUG sync": "SCRIPT DEBUG yes");
            if (reply) freeReplyObject(reply);
        }

        /* Create our argument vector */
        argv2 = zmalloc(sizeof(sds)*(argc+3));
        argv2[0] = sdsnew("EVAL");
        argv2[1] = script;
        for (j = 0; j < argc; j++) {
            if (!got_comma && argv[j][0] == ',' && argv[j][1] == 0) {
                got_comma = 1;
                continue;
            }
            argv2[j+3-got_comma] = sdsnew(argv[j]);
            if (!got_comma) keys++;
        }
        argv2[2] = sdscatprintf(sdsempty(),"%d",keys);

        /* Call it */
        int eval_ldb = config.eval_ldb; /* Save it, may be reverteed. */
        retval = issueCommand(argc+3-got_comma, argv2);
        if (eval_ldb) {
            if (!config.eval_ldb) {
                /* If the debugging session ended immediately, there was an
                 * error compiling the script. Show it and they don't enter
                 * the REPL at all. */
                printf("Eval debugging session can't start:\n");
                cliReadReply(0);
                break; /* Return to the caller. */
            } else {
                strncpy(config.prompt,"lua debugger> ",sizeof(config.prompt));
                repl();
                /* Restart the session if repl() returned. */
                cliConnect(CC_FORCE);
                printf("\n");
            }
        } else {
            break; /* Return to the caller. */
        }
    }
    return retval;
}