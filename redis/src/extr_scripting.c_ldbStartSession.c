#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sigaction {int /*<<< orphan*/  sa_handler; scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; } ;
typedef  char* sds ;
typedef  int pid_t ;
struct TYPE_8__ {int flags; TYPE_1__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_9__ {int forked; int active; int /*<<< orphan*/  lines; int /*<<< orphan*/  src; int /*<<< orphan*/  conn; int /*<<< orphan*/  children; } ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int CLIENT_LUA_DEBUG_SYNC ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  addReplyError (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  connBlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connSendTimeout (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  freeClientAsync (TYPE_2__*) ; 
 TYPE_4__ ldb ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ ,void*) ; 
 int redisFork () ; 
 char* sdsdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 size_t sdslen (char*) ; 
 int /*<<< orphan*/  sdssetlen (char*,size_t) ; 
 int /*<<< orphan*/  sdssplitlen (char*,size_t,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

int ldbStartSession(client *c) {
    ldb.forked = (c->flags & CLIENT_LUA_DEBUG_SYNC) == 0;
    if (ldb.forked) {
        pid_t cp = redisFork();
        if (cp == -1) {
            addReplyError(c,"Fork() failed: can't run EVAL in debugging mode.");
            return 0;
        } else if (cp == 0) {
            /* Child. Let's ignore important signals handled by the parent. */
            struct sigaction act;
            sigemptyset(&act.sa_mask);
            act.sa_flags = 0;
            act.sa_handler = SIG_IGN;
            sigaction(SIGTERM, &act, NULL);
            sigaction(SIGINT, &act, NULL);

            /* Log the creation of the child and close the listening
             * socket to make sure if the parent crashes a reset is sent
             * to the clients. */
            serverLog(LL_WARNING,"Redis forked for debugging eval");
        } else {
            /* Parent */
            listAddNodeTail(ldb.children,(void*)(unsigned long)cp);
            freeClientAsync(c); /* Close the client in the parent side. */
            return 0;
        }
    } else {
        serverLog(LL_WARNING,
            "Redis synchronous debugging eval session started");
    }

    /* Setup our debugging session. */
    connBlock(ldb.conn);
    connSendTimeout(ldb.conn,5000);
    ldb.active = 1;

    /* First argument of EVAL is the script itself. We split it into different
     * lines since this is the way the debugger accesses the source code. */
    sds srcstring = sdsdup(c->argv[1]->ptr);
    size_t srclen = sdslen(srcstring);
    while(srclen && (srcstring[srclen-1] == '\n' ||
                     srcstring[srclen-1] == '\r'))
    {
        srcstring[--srclen] = '\0';
    }
    sdssetlen(srcstring,srclen);
    ldb.src = sdssplitlen(srcstring,sdslen(srcstring),"\n",1,&ldb.lines);
    sdsfree(srcstring);
    return 1;
}