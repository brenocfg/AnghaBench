#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char const* name; void* handle; scalar_t__ blocked_clients; } ;
struct TYPE_10__ {TYPE_2__* module; } ;
typedef  TYPE_1__ RedisModuleCtx ;

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 TYPE_1__ REDISMODULE_CTX_INIT ; 
 int REDISMODULE_ERR ; 
 int /*<<< orphan*/  REDISMODULE_EVENT_MODULE_CHANGE ; 
 int /*<<< orphan*/  REDISMODULE_SUBEVENT_MODULE_LOADED ; 
 int RTLD_LOCAL ; 
 int RTLD_NOW ; 
 int /*<<< orphan*/  dictAdd (int /*<<< orphan*/ ,char const*,TYPE_2__*) ; 
 int /*<<< orphan*/  dlclose (void*) ; 
 char const* dlerror () ; 
 void* dlopen (char const*,int) ; 
 scalar_t__ dlsym (void*,char*) ; 
 int /*<<< orphan*/  moduleFireServerEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  moduleFreeContext (TYPE_1__*) ; 
 int /*<<< orphan*/  moduleFreeModuleStructure (TYPE_2__*) ; 
 int /*<<< orphan*/  moduleUnregisterCommands (TYPE_2__*) ; 
 int /*<<< orphan*/  moduleUnregisterSharedAPI (TYPE_2__*) ; 
 int /*<<< orphan*/  moduleUnregisterUsedAPI (TYPE_2__*) ; 
 int /*<<< orphan*/  modules ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,char const*,...) ; 

int moduleLoad(const char *path, void **module_argv, int module_argc) {
    int (*onload)(void *, void **, int);
    void *handle;
    RedisModuleCtx ctx = REDISMODULE_CTX_INIT;

    handle = dlopen(path,RTLD_NOW|RTLD_LOCAL);
    if (handle == NULL) {
        serverLog(LL_WARNING, "Module %s failed to load: %s", path, dlerror());
        return C_ERR;
    }
    onload = (int (*)(void *, void **, int))(unsigned long) dlsym(handle,"RedisModule_OnLoad");
    if (onload == NULL) {
        dlclose(handle);
        serverLog(LL_WARNING,
            "Module %s does not export RedisModule_OnLoad() "
            "symbol. Module not loaded.",path);
        return C_ERR;
    }
    if (onload((void*)&ctx,module_argv,module_argc) == REDISMODULE_ERR) {
        if (ctx.module) {
            moduleUnregisterCommands(ctx.module);
            moduleUnregisterSharedAPI(ctx.module);
            moduleUnregisterUsedAPI(ctx.module);
            moduleFreeModuleStructure(ctx.module);
        }
        dlclose(handle);
        serverLog(LL_WARNING,
            "Module %s initialization failed. Module not loaded",path);
        return C_ERR;
    }

    /* Redis module loaded! Register it. */
    dictAdd(modules,ctx.module->name,ctx.module);
    ctx.module->blocked_clients = 0;
    ctx.module->handle = handle;
    serverLog(LL_NOTICE,"Module '%s' loaded from %s",ctx.module->name,path);
    /* Fire the loaded modules event. */
    moduleFireServerEvent(REDISMODULE_EVENT_MODULE_CHANGE,
                          REDISMODULE_SUBEVENT_MODULE_LOADED,
                          ctx.module);

    moduleFreeContext(&ctx);
    return C_OK;
}