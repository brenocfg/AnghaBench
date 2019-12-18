#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * module_blocked_pipe; } ;
struct TYPE_5__ {int unblocked; void* privdata; int /*<<< orphan*/  blocked_on_keys; } ;
typedef  TYPE_1__ RedisModuleBlockedClient ;

/* Variables and functions */
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  moduleUnblockedClients ; 
 int /*<<< orphan*/  moduleUnblockedClientsMutex ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__ server ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

int moduleUnblockClientByHandle(RedisModuleBlockedClient *bc, void *privdata) {
    pthread_mutex_lock(&moduleUnblockedClientsMutex);
    if (!bc->blocked_on_keys) bc->privdata = privdata;
    bc->unblocked = 1;
    listAddNodeTail(moduleUnblockedClients,bc);
    if (write(server.module_blocked_pipe[1],"A",1) != 1) {
        /* Ignore the error, this is best-effort. */
    }
    pthread_mutex_unlock(&moduleUnblockedClientsMutex);
    return REDISMODULE_OK;
}