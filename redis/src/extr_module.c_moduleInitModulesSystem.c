#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * user; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/ * module_blocked_pipe; void* loadmodule_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_MODULE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 void* RedisModule_EventListeners ; 
 int /*<<< orphan*/  Timers ; 
 int /*<<< orphan*/  anetNonBlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* createClient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 void* listCreate () ; 
 void* moduleCommandFilters ; 
 TYPE_2__* moduleFreeContextReusedClient ; 
 int /*<<< orphan*/  moduleGIL ; 
 void* moduleKeyspaceSubscribers ; 
 int /*<<< orphan*/  moduleRegisterCoreAPI () ; 
 void* moduleUnblockedClients ; 
 int /*<<< orphan*/  modules ; 
 int /*<<< orphan*/  modulesDictType ; 
 int pipe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raxNew () ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void moduleInitModulesSystem(void) {
    moduleUnblockedClients = listCreate();
    server.loadmodule_queue = listCreate();
    modules = dictCreate(&modulesDictType,NULL);

    /* Set up the keyspace notification susbscriber list and static client */
    moduleKeyspaceSubscribers = listCreate();
    moduleFreeContextReusedClient = createClient(NULL);
    moduleFreeContextReusedClient->flags |= CLIENT_MODULE;
    moduleFreeContextReusedClient->user = NULL; /* root user. */

    /* Set up filter list */
    moduleCommandFilters = listCreate();

    moduleRegisterCoreAPI();
    if (pipe(server.module_blocked_pipe) == -1) {
        serverLog(LL_WARNING,
            "Can't create the pipe for module blocking commands: %s",
            strerror(errno));
        exit(1);
    }
    /* Make the pipe non blocking. This is just a best effort aware mechanism
     * and we do not want to block not in the read nor in the write half. */
    anetNonBlock(NULL,server.module_blocked_pipe[0]);
    anetNonBlock(NULL,server.module_blocked_pipe[1]);

    /* Create the timers radix tree. */
    Timers = raxNew();

    /* Setup the event listeners data structures. */
    RedisModule_EventListeners = listCreate();

    /* Our thread-safe contexts GIL must start with already locked:
     * it is just unlocked when it's safe. */
    pthread_mutex_lock(&moduleGIL);
}