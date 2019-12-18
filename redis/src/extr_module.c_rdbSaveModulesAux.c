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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  rio ;
struct TYPE_5__ {int aux_save_triggers; int /*<<< orphan*/  aux_save; } ;
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
 int /*<<< orphan*/  modules ; 
 int rdbSaveSingleModuleAux (int /*<<< orphan*/ *,int,TYPE_1__*) ; 

ssize_t rdbSaveModulesAux(rio *rdb, int when) {
    size_t total_written = 0;
    dictIterator *di = dictGetIterator(modules);
    dictEntry *de;

    while ((de = dictNext(di)) != NULL) {
        struct RedisModule *module = dictGetVal(de);
        listIter li;
        listNode *ln;

        listRewind(module->types,&li);
        while((ln = listNext(&li))) {
            moduleType *mt = ln->value;
            if (!mt->aux_save || !(mt->aux_save_triggers & when))
                continue;
            ssize_t ret = rdbSaveSingleModuleAux(rdb, when, mt);
            if (ret==-1) {
                dictReleaseIterator(di);
                return -1;
            }
            total_written += ret;
        }
    }

    dictReleaseIterator(di);
    return total_written;
}