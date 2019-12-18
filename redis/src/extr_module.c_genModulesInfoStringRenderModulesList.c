#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
struct TYPE_4__ {TYPE_2__* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
typedef  int /*<<< orphan*/  list ;
struct TYPE_5__ {char* name; } ;
typedef  TYPE_2__ RedisModule ;

/* Variables and functions */
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdscat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 int /*<<< orphan*/  sdstrim (int /*<<< orphan*/ ,char*) ; 

sds genModulesInfoStringRenderModulesList(list *l) {
    listIter li;
    listNode *ln;
    listRewind(l,&li);
    sds output = sdsnew("[");
    while((ln = listNext(&li))) {
        RedisModule *module = ln->value;
        output = sdscat(output,module->name);
    }
    output = sdstrim(output,"|");
    output = sdscat(output,"]");
    return output;
}