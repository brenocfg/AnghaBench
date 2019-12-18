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
struct RedisModule {int options; int /*<<< orphan*/  types; } ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;

/* Variables and functions */
 int REDISMODULE_OPTIONS_HANDLE_IO_ERRORS ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 struct RedisModule* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modules ; 

int moduleAllDatatypesHandleErrors() {
    dictIterator *di = dictGetIterator(modules);
    dictEntry *de;

    while ((de = dictNext(di)) != NULL) {
        struct RedisModule *module = dictGetVal(de);
        if (listLength(module->types) &&
            !(module->options & REDISMODULE_OPTIONS_HANDLE_IO_ERRORS))
        {
            dictReleaseIterator(di);
            return 0;
        }
    }
    dictReleaseIterator(di);
    return 1;
}