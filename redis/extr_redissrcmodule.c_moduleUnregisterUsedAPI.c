#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_9__ {int /*<<< orphan*/  using; int /*<<< orphan*/  usedby; } ;
typedef  TYPE_2__ RedisModule ;

/* Variables and functions */
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* listSearchKey (int /*<<< orphan*/ ,TYPE_2__*) ; 

int moduleUnregisterUsedAPI(RedisModule *module) {
    listIter li;
    listNode *ln;
    int count = 0;

    listRewind(module->using,&li);
    while((ln = listNext(&li))) {
        RedisModule *used = ln->value;
        listNode *ln = listSearchKey(used->usedby,module);
        if (ln) {
            listDelNode(module->using,ln);
            count++;
        }
    }
    return count;
}