#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_6__ {int /*<<< orphan*/  sharedapi; } ;
struct TYPE_5__ {int /*<<< orphan*/ * module; } ;
typedef  TYPE_1__ RedisModuleSharedAPI ;
typedef  int /*<<< orphan*/  RedisModule ;

/* Variables and functions */
 int /*<<< orphan*/  dictDelete (int /*<<< orphan*/ ,char const*) ; 
 char* dictGetKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictGetSafeIterator (int /*<<< orphan*/ ) ; 
 TYPE_1__* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  zfree (TYPE_1__*) ; 

int moduleUnregisterSharedAPI(RedisModule *module) {
    int count = 0;
    dictIterator *di = dictGetSafeIterator(server.sharedapi);
    dictEntry *de;
    while ((de = dictNext(di)) != NULL) {
        const char *apiname = dictGetKey(de);
        RedisModuleSharedAPI *sapi = dictGetVal(de);
        if (sapi->module == module) {
            dictDelete(server.sharedapi,apiname);
            zfree(sapi);
            count++;
        }
    }
    dictReleaseIterator(di);
    return count;
}