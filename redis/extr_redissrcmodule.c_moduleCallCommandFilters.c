#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_5__* value; } ;
typedef  TYPE_2__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_11__ {int /*<<< orphan*/  argc; int /*<<< orphan*/  argv; } ;
typedef  TYPE_3__ client ;
struct TYPE_13__ {int flags; int /*<<< orphan*/  (* callback ) (TYPE_4__*) ;TYPE_1__* module; } ;
struct TYPE_12__ {int /*<<< orphan*/  argc; int /*<<< orphan*/  argv; } ;
struct TYPE_9__ {scalar_t__ in_call; } ;
typedef  TYPE_4__ RedisModuleCommandFilterCtx ;
typedef  TYPE_5__ RedisModuleCommandFilter ;

/* Variables and functions */
 int REDISMODULE_CMDFILTER_NOSELF ; 
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 
 TYPE_2__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  moduleCommandFilters ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

void moduleCallCommandFilters(client *c) {
    if (listLength(moduleCommandFilters) == 0) return;

    listIter li;
    listNode *ln;
    listRewind(moduleCommandFilters,&li);

    RedisModuleCommandFilterCtx filter = {
        .argv = c->argv,
        .argc = c->argc
    };

    while((ln = listNext(&li))) {
        RedisModuleCommandFilter *f = ln->value;

        /* Skip filter if REDISMODULE_CMDFILTER_NOSELF is set and module is
         * currently processing a command.
         */
        if ((f->flags & REDISMODULE_CMDFILTER_NOSELF) && f->module->in_call) continue;

        /* Call filter */
        f->callback(&filter);
    }

    c->argv = filter.argv;
    c->argc = filter.argc;
}