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
struct RedisModule {int /*<<< orphan*/  filters; int /*<<< orphan*/  apiver; int /*<<< orphan*/  ver; int /*<<< orphan*/  using; int /*<<< orphan*/  usedby; } ;
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;

/* Variables and functions */
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictGetKey (int /*<<< orphan*/ *) ; 
 struct RedisModule* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  genModulesInfoStringRenderModuleOptions (struct RedisModule*) ; 
 int /*<<< orphan*/  genModulesInfoStringRenderModulesList (int /*<<< orphan*/ ) ; 
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modules ; 
 int /*<<< orphan*/  sdscatfmt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 

sds genModulesInfoString(sds info) {
    dictIterator *di = dictGetIterator(modules);
    dictEntry *de;

    while ((de = dictNext(di)) != NULL) {
        sds name = dictGetKey(de);
        struct RedisModule *module = dictGetVal(de);

        sds usedby = genModulesInfoStringRenderModulesList(module->usedby);
        sds using = genModulesInfoStringRenderModulesList(module->using);
        sds options = genModulesInfoStringRenderModuleOptions(module);
        info = sdscatfmt(info,
            "module:name=%S,ver=%i,api=%i,filters=%i,"
            "usedby=%S,using=%S,options=%S\r\n",
                name, module->ver, module->apiver,
                (int)listLength(module->filters), usedby, using, options);
        sdsfree(usedby);
        sdsfree(using);
        sdsfree(options);
    }
    dictReleaseIterator(di);
    return info;
}