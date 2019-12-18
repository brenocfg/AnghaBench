#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_8__ {int /*<<< orphan*/  filters; } ;
typedef  int /*<<< orphan*/  RedisModuleCommandFilter ;
typedef  TYPE_2__ RedisModule ;

/* Variables and functions */
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* listSearchKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  moduleCommandFilters ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

int moduleUnregisterFilters(RedisModule *module) {
    listIter li;
    listNode *ln;
    int count = 0;

    listRewind(module->filters,&li);
    while((ln = listNext(&li))) {
        RedisModuleCommandFilter *filter = ln->value;
        listNode *ln = listSearchKey(moduleCommandFilters,filter);
        if (ln) {
            listDelNode(moduleCommandFilters,ln);
            count++;
        }
        zfree(filter);
    }
    return count;
}