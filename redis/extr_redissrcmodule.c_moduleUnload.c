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
struct RedisModule {int /*<<< orphan*/ * name; int /*<<< orphan*/  handle; int /*<<< orphan*/  usedby; int /*<<< orphan*/  types; } ;
typedef  int /*<<< orphan*/  sds ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  dictDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct RedisModule* dictFetchValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dlclose (int /*<<< orphan*/ ) ; 
 char* dlerror () ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moduleFreeModuleStructure (struct RedisModule*) ; 
 int /*<<< orphan*/  moduleUnregisterCommands (struct RedisModule*) ; 
 int /*<<< orphan*/  moduleUnregisterFilters (struct RedisModule*) ; 
 int /*<<< orphan*/  moduleUnregisterSharedAPI (struct RedisModule*) ; 
 int /*<<< orphan*/  moduleUnregisterUsedAPI (struct RedisModule*) ; 
 int /*<<< orphan*/  moduleUnsubscribeNotifications (struct RedisModule*) ; 
 int /*<<< orphan*/  modules ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,...) ; 

int moduleUnload(sds name) {
    struct RedisModule *module = dictFetchValue(modules,name);

    if (module == NULL) {
        errno = ENOENT;
        return REDISMODULE_ERR;
    } else if (listLength(module->types)) {
        errno = EBUSY;
        return REDISMODULE_ERR;
    } else if (listLength(module->usedby)) {
        errno = EPERM;
        return REDISMODULE_ERR;
    }

    moduleUnregisterCommands(module);
    moduleUnregisterSharedAPI(module);
    moduleUnregisterUsedAPI(module);
    moduleUnregisterFilters(module);

    /* Remove any notification subscribers this module might have */
    moduleUnsubscribeNotifications(module);

    /* Unregister all the hooks. TODO: Yet no hooks support here. */

    /* Unload the dynamic library. */
    if (dlclose(module->handle) == -1) {
        char *error = dlerror();
        if (error == NULL) error = "Unknown error";
        serverLog(LL_WARNING,"Error when trying to close the %s module: %s",
            module->name, error);
    }

    /* Remove from list of modules. */
    serverLog(LL_NOTICE,"Module %s unloaded",module->name);
    dictDelete(modules,module->name);
    module->name = NULL; /* The name was already freed by dictDelete(). */
    moduleFreeModuleStructure(module);

    return REDISMODULE_OK;
}