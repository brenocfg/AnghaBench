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
struct RedisModule {int /*<<< orphan*/  types; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ moduleType ;
struct TYPE_6__ {TYPE_1__* value; } ;
typedef  TYPE_2__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;

/* Variables and functions */
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 struct RedisModule* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 TYPE_2__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  modules ; 

moduleType *moduleTypeLookupModuleByName(const char *name) {
    dictIterator *di = dictGetIterator(modules);
    dictEntry *de;

    while ((de = dictNext(di)) != NULL) {
        struct RedisModule *module = dictGetVal(de);
        listIter li;
        listNode *ln;

        listRewind(module->types,&li);
        while((ln = listNext(&li))) {
            moduleType *mt = ln->value;
            if (memcmp(name,mt->name,sizeof(mt->name)) == 0) {
                dictReleaseIterator(di);
                return mt;
            }
        }
    }
    dictReleaseIterator(di);
    return NULL;
}