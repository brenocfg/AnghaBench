#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ client; scalar_t__ unblocked; int /*<<< orphan*/ * timeout_callback; scalar_t__ blocked_on_keys; } ;
typedef  TYPE_1__ RedisModuleBlockedClient ;

/* Variables and functions */
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  moduleBlockedClientTimedOut (scalar_t__) ; 
 int /*<<< orphan*/  moduleUnblockClientByHandle (TYPE_1__*,void*) ; 

int RM_UnblockClient(RedisModuleBlockedClient *bc, void *privdata) {
    if (bc->blocked_on_keys) {
        /* In theory the user should always pass the timeout handler as an
         * argument, but better to be safe than sorry. */
        if (bc->timeout_callback == NULL) return REDISMODULE_ERR;
        if (bc->unblocked) return REDISMODULE_OK;
        if (bc->client) moduleBlockedClientTimedOut(bc->client);
    }
    moduleUnblockClientByHandle(bc,privdata);
    return REDISMODULE_OK;
}